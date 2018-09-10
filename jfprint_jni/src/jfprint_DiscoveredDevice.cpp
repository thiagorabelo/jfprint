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
    log("Running ", FUNC_DESC);

    fp_dscv_dev **p_discovered_dev = reinterpret_cast<fp_dscv_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    if (Util::checkAndThrowException(env, p_discovered_dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_dev *dev = fp_dev_open(*p_discovered_dev);

    if (NULL == dev) {
        log(UNABLE_OPEN_DEVICE);
        fp_dev_close(dev);
        Util::throwOperationError(env, UNABLE_OPEN_DEVICE);
        return NULL;
    }

    jobject device = Util::newInstance(env, CLASS_DEVICE);

    if (Util::checkAndThrowException(env, device, obj,
                                     CAN_NOT_INSTANTIATE(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        fp_dev_close(dev);
        return NULL;
    }

    fp_dev **pdev = new fp_dev*;
    *pdev = dev;

    Util::setPointerAddress(env, device, "pointer", pdev, sizeof(fp_dev*));

    if (Util::checkAndThrowException(env, obj, CAN_NOT_SET_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        delete pdev;
        fp_dev_close(dev);
        return NULL;
    }

    return device;
}
