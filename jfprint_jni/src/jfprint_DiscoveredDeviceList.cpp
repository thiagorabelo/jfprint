#include "jfprint_DiscoveredDeviceList.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredDeviceList_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        Util::DiscoveredItemsList::nativeClose<fp_dscv_dev>(env, obj, fp_dscv_devs_free);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1get
  (JNIEnv *env, jobject obj, jint index)
{
    log("Running ", FUNC_DESC);

    try {
        jobject dscv_dev = Util::DiscoveredItemsList::nativeGet<fp_dscv_dev>(env,
                                                                             obj,
                                                                             index,
                                                                             CLASS_DISCOVERED_DEVICE);
        return dscv_dev;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1dicoverDevices
  (JNIEnv *env, jclass cls)
{
    log("Running ", FUNC_DESC);

    try {
        jobject dscv_dev_list = Util::DiscoveredItemsList::discover<fp_dscv_dev>(env,
                                                                                 cls,
                                                                                 fp_discover_devs,
                                                                                 fp_dscv_devs_free);
        return dscv_dev_list;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}
