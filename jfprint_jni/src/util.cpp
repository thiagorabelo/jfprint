#include "util.h"

namespace Util {

    void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName)
	{
		jclass cls = env->GetObjectClass(obj);

        if (NULL == cls) {
			log("Can not access class. " LOCATION_INFO);
			return NULL;
		}

		jfieldID pointerId = env->GetFieldID(cls, fieldName, "Ljava/nio/ByteBuffer;");
		if (NULL == pointerId) {
			log("Can not access field ID 'pointer'. " LOCATION_INFO);
			return NULL;
		}

		jobject pointer = env->GetObjectField(obj, pointerId);
		if (NULL == pointer) {
			log("Can not access field 'pointer'. " LOCATION_INFO);
			return NULL;
		}

		return static_cast<void**>(env->GetDirectBufferAddress(pointer));
	}


    void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size)
    {
        jclass cls = env->GetObjectClass(obj);
        jfieldID pointerId = env->GetFieldID(cls,  fieldName, "Ljava/nio/ByteBuffer;");

        if (NULL == pointerId) {
            log("Can not find 'pointerId'. " LOCATION_INFO);
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
            log("Can not find class ", clsDescription);
            return NULL;
        }

        return Util::newInstance(env, cls);
    }


    jobject newInstance(JNIEnv *env, jclass cls)
    {
        jmethodID midInit = env->GetMethodID(cls, "<init>", "()V");

        if (NULL == midInit) {
            log("Can not find method initializer.");
            return NULL;
        }

        jobject newInstance = env->NewObject(cls, midInit);

        return newInstance;
    }

    jint throwException(JNIEnv *env, const char *message)
    {
        jclass excp = env->FindClass("Ljava/lang/Exception;");
        return env->ThrowNew(excp, message);
    }
}
