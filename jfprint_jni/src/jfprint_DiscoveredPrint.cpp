
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

    fp_dscv_print **p_dscvrd_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_dscvrd_print, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<int>(fp_dscv_print_get_driver_id(*p_dscvrd_print));
}


JNIEXPORT jlong JNICALL Java_jfprint_DiscoveredPrint_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dscv_print **p_dscvrd_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_dscvrd_print, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<long>(fp_dscv_print_get_devtype(*p_dscvrd_print));
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_fp_1getFinger
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dscv_print **p_dscvrd_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_dscvrd_print, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<int>(fp_dscv_print_get_finger(*p_dscvrd_print));
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_fp_1delete
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);
    
    fp_dscv_print **p_dscvrd_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_dscvrd_print, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<int>(fp_dscv_print_delete(*p_dscvrd_print));
}
