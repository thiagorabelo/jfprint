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

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_dev_close(*dev);
    delete dev;

    log("Running ", FUNC_DESC);
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1getDriver
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_driver *driver = fp_dev_get_driver(*dev);

    if (Util::checkAndThrowException(env, driver, obj, "Can not retrieve driver", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    jobject jdriver = Util::newInstance(env, "Ljfprint/Driver;");

    if (Util::checkAndThrowException(env, jdriver, obj,
                                     "Can not instantiate Ljfprint/Driver;", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_driver **pdriver = new fp_driver*;
    *pdriver = driver;

    // Returned value does not need be freed
    Util::setPointerAddress(env, jdriver, "pointer", pdriver, sizeof(fp_driver*));

    if (Util::checkAndThrowException(env, obj, "Can not set Driver 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        delete pdriver;
        return NULL;
    }

    return jdriver;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getNumEnrollStages
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_nr_enroll_stages(*dev);
}


JNIEXPORT jlong JNICALL Java_jfprint_Device_fp_1getDevType
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return static_cast<jlong>(fp_dev_get_devtype(*dev));
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsPrintData
  (JNIEnv *env, jobject obj, jobject printData)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, printData, "pointer"));

    if (Util::checkAndThrowException(env, data, obj, "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_print_data(*dev, *data) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsDiscoveredPrint
  (JNIEnv *env, jobject obj, jobject discoveredPrint)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev,  obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));

    if (Util::checkAndThrowException(env, discovered_print, obj,
                                     "Can not access DiscoveredPrint 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_dscv_print(*dev, *discovered_print) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsImaging
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_imaging(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsIdentification
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_identification(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1imgCapture
  (JNIEnv *env, jobject obj, jboolean unconditional)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

    if (Util::checkAndThrowException(env, jimg, obj, "Can not instantiate Ljfprint/Img;", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_img *img = NULL;
    int ret = fp_dev_img_capture(*dev, unconditional, &img);

    if (ret != 0) {
        if (NULL != img) {
            fp_img_free(img);
        }

        log("Can not capture image from device. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);
        Util::throwCodeError(env, ret);

        return NULL;
    }

    fp_img **p_img = new fp_img*;
    *p_img = img;

    Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

    if (Util::checkAndThrowException(env, obj, "Can not set Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        delete p_img;
        return NULL;
    }

    return jimg;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgWidth
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_img_width(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgHeight
  (JNIEnv *env, jobject obj)
{
    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_img_height(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFingerImg
  (JNIEnv *env, jobject obj, jobject printDataWrapper, jobject imgWrapper)
{
    jclass wrapperPrintDataCls = env->GetObjectClass(printDataWrapper);
    if (Util::checkAndThrowException(env, wrapperPrintDataCls, obj,
                                     "Can not access Class<Wrapper<PrintData>>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (Util::checkAndThrowException(env, wrapperImgCls, obj,
                                     "Can not access Class<Wrapper<Img>>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperPrintDataObjField = env->GetFieldID(wrapperPrintDataCls, "obj", "Ljfprint/base/NativeResource;");
    if (Util::checkAndThrowException(env, wrapperPrintDataObjField, obj,
                                     "Can not access 'obj' field in Wrapper<PrintData>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", "Ljfprint/base/NativeResource;");
    if (Util::checkAndThrowException(env, wrapperImgObjField, obj,
                                     "Can not access 'obj' field in Wrapper<Img>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_print_data **enrolled_print = new fp_print_data*;
    fp_img **img = new fp_img*;

    *enrolled_print = NULL;
    *img = NULL;

    int ret = fp_enroll_finger_img(*dev, enrolled_print, img);

    if (ret < 0) {
        log("Can not enroll finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

        if (NULL != *enrolled_print) {
            fp_print_data_free(*enrolled_print);
        }

        if (NULL != *img) {
            fp_img_free(*img);
        }

        delete enrolled_print;
        delete img;

        Util::throwCodeError(env, ret);

        return 0;
    }

    if (NULL != *img) {
        jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

        if (Util::checkAndThrowException(env, jimg, obj,
                                         "Can not instantiate Ljfprint/Img;", LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            delete img;

            return 0;
        }

        Util::setPointerAddress(env, jimg, "pointer", img, sizeof(fp_img*));

        if (Util::checkAndThrowException(env, obj, "Can not set Ljfprint/Img; 'pointer'", LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            delete img;

            return 0;
        }

        env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);

        if (Util::checkAndThrowException(env, obj,
                                         "Can not set 'obj' field in Wrapper<Img>", LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }
    } else {
        delete img;
    }

    if (NULL != *enrolled_print) {
        jobject jprintData = Util::newInstance(env, "Ljfprint/PrintData;");

        if (Util::checkAndThrowException(env, jprintData, obj,
                                         "Can not instantiate Ljfprint/PrintData;", LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        Util::setPointerAddress(env, jprintData, "pointer", enrolled_print, sizeof(fp_print_data*));

        if (Util::checkAndThrowException(env, obj,
                                         "Can not set Ljfprint/PrintData; 'pointer'", LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        env->SetObjectField(printDataWrapper, wrapperPrintDataObjField, jprintData);

        if (Util::checkAndThrowException(env, obj,
                                         "Can not set 'obj' field in Wrapper<PrintData>", LOCATION_INFO, FUNC_DESC)) {

            // enrolled_print will be deletede when PrintData.close() gonna called
            // img will be deletede when Img.close() gonna called

            return 0;
        }

    } else {
        delete enrolled_print;
    }

    return ret;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1verifyFingerImg
  (JNIEnv *env, jobject obj, jobject enrolled_print, jobject imgWrapper)
{
    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (Util::checkAndThrowException(env, wrapperImgCls, obj,
                                     "Can not access Class<Wrapper<Img>>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", "Ljfprint/base/NativeResource;");
    if (Util::checkAndThrowException(env, wrapperImgCls, obj,
                                     "Can not access 'obj' field in Wrapper<Img>", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, "Can not access Device 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, enrolled_print, "pointer"));

    if (Util::checkAndThrowException(env, data, obj, "Can not access PrintData 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_img *img = NULL;

    int ret = fp_verify_finger_img(*dev, *data, &img);

    if (ret < 0) {
        log("Can not verify finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

        if (NULL != img) {
            fp_img_free(img);
        }

        Util::throwCodeError(env, ret);

        return 0;
    }

    jobject jimg = Util::newInstance(env, "Ljfprint/Img;");

    if (Util::checkAndThrowException(env, jimg, obj, "Can not instantiate Ljfprint/Img;", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_img **p_img = new fp_img*;
    *p_img = img;

    Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

    if (Util::checkAndThrowException(env, obj, "Can not set Ljfprint/Img; 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        delete p_img;
        return 0;
    }

    env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);

    if (Util::checkAndThrowException(env, obj, "Can not set 'obj' field in Wrapper<Img>", LOCATION_INFO, FUNC_DESC)) {
        // p_img will be deletede when Img.close gonna called
        return 0;
    }

    return ret;
}
