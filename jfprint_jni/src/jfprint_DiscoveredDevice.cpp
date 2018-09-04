#include "jfprint_DiscoveredDevice.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredDevice_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDevice_fp_1open
  (JNIEnv *env, jobject obj)
{
    fp_dscv_dev **p_discovered_dev = reinterpret_cast<fp_dscv_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    if (NULL == p_discovered_dev) {
        err("Can not access DiscoveredDevice 'pointer' - " LOCATION_INFO, ", ", FUNC_DESC);

        if (env->ExceptionCheck()) {
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, obj,
                                       "Can not access DiscoveredDevice 'pointer'", FUNC_DESC, LOCATION_INFO);
        } else {
            Util::throwNativeException(env, obj,
                                       "Can not access DiscoveredDevice 'pointer'", FUNC_DESC, LOCATION_INFO);
        }

        return NULL;
    }

    fp_dev *dev = fp_dev_open(*p_discovered_dev);

    if (NULL == dev) {
        err("Could not open device - " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwNativeException(env, obj, "Could not open device. ", FUNC_DESC, LOCATION_INFO);
    }

    jobject device = Util::newInstance(env, "Ljfprint/Device;");

    if (NULL == device) {
        err("Can not instantiate Ljfprint/Device; - " LOCATION_INFO ", ", FUNC_DESC);

        if (env->ExceptionCheck()) {
            jthrowable cause = Util::stopExceptionPropagation(env);
            Util::throwNativeException(env, cause, obj, "Can not instantiate Ljfprint/Device;", FUNC_DESC, LOCATION_INFO);
        } else {
            Util::throwNativeException(env, obj, "Can not instantiate Ljfprint/Device;", FUNC_DESC, LOCATION_INFO);
        }

        return NULL;
    }

    fp_dev **pdev = new fp_dev*;
    *pdev = dev;

    Util::setPointerAddress(env, device, "pointer", pdev, sizeof(fp_dev*));

    if (env->ExceptionCheck()) {
        err("Can not set Device 'pointer' - " LOCATION_INFO ", ", FUNC_DESC);

        jthrowable cause = Util::stopExceptionPropagation(env);
        Util::throwNativeException(env, cause, obj, "Can not set Device 'pointer'", FUNC_DESC, LOCATION_INFO);

        delete pdev;

        return NULL;
    }


    return device;
}
