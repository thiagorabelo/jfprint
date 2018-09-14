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

    try {
        fp_dev **dev = Util::JNIHandler(env).getPointer(obj);
        fp_dev_close(*dev);
        delete dev;
    } catch (JNIPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1getDriver
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev;

    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    fp_driver *driver = fp_dev_get_driver(*dev);

    if (NULL == driver) {
        Util::throwNativeException(env, obj, CAN_NOT_RETRIEVE_POINTER("driver"), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    jobject jdriver;

    try {
        jdriver = Util::newInstance(env, CLASS_DRIVER);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_INSTANTIATE(CLASS_DRIVER), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    fp_driver **pdriver = new fp_driver*;
    *pdriver = driver;

    try {
        // Returned value does not need be freed
        Util::setPointerAddress(env, jdriver, "pointer", pdriver, sizeof(fp_driver*));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_DRIVER), LOCATION_INFO, FUNC_DESC);
        delete pdriver;
        return NULL;
    }

    return jdriver;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getNumEnrollStages
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return fp_dev_get_nr_enroll_stages(*dev);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_Device_fp_1getDevType
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return static_cast<jlong>(fp_dev_get_devtype(*dev));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsPrintData
  (JNIEnv *env, jobject obj, jobject printData)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev;

    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return false;
    }

    fp_print_data **data;

    try {
        data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, printData, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);
        return false;
    }

    return fp_dev_supports_print_data(*dev, *data) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsDiscoveredPrint
  (JNIEnv *env, jobject obj, jobject discoveredPrint)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev;

    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return false;
    }

    fp_dscv_print **discovered_print;

    try {
        discovered_print = reinterpret_cast<fp_dscv_print**>(Util::getPointerAddress(env, discoveredPrint, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj,
                                   CAN_NOT_ACCESS_POINTER(CLASS_DISCOVERED_PRINT), LOCATION_INFO, FUNC_DESC);
        return false;
    }

    return fp_dev_supports_dscv_print(*dev, *discovered_print) != 0;
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsImaging
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return fp_dev_supports_imaging(*dev) != 0 ? 1 : 0;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsIdentification
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return fp_dev_supports_identification(*dev) != 0 ? 1 : 0;
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1imgCapture
  (JNIEnv *env, jobject obj, jboolean unconditional)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev;

    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    jobject jimg;

    try {
        jimg = Util::newInstance(env, CLASS_IMG);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
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

    try {
        Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);

        delete p_img;
        fp_img_free(img);

        return NULL;
    }

    return jimg;
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgWidth
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return fp_dev_get_img_width(*dev);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgHeight
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    try {
        fp_dev **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
        return fp_dev_get_img_height(*dev);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFingerImg
  (JNIEnv *env, jobject obj, jobject printDataWrapper, jobject imgWrapper)
{
    log("Running ", FUNC_DESC);

    jclass wrapperPrintDataCls = env->GetObjectClass(printDataWrapper);
    if (NULL == wrapperPrintDataCls || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_RETRIEVE_WRAPPER_CLASS("PrintData"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    jclass wrapperImgCls = env->GetObjectClass(imgWrapper);
    if (NULL == wrapperImgCls || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_RETRIEVE_WRAPPER_CLASS("Img"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    jfieldID wrapperPrintDataObjField = env->GetFieldID(wrapperPrintDataCls, "obj", CLASS_NATIVE_RESOURCE);
    if (NULL == wrapperPrintDataObjField || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", CLASS_NATIVE_RESOURCE);
    if (NULL == wrapperImgObjField || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    fp_dev **dev;
    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
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
        jobject jimg;

        try {
            jimg = Util::newInstance(env, CLASS_IMG);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_INSTANTIATE(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
            delete enrolled_print;
            delete img;

            return 0;
        }

        try {
            Util::setPointerAddress(env, jimg, "pointer", img, sizeof(fp_img*));
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
            delete enrolled_print;
            delete img;

            return 0;
        }

        try {
            env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_SET_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC);
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }
    } else {
        delete img;
    }

    if (NULL != *enrolled_print) {
        jobject jprintData;

        try {
            jprintData = Util::newInstance(env, CLASS_PRINT_DATA);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        try {
            Util::setPointerAddress(env, jprintData, "pointer", enrolled_print, sizeof(fp_print_data*));
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);
            delete enrolled_print;
            // img will be deletede when Img.close() gonna called

            return 0;
        }

        try {
            env->SetObjectField(printDataWrapper, wrapperPrintDataObjField, jprintData);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_SET_OBJ_IN_WRAPPER("PrintData"), LOCATION_INFO, FUNC_DESC);
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
    if (NULL == wrapperImgCls || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_RETRIEVE_WRAPPER_CLASS("Img"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    jfieldID wrapperImgObjField = env->GetFieldID(wrapperImgCls, "obj", CLASS_NATIVE_RESOURCE);
    if (NULL == wrapperImgObjField || env->ExceptionCheck()) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    fp_dev **dev;
    try {
        **dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    fp_print_data **data;

    try {
        data = reinterpret_cast<fp_print_data**>(Util::getPointerAddress(env, enrolled_print, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);
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


    jobject jimg;

    try {
        jimg = Util::newInstance(env, CLASS_IMG);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, jimg, obj, CAN_NOT_INSTANTIATE(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
        fp_img_free(img);
        return 0;
    }

    fp_img **p_img = new fp_img*;
    *p_img = img;

    try {
        Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
        delete p_img;
        fp_img_free(img);
        return 0;
    }

    try {
        env->SetObjectField(imgWrapper, wrapperImgObjField, jimg);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_SET_OBJ_IN_WRAPPER("Img"), LOCATION_INFO, FUNC_DESC);
        // p_img will be deletede when Img.close gonna called
        return 0;
    }

    return ret;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1identifyFingerImg
  (JNIEnv *env, jobject obj, jobject imgWrapper, jobjectArray printGallery)
{
    log("Running ", FUNC_DESC);

    fp_dev **dev;
    try {
        dev = reinterpret_cast<fp_dev**>(Util::getPointerAddress(env, obj, "pointer"));
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, CAN_NOT_ACCESS_POINTER(CLASS_DEVICE), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    fp_print_data **print_data_list;
    try {
        print_data_list = Util::jobjectArrayToCNULLTerminatedArray<fp_print_data>(env, printGallery);
    } catch (JNIError& ex) {
        Util::throwNativeException(env, obj, "Can not convert list of arguments of PrintData "
                                             "in native null terminated array of pointers",
                                   LOCATION_INFO, FUNC_DESC);
        return NULL;
    }

    size_t offset;
    fp_img *img = NULL;
    int ret;

    ret = fp_identify_finger_img(*dev, print_data_list, &offset, NULL == imgWrapper ? NULL : &img);

    if (ret < 0) {
        delete [] print_data_list;

        if (NULL != img) {
            fp_img_free(img);
        }

        Util::throwCodeError(env, ret);

        return NULL;
    }

    if (NULL != img) {
        jobject jimg;

        try {
            jimg = Util::newInstance(env, CLASS_IMG);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_INSTANTIATE(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
            fp_img_free(img);
            return NULL;
        }

        fp_img **p_img = new fp_img*;
        *p_img = img;

        try {
            Util::setPointerAddress(env, jimg, "pointer", sizeof(fp_img*));
        } catch (JNIError& ex) {
            delete p_img;
            fp_img_free(img);
            Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);

            return NULL;
        }

        // from here p_img will deleted in Img.close()

        jclass imgWrapperClass = env->GetObjectClass(imgWrapper);
        if (NULL == imgWrapperClass || env->ExceptionCheck()) {
            Util::throwNativeException(env, obj, CAN_NOT_RETRIEVE_CLASS(CLASS_WRAPPER), LOCATION_INFO, FUNC_DESC);
            return NULL;
        }

        jfieldID fieldId = env->GetFieldID(imgWrapperClass, "obj", CLASS_WRAPPER);
        if (NULL == fieldId || env->ExceptionCheck()) {
            Util::throwNativeException(env, obj, CAN_NOT_ACCESS_OBJ_IN_WRAPPER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
            return NULL;
        }

        env->SetObjectField(imgWrapper, fieldId, jimg);
        if (env->ExceptionCheck()) {
            Util::throwNativeException(env, obj, CAN_NOT_SET_OBJ_IN_WRAPPER(CLASS_IMG), LOCATION_INFO, FUNC_DESC);
            return NULL;
        }
    }

    jobject result;

    if (FP_VERIFY_MATCH == ret) {
        fp_print_data *print_data = print_data_list[offset];

        jobject jprintData;

        try {
            jprintData = Util::newInstance(env, CLASS_PRINT_DATA);
        } catch (JNIError& ex) {
            Util::throwNativeException(env, obj, CAN_NOT_INSTANTIATE(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);
            return NULL;
        }

        fp_print_data **p_print_data = new fp_print_data*;
        *p_print_data = print_data;

        try {
            Util::setPointerAddress(env, jprintData, "pointer", sizeof(fp_print_data*));
        } catch (JNIError& ex) {
            delete p_print_data;
            Util::throwNativeException(env, obj, CAN_NOT_SET_POINTER(CLASS_PRINT_DATA), LOCATION_INFO, FUNC_DESC);

            return NULL;
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
