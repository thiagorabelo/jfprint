
#include "jfprint_DiscoveredPrint.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredPrint_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_getDriverId
  (JNIEnv *env, jobject obj)
{
    fp_dscv_print **p_discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<int>(fp_dscv_print_get_driver_id(*p_discovered_print));
}


JNIEXPORT jlong JNICALL Java_jfprint_DiscoveredPrint_getDevtype
  (JNIEnv *env, jobject obj)
{
    fp_dscv_print **p_discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<long>(fp_dscv_print_get_devtype(*p_discovered_print));
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_getFinger
  (JNIEnv *env, jobject obj)
{
    fp_dscv_print **p_discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<int>(fp_dscv_print_get_finger(*p_discovered_print));
}


JNIEXPORT jint JNICALL Java_jfprint_DiscoveredPrint_delete
  (JNIEnv *env, jobject obj)
{
    fp_dscv_print **p_discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<int>(fp_dscv_print_delete(*p_discovered_print));
}
