#include "util.h"


#define CONSTRUCTOR_OPERATION_ERROR_EXCEPTION "()V"
#define CONSTRUCTOR_OPERATION_ERROR_EXCEPTION_MSG "(Ljava/lang/String;)V"

#define CONSTRUCTOR_CODE_ERROR_EXCEPTION "(I)V"

#define CONSTRUCTOR_NATIVE_EXCEPTION "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
#define CONSTRUCTOR_NATIVE_EXCEPTION_CAUSE "(Ljava/lang/Throwable;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"

#define CONSTRUCTOR_CLASS_NATIVE_EXCEPTION "(Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
#define CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE "(Ljava/lang/Throwable;Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"

#define CONSTRUCTOR_NATIVE_CAN_NOT_FIND_EXCEPTION "(Ljava/lang/String;)V"

#define EXCEPTION "Ljava/lang/Exception;"


namespace Util {

    void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName)
	{
		jclass cls = env->GetObjectClass(obj);
		jfieldID pointerId = env->GetFieldID(cls, fieldName, "Ljava/nio/ByteBuffer;");
		jobject pointer = env->GetObjectField(obj, pointerId);

		if (NULL == pointer) {
			err("Can not access field 'pointer'. - " LOCATION_INFO, ", ", __PRETTY_FUNCTION__);
			return NULL;
		}

		return static_cast<void**>(env->GetDirectBufferAddress(pointer));
	}


    // TODO: Check all calls to me, if the returned value must be freed.
    void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size)
    {
        jclass cls = env->GetObjectClass(obj);
        jfieldID pointerId = env->GetFieldID(cls,  fieldName, "Ljava/nio/ByteBuffer;");

        if (NULL == pointerId || env->ExceptionCheck()) {
            err("Can not find 'pointerId' - " LOCATION_INFO, ", ", __PRETTY_FUNCTION__);
            return NULL;
        }

        jobject oldPointer = env->GetObjectField(obj, pointerId);
        jobject pointer = env->NewDirectByteBuffer(address, size);

        env->SetObjectField(obj, pointerId, pointer);

        if (NULL == oldPointer) {
            return NULL;
        }

        return env->GetDirectBufferAddress(oldPointer);
    }


    jobject newInstance(JNIEnv *env, const char *clsDescription)
    {
        jclass cls = env->FindClass(clsDescription);

        if (NULL == cls) {
            err("Can not find class: ", clsDescription, " - ", LOCATION_INFO, ", ", __PRETTY_FUNCTION__);
            return NULL;
        }

        return Util::newInstance(env, cls);
    }


    jobject newInstance(JNIEnv *env, jclass cls)
    {
        jmethodID midInit = env->GetMethodID(cls, "<init>", "()V");

        if (NULL == midInit) {
            err("Can not find method initializer ()V.", " - ", LOCATION_INFO, ", ", __PRETTY_FUNCTION__);

            if (env->ExceptionCheck()) {
                jthrowable cause = Util::stopExceptionPropagation(env);

                Util::throwNativeException(env, cause, cls,
                                           "Can not find method initializer ()V", __PRETTY_FUNCTION__, LOCATION_INFO);
            } else {
                Util::throwNativeException(env, cls, "Can not find method initializer ()V",
                                           __PRETTY_FUNCTION__, LOCATION_INFO);
            }

            return NULL;
        }

        jobject newInstance = env->NewObject(cls, midInit);

        return newInstance;
    }


    jint throwCodeError(JNIEnv *env, jint code)
    {
        jclass cls = env->FindClass(CLASS_CODE_ERROR);
        jmethodID cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_CODE_ERROR_EXCEPTION);
        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, code));

        return env->Throw(excpt);
    }


    jint throwOperationError(JNIEnv *env)
    {
        jclass cls = env->FindClass(CLASS_OPERATION_ERROR);
        jmethodID cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_OPERATION_ERROR_EXCEPTION);
        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr));

        return env->Throw(excpt);
    }


    jint throwOperationError(JNIEnv *env, const char *msg)
    {
        jclass cls = env->FindClass(CLASS_OPERATION_ERROR);
        jmethodID cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_OPERATION_ERROR_EXCEPTION_MSG);
        jstring jmsg = env->NewStringUTF(msg);
        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, jmsg));

        return env->Throw(excpt);
    }


    jint throwException(JNIEnv *env, const char *message)
    {
        return Util::throwException(env, EXCEPTION, message);
    }


    jint throwException(JNIEnv *env, const char *clsName, const char *message)
    {
        jclass cls = env->FindClass(clsName);
        return env->ThrowNew(cls, message);
    }


    jint throwNativeException(JNIEnv *env, const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass cls = env->FindClass(CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_NATIVE_EXCEPTION);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jclass cls,
                              const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cls,
                                                                       jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jobject obj,
                              const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION);

        jclass cls = env->GetObjectClass(obj);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cls,
                                                                       jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jthrowable cause,
                              const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass cls = env->FindClass(CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_NATIVE_EXCEPTION_CAUSE);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, cause,
                                                        jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jthrowable cause, jobject obj,
                              const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE);

        jclass cls = env->GetObjectClass(obj);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cause, cls,
                                                                       jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jthrowable cause, jclass cls,
                              const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cause, cls,
                                                                       jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }


    bool checkAndThrowException(JNIEnv *env,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (env->ExceptionCheck()) {
            err(message, " - ", locationInfo, ", ", funcName);
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, message, funcName, locationInfo);

            return true;
        }

        return false;
    }


    bool checkAndThrowException(JNIEnv *env, jobject obj,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (env->ExceptionCheck()) {
            err(message, " - ", locationInfo, ", ", funcName);
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, obj, message, funcName, locationInfo);

            return true;
        }

        return false;
    }


    bool checkAndThrowException(JNIEnv *env, jclass cls,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (env->ExceptionCheck()) {
            err(message, " - ", locationInfo, ", ", funcName);
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, cls, message, funcName, locationInfo);

            return true;
        }

        return false;
    }


    bool checkAndThrowException(JNIEnv *env, const void *to_verify,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (NULL == to_verify) {
            err(message, " - ", locationInfo, ", ", funcName);

            if (env->ExceptionCheck()) {
                jthrowable cause = Util::stopExceptionPropagation(env);
                Util::throwNativeException(env, cause, message, funcName, locationInfo);
            } else {
                Util::throwNativeException(env, message, funcName, locationInfo);
            }

            return true;
        }

        return false;
    }


    bool checkAndThrowException(JNIEnv *env, const void *to_verify, jclass cls,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (NULL == to_verify) {
            err(message, " - ", locationInfo, ", ", funcName);

            if (env->ExceptionCheck()) {
                jthrowable cause = Util::stopExceptionPropagation(env);
                Util::throwNativeException(env, cause, cls, message, funcName, locationInfo);
            } else {
                Util::throwNativeException(env, cls, message, funcName, locationInfo);
            }

            return true;
        }

        return false;
    }


    bool checkAndThrowException(JNIEnv *env, const void *to_verify, jobject obj,
                                const char *message, const char *locationInfo, const char *funcName)
    {
        if (NULL == to_verify) {
            err(message, " - ", locationInfo, ", ", funcName);

            if (env->ExceptionCheck()) {
                jthrowable cause = Util::stopExceptionPropagation(env);
                Util::throwNativeException(env, cause, obj, message, funcName, locationInfo);
            } else {
                Util::throwNativeException(env, obj, message, funcName, locationInfo);
            }

            return true;
        }

        return false;
    }

};
