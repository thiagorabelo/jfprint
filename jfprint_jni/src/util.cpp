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


    JNIHandler::JNIHandler(JNIEnv* env)
    : env(env)
    {
    }

    JNIHandler::~JNIHandler()
    {
    }

    void* JNIHandler::setPointer(jobject obj, void *address, size_t size) noexcept(false)
    {
        try {
            return Util::setPointerAddress(env, obj, "pointer", address, size);
        } catch (JNIError& error) {
            throw JNISetPointerError(error);
        }
    }

    jobject JNIHandler::newInstance(const char* clsName)
    {
        try {
            return Util::newInstance(env, clsName);
        } catch (JNIError& cause) {
            throw JNINewInstanceError(cause);
        }
    }

    jobject JNIHandler::newInstance(jclass cls)
    {
        try {
            return Util::newInstance(env, cls);
        } catch (JNIError& cause) {
            throw JNINewInstanceError(cause);
        }
    }

    void JNIHandler::setWrapperObj(jobject wrapper, jobject obj)
    {
        try {
            return Util::setWrapperObj(env, wrapper, obj);
        } catch (JNIError& cause) {
            throw JNISetWrapperObjError(cause);
        }
    }

    jobject JNIHandler::newResultTuple(int code)
    {
        try {
            return Util::newResultTuple(env, code);
        } catch (JNIError& cause) {
            throw JNINewInstanceError(cause);
        }
    }

    jobject JNIHandler::newResultTuple(jobject obj, int code)
    {
        try {
            return Util::newResultTuple(env, obj, code);
        } catch (JNIError& cause) {
            throw JNINewInstanceError(cause);
        }
    }

    jbyteArray JNIHandler::newByteArray(jsize size, jbyte* buf)
    {
        try {
            return Util::newByteArray(env, size, buf);
        } catch (JNIError& cause) {
            throw JNINewByteArrayError(cause);
        }
    }

    jbyte *JNIHandler::fromByteArray(jbyteArray byteArray)
    {
        try {
            return Util::fromByteArray(env, byteArray);
        } catch (JNIError& cause) {
            throw JNIByteArrayError(cause);
        }
    }


    void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError
	{
		jclass cls = env->GetObjectClass(obj);
        if (NULL == cls) {
            log_error("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get object class", LOCATION_INFO, FUNC_DESC);
        }

		jfieldID pointerId = env->GetFieldID(cls, fieldName, CLASS_BYTE_BUFFER);
        if (NULL == pointerId) {
            log_error("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get field id", LOCATION_INFO, FUNC_DESC);
        }

		jobject pointer = env->GetObjectField(obj, pointerId);

		if (NULL == pointer) {
			log_error("On get 'pointer' field - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get 'pointer' value", LOCATION_INFO, FUNC_DESC);
		}

		return static_cast<void**>(env->GetDirectBufferAddress(pointer));
	}


    // TODO: Check all calls to me, if the returned value must be freed.
    void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError, JNISetFieldValueError
    {
        jclass cls = env->GetObjectClass(obj);
        if (NULL == cls) {
            log_error("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get object class", LOCATION_INFO, FUNC_DESC);
        }

        jfieldID pointerId = env->GetFieldID(cls,  fieldName, CLASS_BYTE_BUFFER);
        if (NULL == pointerId || env->ExceptionCheck()) {
            log_error("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get field id", LOCATION_INFO, FUNC_DESC);
        }

        jobject oldPointer = env->GetObjectField(obj, pointerId);
        if (env->ExceptionCheck()) {
            log_error("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get field id", LOCATION_INFO, FUNC_DESC);
        }

        jobject pointer = env->NewDirectByteBuffer(address, size);
        if (NULL == pointer) {
            log_error("On get 'pointer' field - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get 'pointer' value", LOCATION_INFO, FUNC_DESC);
        }

        env->SetObjectField(obj, pointerId, pointer);
        if (env->ExceptionCheck()) {
            log_error("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On set field value", LOCATION_INFO, FUNC_DESC);
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
            log_error("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On find class", LOCATION_INFO, FUNC_DESC);
        }

        return Util::newInstance(env, cls);
    }


    jobject newInstance(JNIEnv *env, jclass cls) noexcept(false)
    // throws: JNIGetIdError, JNINewObjectError
    {
        jmethodID midInit = env->GetMethodID(cls, "<init>", "()V");
        if (NULL == midInit) {
            log_error("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get method id", LOCATION_INFO, FUNC_DESC);
        }

        jobject newInstance = env->NewObject(cls, midInit);
        if (NULL == newInstance || env->ExceptionCheck()) {
            log_error("On instantiate a new object" LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On instantiate a new object", LOCATION_INFO, FUNC_DESC);
        }

        return newInstance;
    }


    jobject newResultTuple(JNIEnv *env, int code) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError
    {
        jclass cls = env->FindClass(CLASS_RESULT_TUPLE);
        if (NULL == cls) {
            log_error("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On find class", LOCATION_INFO, FUNC_DESC);
        }

        jmethodID midInit = env->GetMethodID(cls, "<init>", CONSTRUCTOR_RESULT_TUPLE);
        if (NULL == midInit) {
            log_error("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get method id", LOCATION_INFO, FUNC_DESC);
        }

        jobject result = env->NewObject(cls, midInit, static_cast<jint>(code));

        if (NULL == result  || env->ExceptionCheck()) {
            log_error("On instantiate object - ", LOCATION_INFO, FUNC_DESC);
            throw JNIError("On instantiate object", LOCATION_INFO, FUNC_DESC);
        }

        return result;
    }


    jobject newResultTuple(JNIEnv *env, jobject obj, int code) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError
    {
        jclass cls = env->FindClass(CLASS_RESULT_TUPLE);
        if (NULL == cls) {
            log_error("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On find class", LOCATION_INFO, FUNC_DESC);
        }

        jmethodID midInit = env->GetMethodID(cls, "<init>", CONSTRUCTOR_RESULT_TUPLE_2);
        if (NULL == midInit) {
            log_error("On get method id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get method id", LOCATION_INFO, FUNC_DESC);
        }

        jobject result = env->NewObject(cls, midInit, obj, static_cast<jint>(code));
        if (NULL == result || env->ExceptionCheck()) {
            log_error("On instantiate object - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On instantiate object", LOCATION_INFO, FUNC_DESC);
        }

        return result;
    }


    void setWrapperObj(JNIEnv *env, jobject wrapper, jobject obj) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNISetFieldValueError
    {
        jclass cls = env->GetObjectClass(wrapper);
        if (NULL == cls) {
            log_error("On get object class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get object class", LOCATION_INFO, FUNC_DESC);
        }

        jfieldID fid = env->GetFieldID(cls, "obj", CLASS_NATIVE_RESOURCE);
        if (NULL == fid) {
            log_error("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On get field id", LOCATION_INFO, FUNC_DESC);
        }

        env->SetObjectField(wrapper, fid, obj);
        if (env->ExceptionCheck()) {
            log_error("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On set field value", LOCATION_INFO, FUNC_DESC);
        }
    }


    jbyteArray newByteArray(JNIEnv *env, jsize size, jbyte* buf)
    {
        jbyteArray byteArray = env->NewByteArray(size);

        if (NULL != byteArray || env->ExceptionCheck()) {
            throw JNIError("On instantiate a new byte array", LOCATION_INFO, FUNC_DESC);
        }

        env->SetByteArrayRegion(byteArray, 0, size, buf);

        if (env->ExceptionCheck()) {
            throw JNIError("On set byte array region", LOCATION_INFO, FUNC_DESC);
        }

        return byteArray;
    }


    jbyte *fromByteArray(JNIEnv *env, jbyteArray byteArray)
    {
        jsize jArraySize = env->GetArrayLength(byteArray);

        if (jArraySize <= 0) {
            log_debug("Array is empty - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("Array is empty", LOCATION_INFO, FUNC_DESC);
        }

        jbyte *buf = new jbyte[jArraySize];
        env->GetByteArrayRegion(byteArray, 0, jArraySize, buf);

        if (env->ExceptionCheck()) {
            delete buf;
            throw JNIError("On copy data from Java byte array to buffer", LOCATION_INFO, FUNC_DESC);
        }

        return buf;
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


    jint throwNativeException(JNIEnv *env, const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass cls;
        jmethodID cttr;
        jthrowable excpt;

        if (env->ExceptionCheck()) {
            cls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_NATIVE_EXCEPTION_CAUSE);
            jthrowable cause = Util::stopExceptionPropagation(env);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, cause, jmessage, jfuncName, jlocationInfo));
        } else {
            cls = env->FindClass(CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(cls, "<init>", CONSTRUCTOR_NATIVE_EXCEPTION);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(cls, cttr, jmessage, jfuncName, jlocationInfo));
        }

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jclass cls,
                              const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls;
        jmethodID cttr;
        jthrowable excpt;

        if (env->ExceptionCheck()) {
            excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE);
            jthrowable cause = Util::stopExceptionPropagation(env);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cause, cls,
                                                                jmessage, jfuncName, jlocationInfo));
        } else {
            excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cls,
                                                                jmessage, jfuncName, jlocationInfo));
        }

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jobject obj,
                              const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls;
        jmethodID cttr;
        jclass cls;;
        jthrowable excpt;

        if (env->ExceptionCheck()) {
            excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE);
            cls = env->GetObjectClass(obj);
            jthrowable cause = Util::stopExceptionPropagation(env);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cause, cls,
                                                                jmessage, jfuncName, jlocationInfo));
        } else {
            excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
            cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION);
            cls = env->GetObjectClass(obj);
            excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cls,
                                                                jmessage, jfuncName, jlocationInfo));
        }

        return env->Throw(excpt);
    }


    jint throwNativeException(JNIEnv *env, jthrowable cause,
                              const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

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
                              const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

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
                              const char *message, const char *locationInfo, const char *funcName)
    {
        log_error(message, " - ", locationInfo, ", ", funcName);

        jstring jmessage = env->NewStringUTF(message);
        jstring jfuncName = env->NewStringUTF(funcName);
        jstring jlocationInfo = env->NewStringUTF(locationInfo);

        jclass excls = env->FindClass(CLASS_CLASS_NATIVE_EXCEPTION);
        jmethodID cttr = env->GetMethodID(excls, "<init>", CONSTRUCTOR_CLASS_NATIVE_EXCEPTION_CAUSE);

        jthrowable excpt = reinterpret_cast<jthrowable>(env->NewObject(excls, cttr, cause, cls,
                                                                       jmessage, jfuncName, jlocationInfo));

        return env->Throw(excpt);
    }

};
