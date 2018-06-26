#include "jfprint_Device.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Device_nativeClose
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (NULL == dev) {
        log("Can not access device 'pointer'. ", LOCATION_INFO);
        Util::throwException(env, "Can not access device 'pointer' in function Java_jfprint_Device_nativeClose.");
        return;
    }

    fp_dev_close(*dev);
    delete dev;

    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_getDriver
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_driver *driver = fp_dev_get_driver(*dev);
    fp_driver **pdriver = new fp_driver*;

    *pdriver = driver;

    jobject jdriver = Util::newInstance(env, "Ljfprint/Driver;");

    // Returned value does not need be freed
    Util::setPointerAddress(env, jdriver, "pointer", pdriver, sizeof(fp_driver*));

    return jdriver;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_getNumEnrollStages
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_dev_get_nr_enroll_stages(*dev);
}


JNIEXPORT jlong JNICALL Java_jfprint_Device_getDevType
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<jlong>(fp_dev_get_devtype(*dev));
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsPrintData
  (JNIEnv *env, jobject obj, jobject printData)
{
    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, printData, "pointer"));
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    return fp_dev_supports_print_data(*dev, *data) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsDiscoveredPrint
  (JNIEnv *env, jobject obj, jobject discoveredPrint)
{
    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    return fp_dev_supports_dscv_print(*dev, *discovered_print) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsImaging
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_dev_supports_imaging(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsIdentification
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_dev_supports_identification(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_imgCapture
  (JNIEnv *env, jobject obj, jboolean unconditional)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_img *img = NULL;

    int ret = fp_dev_img_capture(*dev, unconditional, &img);

    if (ret != 0) {
        if (NULL != img) {
            fp_img_free(img);
        }

        log("Can not capture image from device. Code error: ", ret, ". ", LOCATION_INFO);
        Util::throwException(env, "Can not capture image from device. " LOCATION_INFO);

        return NULL;
    }

    jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

    fp_img **p_img = new fp_img*;
    *p_img = img;

    Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

    return jimg;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_getImgWidth
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_dev_get_img_width(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_getImgHeight
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    return fp_dev_get_img_height(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_enrollFingerImg
  (JNIEnv *env, jobject obj, jobject printDataWrapper, jobject imgWrapper)
{
    jclass wrapperPrintDataCls = env->GetObjectClass(printDataWrapper);
    if (NULL == wrapperPrintDataCls) {
        log("Can not access wrapperPrintDataCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperPrintDataCls. " LOCATION_INFO);
    }

    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (NULL == wrapperImgCls) {
        log("Can not access wrapperImgCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperImgCls. " LOCATION_INFO);
    }

    jfieldID wrapperPrintDataObjField = env->GetFieldID(wrapperPrintDataCls, "obj", "Ljava/lang/Object;");
    if (NULL == wrapperPrintDataObjField) {
        log("Can not access wrapperPrintDataCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperPrintDataCls. " LOCATION_INFO);
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", "Ljava/lang/Object;");
    if (NULL == wrapperImgObjField) {
        log("Can not access wrapperImgCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperImgCls. " LOCATION_INFO);
    }

    // TODO: Rever esta parte
    fp_print_data **enrolled_print = new fp_print_data*;
    fp_img **img = new fp_img*; // TODO: Sobretudo essa
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    // TODO: E essa
    int ret = fp_enroll_finger_img(*dev, enrolled_print, img);

    if (NULL != *img) {
        jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

        Util::setPointerAddress(env, jimg, "pointer", img, sizeof(fp_img*));
        env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);
    } else {
        delete img;
    }

    if (NULL != *enrolled_print) {
        jobject jprintData = Util::newInstance(env, "Ljfprint/PrintData;");

        Util::setPointerAddress(env, jprintData, "pointer", enrolled_print, sizeof(fp_print_data*));
        env->SetObjectField(printDataWrapper, wrapperPrintDataObjField, jprintData);
    } else {
        delete enrolled_print;
    }

    return ret;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_verifyFingerImg
  (JNIEnv *env, jobject obj, jobject enrolled_print, jobject imgWrapper)
{
    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (NULL == wrapperImgCls) {
        log("Can not access wrapperImgCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperImgCls. " LOCATION_INFO);
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", "Ljava/lang/Object;");
    if (NULL == wrapperImgObjField) {
        log("Can not access wrapperImgCls. " LOCATION_INFO);
        return Util::throwException(env, "Can not access wrapperImgCls. " LOCATION_INFO);
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, enrolled_print, "pointer"));
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_img *img = NULL;

    int ret = fp_verify_finger_img(*dev, *data, &img);

    if (ret < 0) {
        // wrapper img ficará com null
        return ret;
    }

    jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

    fp_img **p_img = new fp_img*;
    *p_img = img;

    Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

    return ret;
}
