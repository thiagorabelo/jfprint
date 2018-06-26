#include "jfprint_DiscoveredDevice.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredDevice_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDevice_open
  (JNIEnv *env, jobject obj)
{
    fp_dscv_dev **p_discovered_dev = reinterpret_cast<fp_dscv_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    if (NULL == p_discovered_dev) {
        log("Can not retrieve discovered devices from 'pointer' field. " LOCATION_INFO);
        Util::throwException(env, "Can not retrieve discovered devices from 'pointer' field. " LOCATION_INFO);
        return NULL;
    }

    fp_dev *dev = fp_dev_open(*p_discovered_dev);
    if (NULL == dev) {
        log("Could not open device. " LOCATION_INFO);
        Util::throwException(env, "Could not open device. " LOCATION_INFO);
    }

    fp_dev **pdev = new fp_dev*;
    *pdev = dev;

    jobject device = Util::newInstance(env, "Ljfprint/Device;");
    Util::setPointerAddress(env, device, "pointer", pdev, sizeof(fp_dev*));

    return device;
}
