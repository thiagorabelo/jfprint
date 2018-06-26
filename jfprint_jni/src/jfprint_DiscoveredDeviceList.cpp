#include "jfprint_DiscoveredDeviceList.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredDeviceList_nativeClose
  (JNIEnv *env, jobject obj)
{
    Util::DiscoveredList::nativeClose<fp_dscv_dev>(env, obj, fp_dscv_devs_free);
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1get
  (JNIEnv *env, jobject obj, jint index)
{
    return Util::DiscoveredList::nativeGet<fp_dscv_dev>(env, obj, index, "Ljfprint/DiscoveredDevice;", "discovered_devs");
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1dicoverDevices
  (JNIEnv *env, jclass cls)
{
    return Util::DiscoveredList::discoverPrints<fp_dscv_dev>(env, cls, "DiscoveredDeviceList", fp_discover_devs);
}
