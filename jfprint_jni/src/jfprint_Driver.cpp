#include "jfprint_Driver.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Driver_nativeClose
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_driver **driver = h.getPointer<fp_driver>(obj);

        // Delete only the pointer to pointer.
        delete driver;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getName
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_driver **p_driver = h.getPointer<fp_driver>(obj);
        const char *name = fp_driver_get_name(*p_driver);
        return env->NewStringUTF(name);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_fp_1getFullName
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_driver **p_driver = h.getPointer<fp_driver>(obj);
        const char *name = fp_driver_get_name(*p_driver);
        return env->NewStringUTF(name);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_Driver_fp_1getDriverID
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_driver **p_driver = h.getPointer<fp_driver>(obj);
        jlong driverId = static_cast<jlong>(fp_driver_get_driver_id(*p_driver));
        return driverId;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}
