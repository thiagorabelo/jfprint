
#include "jfprint_PrintData.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_PrintData_nativeClose
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_print_data **print_data = h.getPointer<fp_print_data>(obj);
        fp_print_data_free(*print_data);
        delete print_data;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_PrintData_fp_1getData
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    unsigned char *data = NULL;

    try {
        fp_print_data **print_data = h.getPointer<fp_print_data>(obj);

        size_t array_size = fp_print_data_get_data(*print_data, &data);

        // TODO: throw exception if array_size > INT_MAX (#include <climits>)

        if (NULL == data || array_size == 0) {
            log_debug(UNABLE_GET_PRINT_DATA " " LOCATION_INFO ", ", FUNC_DESC);
            Util::throwOperationError(env, UNABLE_GET_PRINT_DATA);
            return NULL;
        }

        jbyteArray byteArray = h.newByteArray(array_size, reinterpret_cast<jbyte*>(data));

        free(data);

        return byteArray;
    } catch (JNIGenericError& ex) {
        if (NULL != data) {
            free(data);
        }

        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);

        return NULL;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromData
  (JNIEnv *env, jclass cls, jbyteArray jdata)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    jbyte *buf;

    try {
        jsize jArraySize = env->GetArrayLength(jdata);
        buf = h.fromByteArray(jdata);

        fp_print_data *print_data = fp_print_data_from_data(reinterpret_cast<unsigned char*>(buf),
                                                            static_cast<size_t>(jArraySize));
        if (NULL == print_data) {
            log_debug(UNABLE_GET_PRINT_DATA " " LOCATION_INFO ", ", FUNC_DESC);
            Util::throwOperationError(env, UNABLE_GET_PRINT_DATA);
            delete [] buf;
            return NULL;
        }

        return h.newNativeResource(cls, print_data);
    } catch (JNIGenericError& ex) {
        if (NULL != buf) {
            delete buf;
        }

        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1dataSave
  (JNIEnv *env, jobject obj, jint finger)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_print_data **print_data = h.getPointer<fp_print_data>(obj);
        return fp_print_data_save(*print_data, static_cast<fp_finger>(finger));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1dataLoad
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_print_data *print_data = NULL;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(device);

        int ret = fp_print_data_load(*dev, static_cast<fp_finger>(finger), &print_data);

        if (ret != 0) {
            log_debug(CAN_NOT_LOAD_PRINT_DATA " - " LOCATION_INFO ", ", FUNC_DESC);
            Util::throwOperationError(env, CAN_NOT_LOAD_PRINT_DATA);
            return NULL;
        }

        return h.newNativeResource(cls, print_data);
    } catch (JNIGenericError& ex) {
        if (NULL != print_data) {
            fp_print_data_free(print_data);
        }

        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1delete
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(device);
        return fp_print_data_delete(*dev, static_cast<fp_finger>(finger));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}

// TODO: A return code of -ENOENT indicates that the file referred to by the discovered
//       print could not be found. Other error codes (both positive and negative) are
//       possible for obscure error conditions (e.g. corruption).
//       HOW CODE MUST HANDLE -ENOENT?
JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromDiscoveredPrint
  (JNIEnv *env, jclass cls, jobject discoveredPrint)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_print_data *data = NULL;

    try {
        fp_dscv_print **discovered_print = h.getPointer<fp_dscv_print>(discoveredPrint);
        int ret = fp_print_data_from_dscv_print(*discovered_print, &data);

        if (0 != ret) {
            log_debug("Error while obtaining print data from discovered print - " LOCATION_INFO ", ", FUNC_DESC);
            Util::throwOperationError(env, "Error while obtaining print data from discovered print");
            return NULL;
        }

        return h.newNativeResource(cls, data);
    } catch (JNIGenericError& ex) {
        if (NULL != data) {
            fp_print_data_free(data);
        }

        Util::throwNativeException(env, cls, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDriverId
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_print_data **print_data = h.getPointer<fp_print_data>(obj);
        return static_cast<jlong>(fp_print_data_get_driver_id(*print_data));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
    log_debug("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_print_data **print_data = h.getPointer<fp_print_data>(obj);
        return static_cast<jlong>(fp_print_data_get_devtype(*print_data));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}
