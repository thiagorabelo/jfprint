
#include "jfprint_PrintData.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_PrintData_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, print_data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_print_data_free(*print_data);
    delete print_data;
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_PrintData_fp_1getData
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, print_data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    unsigned char *data = NULL;
    size_t array_size = fp_print_data_get_data(*print_data, &data);

    if (NULL == data || array_size == 0) {
        log(UNABLE_GET_PRINT_DATA " " LOCATION_INFO ", ", FUNC_DESC);

        Util::throwOperationError(env, UNABLE_GET_PRINT_DATA);

        return NULL;
    }

    jbyteArray byteArray = env->NewByteArray(static_cast<jsize>(array_size));

    if (Util::checkAndThrowException(env, byteArray,
                                     CAN_NOT_INSTANTIATE("Java byte array"), LOCATION_INFO, FUNC_DESC)) {
        free(data);
        return NULL;
    }

    env->SetByteArrayRegion(byteArray, 0, static_cast<jsize>(array_size), reinterpret_cast<jbyte*>(data));

    if (Util::checkAndThrowException(env, obj, UNABLE_POPULATE_BYTE_ARRAY, LOCATION_INFO, FUNC_DESC)) {
        free(data);
        return NULL;
    }

    return byteArray;
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromData
  (JNIEnv *env, jclass cls, jbyteArray jdata)
{
    log("Running ", FUNC_DESC);

    jsize jArraySize = env->GetArrayLength(jdata);

    if (jArraySize <= 0) {
        log("Array is empty. " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, "Array is empty");
        return NULL;
    } else if (env->ExceptionCheck()) { // Possible NullPointerException
        return NULL;
    }

    jbyte *buf = new jbyte[jArraySize];
    env->GetByteArrayRegion(jdata, 0, jArraySize, buf);

    if (env->ExceptionCheck()) {
        err("ArrayIndexOutOfBoundsException on copy of jByteArray. " LOCATION_INFO ", ", FUNC_DESC);
        delete [] buf;
        return NULL;
    }

    fp_print_data *print_data = fp_print_data_from_data(reinterpret_cast<unsigned char*>(buf),
                                                        static_cast<size_t>(jArraySize));
    if (NULL == print_data) {
        log(UNABLE_GET_PRINT_DATA " " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, UNABLE_GET_PRINT_DATA);
        fp_print_data_free(print_data);
        delete [] buf;
        return NULL;
    }

    delete [] buf;

    jobject jprintData = Util::newInstance(env, cls);

    if (Util::checkAndThrowException(env, jprintData, cls,
                                     CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        return NULL;
    }

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        delete p_print_data;
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1dataSave
  (JNIEnv *env, jobject obj, jint finger)
{
    log("Running ", FUNC_DESC);

    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, print_data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_print_data_save(*print_data, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1dataLoad
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));

    if (Util::checkAndThrowException(env, dev, cls, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_print_data *print_data = NULL;

    int ret = fp_print_data_load(*dev, static_cast<fp_finger>(finger), &print_data);

    if (ret != 0) {
        log(CAN_NOT_LOAD_PRINT_DATA " - " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, CAN_NOT_LOAD_PRINT_DATA);
        return NULL;
    }


    jobject jprintData = Util::newInstance(env, cls);

    if (Util::checkAndThrowException(env, jprintData, cls,
                                     CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        return NULL;
    }

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        delete p_print_data;
        fp_print_data_free(print_data);
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1delete
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));

    if (Util::checkAndThrowException(env, dev, cls,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_print_data_delete(*dev, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromDiscoveredPrint
  (JNIEnv *env, jclass cls, jobject discoveredPrint)
{
    log("Running ", FUNC_DESC);

    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));

    if (Util::checkAndThrowException(env, discovered_print, cls,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_print_data *data = NULL;

    int ret = fp_print_data_from_dscv_print(*discovered_print, &data);

    if (0 != ret) {
        log("Error while obtaining print data from discovered print. " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, "Error while obtaining print data from discovered print");
        return NULL;
    }

    jobject jprintData = Util::newInstance(env, cls);

    if (Util::checkAndThrowException(env, jprintData, cls,
                                     CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(data);
        return NULL;
    }

    fp_print_data **p_data = new fp_print_data*;
    *p_data = data;

    Util::setPointerAddress(env, jprintData, "pointer", p_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        delete p_data;
        fp_print_data_free(data);
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDriverId
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_driver_id(*print_data));

    long id = Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_driver_id, 0L);

    if (Util::checkAndThrowException(env, obj, CAN_NOT_RETRIEVE_DRIVER_ID, LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return id;
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_devtype(*print_data));

    long devType = Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_devtype, 0L);

    if (Util::checkAndThrowException(env, obj, CAN_NOT_RETRIEVE_DRIVER_TYPE, LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return devType;
}
