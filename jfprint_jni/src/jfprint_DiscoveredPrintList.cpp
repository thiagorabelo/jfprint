#include "jfprint_DiscoveredPrintList.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredPrintList_nativeClose
  (JNIEnv *env, jobject obj)
{
    Util::DiscoveredList::nativeClose<fp_dscv_print>(env, obj, fp_dscv_prints_free);
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_nativeGet
  (JNIEnv *env, jobject obj, jint index)
{
    return Util::DiscoveredList::nativeGet<fp_dscv_print>(env, obj, index, "Ljfprint/DiscoveredPrint;", "discovered_prints");
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredPrintList_discoverPrints
  (JNIEnv *env, jclass cls)
{
    return Util::DiscoveredList::discoverPrints<fp_dscv_print>(env, cls, "DiscoveredPrintList", fp_discover_prints);
}