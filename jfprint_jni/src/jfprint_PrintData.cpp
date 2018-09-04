
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
                                     "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_print_data_free(*print_data);
    delete print_data;
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_PrintData_fp_1getData
  (JNIEnv *env, jobject obj)
{
    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, print_data, obj,
                                     "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    unsigned char *data = NULL;
    size_t array_size = fp_print_data_get_data(*print_data, &data);

    if (NULL == data || array_size == 0) {
        log("fp_print_data_from_data returned NULL " LOCATION_INFO ", ", FUNC_DESC);

        Util::throwOperationError(env, "fp_print_data_from_data returned NULL");

        return NULL;
    }

    jbyteArray byteArray = env->NewByteArray(static_cast<jsize>(array_size));

    if (Util::checkAndThrowException(env, byteArray, "Can not instantiate byte array", LOCATION_INFO, FUNC_DESC)) {
        free(data);
        return NULL;
    }

    env->SetByteArrayRegion(byteArray, 0, static_cast<jsize>(array_size), reinterpret_cast<jbyte*>(data));

    if (Util::checkAndThrowException(env, obj, "Unable to populate the byte array", LOCATION_INFO, FUNC_DESC)) {
        free(data);
        return NULL;
    }

    return byteArray;
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromData
  (JNIEnv *env, jclass cls, jbyteArray jdata)
{
    jsize jArraySize = env->GetArrayLength(jdata);

    if (jArraySize <= 0) {
        log("Array is empty. " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, "Array is empty");
        return NULL;
    }

    jbyte *buf = new jbyte[jArraySize];
    env->GetByteArrayRegion(jdata, 0, jArraySize, buf);

    if (env->ExceptionCheck()) {
        err("ArrayIndexOutOfBoundsException on copy of jByteArray. " LOCATION_INFO ", ", FUNC_DESC);
        delete buf;
        return NULL;
    }

    fp_print_data *print_data = fp_print_data_from_data(reinterpret_cast<unsigned char*>(buf),
                                                        static_cast<size_t>(jArraySize));
    if (NULL == print_data) {
        log("fp_print_data_from_data returned NULL. " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, "fp_print_data_from_data returned NULL");
        fp_print_data_free(print_data);
        delete buf;
        return NULL;
    }

    delete [] buf;

    jobject jprintData = Util::newInstance(env, cls);

    if (Util::checkAndThrowException(env, jprintData, cls,
                                     "Can not instantiate PrintData", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        return NULL;
    }

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        delete p_print_data;
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1dataSave
  (JNIEnv *env, jobject obj, jint finger)
{
    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, print_data, obj,
                                     "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_print_data_save(*print_data, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1dataLoad
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));

    if (Util::checkAndThrowException(env, dev, cls, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_print_data *print_data = NULL;

    int ret = fp_print_data_load(*dev, static_cast<fp_finger>(finger), &print_data);

    if (ret != 0) {
        log("Can not load fp_print_data - " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env, "Can not load fp_print_data");
        return NULL;
    }

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    jobject jprintData = Util::newInstance(env, cls);

    if (Util::checkAndThrowException(env, jprintData, cls,
                                     "Can not instantiate PrintData", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        delete p_print_data;
        return NULL;
    }

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(print_data);
        delete p_print_data;
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1delete
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));

    if (Util::checkAndThrowException(env, dev, cls, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_print_data_delete(*dev, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromDiscoveredPrint
  (JNIEnv *env, jclass cls, jobject discoveredPrint)
{
    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));

    if (Util::checkAndThrowException(env, discovered_print, cls,
                                     "Can not access DiscoveredPrint 'pointer'", LOCATION_INFO, FUNC_DESC)) {
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
                                     "Can not instantiate PrintData", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(data);
        return NULL;
    }

    fp_print_data **p_data = new fp_print_data*;
    *p_data = data;

    Util::setPointerAddress(env, jprintData, "pointer", p_data, sizeof(fp_print_data*));

    if (Util::checkAndThrowException(env, cls, "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        fp_print_data_free(data);
        delete p_data;
        return NULL;
    }

    return jprintData;
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDriverId
  (JNIEnv *env, jobject obj)
{
//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_driver_id(*print_data));

    long id = Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_driver_id, 0L);

    if (Util::checkAndThrowException(env, obj, "Can not retrieve driver name", LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return id;
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_devtype(*print_data));

    long devType = Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_devtype, 0L);

    if (Util::checkAndThrowException(env, obj, "Can not retrieve device type", LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return devType;
}
