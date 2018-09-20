#include "jfprint_DiscoveredDevice.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_DiscoveredDevice_nativeClose
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);
}


JNIEXPORT jobject JNICALL Java_jfprint_DiscoveredDevice_fp_1open
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_dev *dev = NULL;

    try {
        fp_dscv_dev **p_discovered_dev = h.getPointer<fp_dscv_dev>(obj);
        dev = fp_dev_open(*p_discovered_dev);

        if (NULL == dev) {
            log_debug(UNABLE_OPEN_DEVICE);
            dev == NULL;
            Util::throwOperationError(env, UNABLE_OPEN_DEVICE);
            return NULL;
        }

        jobject device = h.newNativeResource(CLASS_DEVICE, dev);

        return device;
    } catch (JNIGenericError& ex) {
        if (NULL != dev) {
            fp_dev_close(dev);
            dev = NULL;
        }

        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}
