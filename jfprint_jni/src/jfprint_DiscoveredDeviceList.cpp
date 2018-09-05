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
    Util::DiscoveredList::nativeClose<fp_dscv_dev>(env, obj, fp_dscv_devs_free);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1get
  (JNIEnv *env, jobject obj, jint index)
{
    jobject dscv_dev = Util::DiscoveredList::nativeGet<fp_dscv_dev>(env, obj, index, "Ljfprint/DiscoveredDevice;");

    if (Util::checkAndThrowException(env, dscv_dev, obj,
                                     CAN_NOT_ACCESS_DISCOVERED("DiscoveredDevice"), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return dscv_dev;
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1dicoverDevices
  (JNIEnv *env, jclass cls)
{
    jobject dscv_dev_list = Util::DiscoveredList::discover<fp_dscv_dev>(env, cls, fp_discover_devs);

    if (Util::checkAndThrowException(env, dscv_dev_list, cls,
                                     CAN_NOT_ACCESS_DISCOVERED_LIST("discovered devices"), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return dscv_dev_list;
}
