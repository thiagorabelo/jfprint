#include "jfprint_DiscoveredPrintList.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredPrintList_nativeClose
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    try {
        Util::DiscoveredItemsList::nativeClose<fp_dscv_print>(env, obj, fp_dscv_prints_free);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_fp_1get
  (JNIEnv *env, jobject obj, jint index)
{
    log_debug("Running ", FUNC_DESC);

    try {
        jobject dscv_print = Util::DiscoveredItemsList::nativeGet<fp_dscv_print>(env,
                                                                                 obj,
                                                                                 index,
                                                                                 CLASS_DISCOVERED_PRINT);
        return dscv_print;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_fp_1discoverPrints
  (JNIEnv *env, jclass cls)
{
    log_debug("Running ", FUNC_DESC);

    try {
        jobject dscv_print_list = Util::DiscoveredItemsList::discover<fp_dscv_print>(env,
                                                                                     cls,
                                                                                     fp_discover_prints,
                                                                                     fp_dscv_prints_free);
        return dscv_print_list;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}
