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
    if (Util::checkAndThrowException(env, p_discovered_dev, obj,
                                     "Can not access DiscoveredDevice 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_dev *dev = fp_dev_open(*p_discovered_dev);

    if (Util::checkAndThrowException(env, dev, obj, "Could not open device", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    jobject device = Util::newInstance(env, "Ljfprint/Device;");

    if (Util::checkAndThrowException(env, device, obj,
                                     "Can not instantiate Ljfprint/Device;", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_dev **pdev = new fp_dev*;
    *pdev = dev;

    Util::setPointerAddress(env, device, "pointer", pdev, sizeof(fp_dev*));

    if (Util::checkAndThrowException(env, obj, "Can not set Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        delete pdev;
        return NULL;
    }

    return device;
}
