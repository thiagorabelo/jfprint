
#include "jfprint_PrintData.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_PrintData_nativeClose
  (JNIEnv *env, jobject obj)
{
    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_print_data_free(*print_data);
    delete print_data;

    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_PrintData_fp_1getData
  (JNIEnv *env, jobject obj)
{
    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
    unsigned char *data = NULL;
    size_t array_size = fp_print_data_get_data(*print_data, &data);

    if (NULL == data) {
        err("Can not access print data. " LOCATION_INFO);
        Util::throwNativeException(env, "Can not access print data. ", __PRETTY_FUNCTION__, LOCATION_INFO);
        return NULL;
    }

    jbyteArray byteArray = env->NewByteArray(static_cast<jsize>(array_size));
    env->SetByteArrayRegion(byteArray, 0, static_cast<jsize>(array_size), reinterpret_cast<jbyte*>(data));
    //(byteArray, 0, static_cast<jsize>(array_size), data);

    return byteArray;
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromData
  (JNIEnv *env, jclass cls, jbyteArray jdata)
{
    jsize jArraySize = env->GetArrayLength(jdata);

    if (jArraySize <= 0) {
        err("Array is empty. " LOCATION_INFO);
        Util::throwNativeException(env, "Array is empty. ", __PRETTY_FUNCTION__, LOCATION_INFO);
        return NULL;
    }

    jbyte *buf = new jbyte[jArraySize];
    env->GetByteArrayRegion(jdata, 0, jArraySize, buf);

    if (env->ExceptionCheck()) {
        err("ArrayIndexOutOfBoundsException on copy of jByteArray. " LOCATION_INFO);
        return NULL;
    }

    fp_print_data *print_data = fp_print_data_from_data(reinterpret_cast<unsigned char*>(buf), static_cast<size_t>(jArraySize));
    if (NULL == print_data) {
        err("fp_print_data_from_data returned NULL. " LOCATION_INFO);
        Util::throwNativeException(env, "fp_print_data_from_data returned NULL. ", __PRETTY_FUNCTION__, LOCATION_INFO);
        return NULL;
    }

    delete [] buf;

    jobject jprintData = Util::newInstance(env, cls);

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1dataSave
  (JNIEnv *env, jobject obj, jint finger)
{
    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_print_data_save(*print_data, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1dataLoad
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));
    fp_print_data *print_data;

    int ret = fp_print_data_load(*dev, static_cast<fp_finger>(finger), &print_data);

    if (ret != 0) {
        err("Can not load fp_print_data. " LOCATION_INFO);
        Util::throwNativeException(env, "Can not load fp_print_data. ", __PRETTY_FUNCTION__, LOCATION_INFO);
        return NULL;
    }

    fp_print_data **p_print_data = new fp_print_data*;
    *p_print_data = print_data;

    jobject jprintData = Util::newInstance(env, cls);

    Util::setPointerAddress(env, jprintData, "pointer", p_print_data, sizeof(fp_print_data*));

    return jprintData;
}


JNIEXPORT jint JNICALL Java_jfprint_PrintData_fp_1delete
  (JNIEnv *env, jclass cls, jobject device, jint finger)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, device, "pointer"));
    return fp_print_data_delete(*dev, static_cast<fp_finger>(finger));
}


JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fp_1fromDiscoveredPrint
  (JNIEnv *env, jclass cls, jobject discoveredPrint)
{
    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));
    fp_print_data *data = NULL;

    int ret = fp_print_data_from_dscv_print(*discovered_print, &data);

    if (0 != ret) {
        err("Error while obtaining print data from discovered print. " LOCATION_INFO);
        Util::throwNativeException(env, "Error while obtaining print data from discovered print. ", __PRETTY_FUNCTION__, LOCATION_INFO);
        return NULL;
    }

    jobject jprintData = Util::newInstance(env, cls);

    fp_print_data **p_data = new fp_print_data*;
    *p_data = data;

    Util::setPointerAddress(env, jprintData, "pointer", p_data, sizeof(fp_print_data*));

    return jprintData;
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDriverId
  (JNIEnv *env, jobject obj)
{
//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_driver_id(*print_data));

    return Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_driver_id);
}


JNIEXPORT jlong JNICALL Java_jfprint_PrintData_fp_1getDevtype
  (JNIEnv *env, jobject obj)
{
//    fp_print_data **print_data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, obj, "pointer"));
//    return static_cast<jlong>(fp_print_data_get_devtype(*print_data));

    return Util::applyFuncToPointer<jlong, fp_print_data>(env, obj, "pointer", fp_print_data_get_devtype);
}
