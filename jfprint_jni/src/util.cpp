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

#define CONSTRUCTOR_RESULT_TUPLE "(I)V"
#define CONSTRUCTOR_RESULT_TUPLE_2 "(Ljfprint/base/NativeResource;I)V"

#define CLASS_BYTE_BUFFER "Ljava/nio/ByteBuffer;"


namespace Util {

//    JNIHelper::JNIHelper(JNIEnv* env)
//    {
//    }
//
//    JNIHelper::JNIHelper(JNIHelper& orig)
//    {
//    }
//
//    JNIHelper::~JNIHelper()
//    {
//    }
//
//    jclass JNIHelper::getObjectClass(jobject obj)
//    {
//        return nullptr;
//    }
//
//    jclass JNIHelper::findClass(const char clsName)
//    {
//        return nullptr;
//    }


    void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError
	{
		jclass cls = env->GetObjectClass(obj);
        if (NULL == cls) {
            err("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetObjectClassError(LOCATION_INFO, FUNC_DESC);
        }

		jfieldID pointerId = env->GetFieldID(cls, fieldName, CLASS_BYTE_BUFFER);
        if (NULL == pointerId) {
            err("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

		jobject pointer = env->GetObjectField(obj, pointerId);

		if (NULL == pointer) {
			err("On get 'pointer' field - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetFieldValueError(LOCATION_INFO, FUNC_DESC);
		}

		return static_cast<void**>(env->GetDirectBufferAddress(pointer));
	}


    // TODO: Check all calls to me, if the returned value must be freed.
    void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError, JNISetFieldValueError
    {
        jclass cls = env->GetObjectClass(obj);
        if (NULL == cls) {
            err("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetObjectClassError(LOCATION_INFO, FUNC_DESC);
        }

        jfieldID pointerId = env->GetFieldID(cls,  fieldName, CLASS_BYTE_BUFFER);
        if (NULL == pointerId || env->ExceptionCheck()) {
            err("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        jobject oldPointer = env->GetObjectField(obj, pointerId);
        if (env->ExceptionCheck()) {
            err("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        jobject pointer = env->NewDirectByteBuffer(address, size);
        if (NULL == pointer) {
            err("On get 'pointer' field - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetFieldValueError(LOCATION_INFO, FUNC_DESC);
        }

        env->SetObjectField(obj, pointerId, pointer);
        if (env->ExceptionCheck()) {
            err("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNISetFieldValueError(LOCATION_INFO, FUNC_DESC);
        }

        if (NULL == oldPointer) {
            return NULL;
        }

        return env->GetDirectBufferAddress(oldPointer);
    }


    jobject newInstance(JNIEnv *env, const char *clsName) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError
    {
        jclass cls = env->FindClass(clsName);

        if (NULL == cls) {
            err("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIFindClassError(LOCATION_INFO, FUNC_DESC);
        }

        return Util::newInstance(env, cls);
    }


    jobject newInstance(JNIEnv *env, jclass cls) noexcept(false)
    // throws: JNIGetIdError, JNINewObjectError
    {
        jmethodID midInit = env->GetMethodID(cls, "<init>", "()V");
        if (NULL == midInit) {
            err("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        jobject newInstance = env->NewObject(cls, midInit);
        if (NULL == newInstance || env->ExceptionCheck()) {
            err("On instantiate a new object");
            throw JNINewObjectError(LOCATION_INFO, FUNC_DESC);
        }

        return newInstance;
    }


    jobject newResultTuple(JNIEnv *env, int code) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError
    {
        jclass cls = env->FindClass(CLASS_RESULT_TUPLE);
        if (NULL == cls) {
            err("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIFindClassError(LOCATION_INFO, FUNC_DESC);
        }

        jmethodID midInit = env->GetMethodID(cls, "<init>", CONSTRUCTOR_RESULT_TUPLE);
        if (NULL == midInit) {
            err("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        jobject result = env->NewObject(cls, midInit, static_cast<jint>(code));

        if (NULL == result  || env->ExceptionCheck()) {
            err("On instantiate object - ", LOCATION_INFO, FUNC_DESC);
            throw JNINewObjectError(LOCATION_INFO, FUNC_DESC);
        }

        return result;
    }


    jobject newResultTuple(JNIEnv *env, jobject obj, int code) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError
    {
        jclass cls = env->FindClass(CLASS_RESULT_TUPLE);
        if (NULL == cls) {
            err("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIFindClassError(LOCATION_INFO, FUNC_DESC);
        }

        jmethodID midInit = env->GetMethodID(cls, "<init>", CONSTRUCTOR_RESULT_TUPLE_2);
        if (NULL == midInit) {
            err("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        jobject result = env->NewObject(cls, midInit, obj, static_cast<jint>(code));
        if (NULL == result || env->ExceptionCheck()) {
            err("On instantiate object - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNINewObjectError(LOCATION_INFO, FUNC_DESC);
        }

        return result;
    }


    void setWrapperObj(JNIEnv *env, jobject wrapper, jobject obj) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNISetFieldValueError
    {
        jclass cls = env->GetObjectClass(wrapper);
        if (NULL == cls) {
            err("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetObjectClassError(LOCATION_INFO, FUNC_DESC);
        }

        jfieldID fid = env->GetFieldID(cls, "obj", CLASS_NATIVE_RESOURCE);
        if (NULL == fid) {
            err("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
        }

        env->SetObjectField(wrapper, fid, obj);
        if (env->ExceptionCheck()) {
            err("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNISetFieldValueError(LOCATION_INFO, FUNC_DESC);
        }
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
