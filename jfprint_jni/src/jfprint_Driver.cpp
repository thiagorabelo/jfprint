#include "jfprint_Driver.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Driver_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", __PRETTY_FUNCTION__);

    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, driver, obj,
                                     "Can not access Driver 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    // Delete only the pointer to pointer.
    delete driver;
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getName
  (JNIEnv *env, jobject obj)
{
    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer", fp_driver_get_name, NULL);

    if (Util::checkAndThrowException(env, name, obj, "Can not retrieve driver name", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return env->NewStringUTF(name);
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getFullName
  (JNIEnv *env, jobject obj)
{
    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer",
                                                                        fp_driver_get_full_name, NULL);

    if (Util::checkAndThrowException(env, name, obj, "Can not retrieve driver full name", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return env->NewStringUTF(name);
}


JNIEXPORT jlong JNICALL Java_jfprint_Driver_fp_1getDriverID
  (JNIEnv *env, jobject obj)
{
    long id = Util::applyFuncToPointer<jlong, fp_driver>(env, obj, "pointer", fp_driver_get_driver_id, 0L);

    if (Util::checkAndThrowException(env, obj, "Can not retrieve driver name", LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return id;
}
