#include "jfprint_DiscoveredPrintList.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredPrintList_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);
    Util::DiscoveredList::nativeClose<fp_dscv_print>(env, obj, fp_dscv_prints_free);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_fp_1get
  (JNIEnv *env, jobject obj, jint index)
{
    jobject dscv_print = Util::DiscoveredList::nativeGet<fp_dscv_print>(env, obj, index, "Ljfprint/DiscoveredPrint;");

    if (Util::checkAndThrowException(env, dscv_print, obj,
                                     "Can not access DiscoveredPrint", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return dscv_print;
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_fp_1discoverPrints
  (JNIEnv *env, jclass cls)
{
    jobject dscv_print_list = Util::DiscoveredList::discover<fp_dscv_print>(env, cls, fp_discover_prints);

    if (Util::checkAndThrowException(env, dscv_print_list, cls,
                                     "Can not access the list of discovered prints", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return dscv_print_list;
}
