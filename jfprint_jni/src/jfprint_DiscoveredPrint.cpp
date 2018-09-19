
#include "jfprint_DiscoveredPrint.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredPrint_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_fp_1getDriverId
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dscv_print **p_dscvrd_print = h.getPointer<fp_dscv_print>(obj);
        return static_cast<int>(fp_dscv_print_get_driver_id(*p_dscvrd_print));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_DiscoveredPrint_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dscv_print **p_dscvrd_print = h.getPointer<fp_dscv_print>(obj);
        return static_cast<long>(fp_dscv_print_get_devtype(*p_dscvrd_print));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_fp_1getFinger
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dscv_print **p_dscvrd_print = h.getPointer<fp_dscv_print>(obj);
        return static_cast<int>(fp_dscv_print_get_finger(*p_dscvrd_print));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_fp_1delete
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dscv_print **p_dscvrd_print = h.getPointer<fp_dscv_print>(obj);
        return static_cast<int>(fp_dscv_print_delete(*p_dscvrd_print));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}
