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

    if (NULL == dscv_dev) {
        err("Can not access DiscoveredDevice - " LOCATION_INFO ", ", FUNC_DESC);

        if (env->ExceptionCheck()) {
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, obj, "Can not access DiscoveredDevice", FUNC_DESC, LOCATION_INFO);
        } else {
            Util::throwNativeException(env, obj, "Can not access DiscoveredDevice", FUNC_DESC, LOCATION_INFO);
        }

        return NULL;
    }

    return dscv_dev;
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDeviceList_fp_1dicoverDevices
  (JNIEnv *env, jclass cls)
{
    jobject dscv_dev_list = Util::DiscoveredList::discover<fp_dscv_dev>(env, cls, fp_discover_devs);

    if (NULL == dscv_dev_list) {
        err("Can not access the list of discovered devices - " LOCATION_INFO ", ", FUNC_DESC);

        if (env->ExceptionCheck()) {
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, cls,
                                       "Can not access the list of discovered devices", FUNC_DESC, LOCATION_INFO);
        } else {
            Util::throwNativeException(env, cls,
                                       "Can not access the list of discovered devices", FUNC_DESC, LOCATION_INFO);
        }

        return NULL;
    }

    return dscv_dev_list;
}
