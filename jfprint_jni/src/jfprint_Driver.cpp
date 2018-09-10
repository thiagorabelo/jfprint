#include "jfprint_Driver.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Driver_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, driver, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DRIVER), LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    // Delete only the pointer to pointer.
    delete driver;
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getName
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer", fp_driver_get_name, NULL);

    if (Util::checkAndThrowException(env, name, obj, CAN_NOT_RETRIEVE_DRIVER_NAME, LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return env->NewStringUTF(name);
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getFullName
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer",
                                                                        fp_driver_get_full_name, NULL);

    if (Util::checkAndThrowException(env, name, obj,
                                     CAN_NOT_RETRIEVE_DRIVER_FULL_NAME, LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return env->NewStringUTF(name);
}


JNIEXPORT jlong JNICALL Java_jfprint_Driver_fp_1getDriverID
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    long id = Util::applyFuncToPointer<jlong, fp_driver>(env, obj, "pointer", fp_driver_get_driver_id, 0L);

    if (Util::checkAndThrowException(env, obj, CAN_NOT_RETRIEVE_DRIVER_ID, LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return id;
}
