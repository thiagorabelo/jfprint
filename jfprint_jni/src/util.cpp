#include "util.h"


#define NATIVE_EXCEPTION "Ljfprint/exception/NativeException;"
#define NATIVE_EXCEPTION_CONSTRUCTOR "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
#define CLASS_NATIVE_EXCEPTION "Ljfprint/exception/ClassNativeException;"
#define CLASS_NATIVE_EXCEPTION_CONSTRUCTOR "(Ljava/lang/Class;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"
#define NATIVE_CAN_NOT_FIND_EXCEPTION "Ljfprint/exception/NativeCanNotFindException;"
#define NATIVE_CAN_NOT_FIND_EXCEPTION_CONSTRUCTOR "(Ljava/lang/String;)V"
#define EXCEPTION "Ljava/lang/Exception;"


namespace Util {

    void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName)
	{
		jclass cls = env->GetObjectClass(obj);

        if (NULL == cls) {
			err("Can not access class. " LOCATION_INFO);
            Util::throwException(env, "Can not access class. " LOCATION_INFO);
			return NULL;
		}

		jfieldID pointerId = env->GetFieldID(cls, fieldName, "Ljava/nio/ByteBuffer;");
		if (NULL == pointerId) {
			err("Can not access field ID 'pointer'. " LOCATION_INFO);
            Util::throwException(env, "Can not access field ID 'pointer'. " LOCATION_INFO);
			return NULL;
		}

		jobject pointer = env->GetObjectField(obj, pointerId);
		if (NULL == pointer) {
			err("Can not access field 'pointer'. " LOCATION_INFO);
            Util::throwException(env, "Can not access field 'pointer'. " LOCATION_INFO);
			return NULL;
		}

		return static_cast<void**>(env->GetDirectBufferAddress(pointer));
	}


    void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size)
    {
        jclass cls = env->GetObjectClass(obj);
        jfieldID pointerId = env->GetFieldID(cls,  fieldName, "Ljava/nio/ByteBuffer;");

        if (NULL == pointerId) {
            err("Can not find 'pointerId'. " LOCATION_INFO);
            Util::throwException(env, "Can not find 'pointerId'. " LOCATION_INFO);
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
            err("Can not find class ", clsDescription);
            Util::throwException(env, NATIVE_CAN_NOT_FIND_EXCEPTION, clsDescription);
            return NULL;
        }

        return Util::newInstance(env, cls);
    }


    jobject newInstance(JNIEnv *env, jclass cls)
    {
        jmethodID midInit = env->GetMethodID(cls, "<init>", "()V");

        if (NULL == midInit) {
            err("Can not find method initializer ()V.");
            Util::throwException(env, NATIVE_CAN_NOT_FIND_EXCEPTION, "Can not find method initializer ()V.");
            return NULL;
        }

        jobject newInstance = env->NewObject(cls, midInit);

        return newInstance;
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

        jclass cls = env->FindClass(NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(cls, "<init>", NATIVE_EXCEPTION_CONSTRUCTOR);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }

    jint throwNativeException(JNIEnv *env, jclass cls, const char *message, const char *funcName, const char *locationInfo)
    {
        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CLASS_NATIVE_EXCEPTION_CONSTRUCTOR);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cls, jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }
}
