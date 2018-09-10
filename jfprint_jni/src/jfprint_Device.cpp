#include "jfprint_Device.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Device_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_dev_close(*dev);
    delete dev;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1getDriver
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_driver *driver = fp_dev_get_driver(*dev);

    if (Util::checkAndThrowException(env, driver, obj,
                                     CAN_NOT_RETRIEVE_POINTER("driver"), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    jobject jdriver = Util::newInstance(env, CLASS_DRIVER);

    if (Util::checkAndThrowException(env, jdriver, obj,
                                     CAN_NOT_INSTANTIATE(CLASS_DRIVER), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_driver **pdriver = new fp_driver*;
    *pdriver = driver;

    // Returned value does not need be freed
    Util::setPointerAddress(env, jdriver, "pointer", pdriver, sizeof(fp_driver*));

    if (Util::checkAndThrowException(env, obj,
                                     CAN_NOT_SET_POINTER(CLASS_DRIVER), LOCATION_INFO, FUNC_DESC)) {
        delete pdriver;
        return NULL;
    }

    return jdriver;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getNumEnrollStages
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_nr_enroll_stages(*dev);
}


JNIEXPORT jlong JNICALL Java_jfprint_Device_fp_1getDevType
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0L;
    }

    return static_cast<jlong>(fp_dev_get_devtype(*dev));
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsPrintData
  (JNIEnv *env, jobject obj, jobject printData)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, printData, "pointer"));

    if (Util::checkAndThrowException(env, data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_print_data(*dev, *data) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsDiscoveredPrint
  (JNIEnv *env, jobject obj, jobject discoveredPrint)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev,  obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    fp_dscv_print **discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(
        env,discoveredPrint, "pointer"));

    if (Util::checkAndThrowException(env, discovered_print, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_dscv_print(*dev, *discovered_print) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsImaging
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_imaging(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsIdentification
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return false;
    }

    return fp_dev_supports_identification(*dev) != 0 ? 1 : 0;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1imgCapture
  (JNIEnv *env, jobject obj, jboolean unconditional)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    jobject jimg = Util::newInstance(env, CLASS_IMG);

    if (Util::checkAndThrowException(env, jimg, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
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

    if (Util::checkAndThrowException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
        delete p_img;
        return NULL;
    }

    return jimg;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgWidth
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_img_width(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgHeight
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return fp_dev_get_img_height(*dev);
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFingerImg
  (JNIEnv *env, jobject obj, jobject printDataWrapper, jobject imgWrapper)
{
    log("Running ", FUNC_DESC);

    jclass wrapperPrintDataCls = env->GetObjectClass(printDataWrapper);
    if (Util::checkAndThrowException(env, wrapperPrintDataCls, obj,
                                     CAN_NOT_RETRIEVE_WRAPPER_CLASS("PrintData"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (Util::checkAndThrowException(env, wrapperImgCls, obj,
                                     CAN_NOT_RETRIEVE_WRAPPER_CLASS("Img"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperPrintDataObjField = env->GetFieldID(wrapperPrintDataCls, "obj", CLASS_NATIVE_RESOURCE);
    if (Util::checkAndThrowException(env, wrapperPrintDataObjField, obj,
                                     CAN_NOT_ACCESS_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", CLASS_NATIVE_RESOURCE);
    if (Util::checkAndThrowException(env, wrapperImgObjField, obj,
                                     CAN_NOT_ACCESS_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
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
        jobject jimg = Util::newInstance(env, CLASS_IMG);

        if (Util::checkAndThrowException(env, jimg, obj,
                                         CAN_NOT_INSTANTIATE(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            delete img;

            return 0;
        }

        Util::setPointerAddress(env, jimg, "pointer", img, sizeof(fp_img*));

        if (Util::checkAndThrowException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            delete img;

            return 0;
        }

        env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);

        if (Util::checkAndThrowException(env, obj,
                                         CAN_NOT_SET_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }
    } else {
        delete img;
    }

    if (NULL != *enrolled_print) {
        jobject jprintData = Util::newInstance(env, CLASS_PRINT_DATA);

        if (Util::checkAndThrowException(env, jprintData, obj,
                                         CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        Util::setPointerAddress(env, jprintData, "pointer", enrolled_print, sizeof(fp_print_data*));

        if (Util::checkAndThrowException(env, obj,
                                         CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        env->SetObjectField(printDataWrapper, wrapperPrintDataObjField, jprintData);

        if (Util::checkAndThrowException(env, obj,
                                         CAN_NOT_SET_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC)) {
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
    log("Running ", FUNC_DESC);

    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (Util::checkAndThrowException(env, wrapperImgCls, obj,
                                     CAN_NOT_RETRIEVE_WRAPPER_CLASS("Img"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", CLASS_NATIVE_RESOURCE);
    if (Util::checkAndThrowException(env, wrapperImgObjField, obj,
                                     CAN_NOT_ACCESS_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, enrolled_print, "pointer"));

    if (Util::checkAndThrowException(env, data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
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

    jobject jimg = Util::newInstance(env, CLASS_IMG);

    if (Util::checkAndThrowException(env, jimg, obj, CAN_NOT_INSTANTIATE(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
        fp_img_free(img);
        return 0;
    }

    fp_img **p_img = new fp_img*;
    *p_img = img;

    Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

    if (Util::checkAndThrowException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC)) {
        delete p_img;
        fp_img_free(img);
        return 0;
    }

    env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);

    if (Util::checkAndThrowException(env, obj, CAN_NOT_SET_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC)) {
        // p_img will be deletede when Img.close gonna called
        return 0;
    }

    return ret;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1identifyFingerImg
  (JNIEnv *env, jobject obj, jobject imgWrapper, jobjectArray printGallery)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_print_data **print_data_list = Util::jobjectArrayToCNULLTerminatedArray<fp_print_data>(env, printGallery);
    size_t offset;
    fp_img *img = NULL;
    int ret;

    ret = fp_identify_finger_img(*dev, print_data_list, &offset, NULL == imgWrapper ? NULL : &img);

    if (ret < 0) {
        delete print_data_list;

        if (NULL != img) {
            fp_img_free(img);
        }

        Util::throwCodeError(env, ret);

        return NULL;
    }

    if (NULL != img) {
        int status;

        jobject jimg = Util::newNativeResource(env, CLASS_IMG, img, &status);

        if (status != Util::InstanciationStatus::INSTANTIATION_OK) {
            const char *msg_error;

            if (status == Util::InstanciationStatus::INSTANTIATION_ERROR) {
                msg_error = CAN_NOT_INSTANTIATE(CLASS_IMG);
            } else { // (status == Util::InstanciationStatus::INSTANTIATION_SET_POINTER_ERROR) {
                msg_error = CAN_NOT_SET_POINTER(CLASS_IMG);
            }

            Util::checkAndThrowException(env, obj, msg_error, LOCATION_INFO, FUNC_DESC);

            delete print_data_list;
            if (NULL != img) {
                fp_img_free(img);
            }

            return NULL;
        }

        Util::setWrapperObj(env, imgWrapper, jimg, &status);

        if (status != Util::SetWrapperStatus::WRAPPER_OK) {
            const char *msg_error;

            if (status == Util::SetWrapperStatus::WRAPPER_GET_CLASS_ERROR) {
                msg_error = CAN_NOT_RETRIEVE_WRAPPER_CLASS("Img");
            } else if (status == Util::SetWrapperStatus::WRAPPER_GET_FIELD_ID_ERROR) {
                msg_error = CAN_NOT_ACCESS_OBJ_IN_WRAPPER("Img");
            } else { // (status == Util::SetWrapperStatus::WRAPPER_SET_FIELD_ERROR)
                msg_error = CAN_NOT_SET_OBJ_IN_WRAPPER("Img");
            }

            Util::checkAndThrowException(env, obj, msg_error, LOCATION_INFO, FUNC_DESC);

            delete print_data_list;
            // img well be freed on Img.close()
            return NULL;
        }
    }

    jobject result;

    if (FP_VERIFY_MATCH == ret) {
        fp_print_data *print_data = print_data_list[offset];

        int status;
        jobject jprintData = Util::newNativeResource(env, CLASS_PRINT_DATA, print_data, &status);

        if (status != Util::InstanciationStatus::INSTANTIATION_OK) {
            const char *msg_error;

            if (status == Util::InstanciationStatus::INSTANTIATION_ERROR) {
                msg_error = CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA);
            } else { // (status == Util::InstanciationStatus::INSTANTIATION_SET_POINTER_ERROR)
                msg_error = CAN_NOT_SET_POINTER(CLASS_PRINT_DATA);
            }

            delete print_data_list;
            // img well be freed on Img.close()
        }

        result = Util::newResultTuple(env, jprintData, ret);
    } else {
        result = Util::newResultTuple(env, ret);
    }

    delete print_data_list;

    return result;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFinger
  (JNIEnv *env, jobject obj, jobject printDataWrapper)
{
    log("Running ", FUNC_DESC);

    jclass wrapperPrintDataCls = env->GetObjectClass(printDataWrapper);
    if (Util::checkAndThrowException(env, wrapperPrintDataCls, obj,
                                     CAN_NOT_RETRIEVE_WRAPPER_CLASS("PrintData"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    jfieldID wrapperPrintDataObjField = env->GetFieldID(wrapperPrintDataCls, "obj", CLASS_NATIVE_RESOURCE);
    if (Util::checkAndThrowException(env, wrapperPrintDataObjField, obj,
                                     CAN_NOT_ACCESS_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_print_data **enrolled_print = new fp_print_data*;
    *enrolled_print = NULL;

    int ret = fp_enroll_finger(*dev, enrolled_print);

    if (ret < 0) {
        log("Can not enroll finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

        if (NULL != *enrolled_print) {
            fp_print_data_free(*enrolled_print);
        }

        delete enrolled_print;
        Util::throwCodeError(env, ret);

        return 0;
    }

    if (NULL != *enrolled_print) {
        jobject jprintData = Util::newInstance(env, CLASS_PRINT_DATA);

        if (Util::checkAndThrowException(env, jprintData, obj,
                                         CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;

            return 0;
        }

        Util::setPointerAddress(env, jprintData, "pointer", enrolled_print, sizeof(fp_print_data*));

        if (Util::checkAndThrowException(env, obj,
                                         CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
            delete enrolled_print;

            return 0;
        }

        env->SetObjectField(printDataWrapper, wrapperPrintDataObjField, jprintData);

        if (Util::checkAndThrowException(env, obj,
                                         CAN_NOT_SET_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC)) {
            // enrolled_print will be deletede when PrintData.close() gonna called

            return 0;
        }

    } else {
        delete enrolled_print;
    }

    return ret;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1verifyFinger
  (JNIEnv *env, jobject obj, jobject enrolled_print) // enroledPrintData)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_print_data **data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, enrolled_print, "pointer"));

    if (Util::checkAndThrowException(env, data, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    int ret = fp_verify_finger(*dev, *data);

    if (ret < 0) {
        log("Can not verify finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);
        Util::throwCodeError(env, ret);
        return 0;
    }

    return ret;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1identifyFinger
  (JNIEnv *env, jobject obj, jobjectArray printGallery)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, dev, obj,
                                     CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    fp_print_data **print_data_list = Util::jobjectArrayToCNULLTerminatedArray<fp_print_data>(env, printGallery);
    size_t offset;
    int ret;

    ret = fp_identify_finger(*dev, print_data_list, &offset);

    if (ret < 0) {
        delete print_data_list;
        Util::throwCodeError(env, ret);
        return NULL;
    }

    jobject result;

    if (FP_VERIFY_MATCH == ret) {
        fp_print_data *print_data = print_data_list[offset];

        int status;
        jobject jprintData = Util::newNativeResource(env, CLASS_PRINT_DATA, print_data, &status);

        if (status != Util::InstanciationStatus::INSTANTIATION_OK) {
            const char *msg_error;

            if (status == Util::InstanciationStatus::INSTANTIATION_ERROR) {
                msg_error = CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA);
            } else { // (status == Util::InstanciationStatus::INSTANTIATION_SET_POINTER_ERROR)
                msg_error = CAN_NOT_SET_POINTER(CLASS_PRINT_DATA);
            }

            delete print_data_list;
            // img well be freed on Img.close()
        }

        result = Util::newResultTuple(env, jprintData, ret);
    } else {
        result = Util::newResultTuple(env, ret);
    }

    delete print_data_list;

    return result;
}
