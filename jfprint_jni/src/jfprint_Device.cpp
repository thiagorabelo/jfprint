#include "jfprint_Device.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


// TODO: Replace h.newInstance(...); h.setPointer(...); for h.nativeResource(...); when possible.


JNIEXPORT void JNICALL Java_jfprint_Device_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        fp_dev_close(*dev);
        delete dev;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1getDriver
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    fp_driver **p_driver;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);

        fp_driver *driver = fp_dev_get_driver(*dev);

        if (NULL == driver) {
            log("Can not retrieve fp_driver");
            return NULL;
        }

        jobject jdriver = h.newInstance(CLASS_DRIVER);

        p_driver = new fp_driver*;
        *p_driver = driver;

        h.setPointer(jdriver, p_driver, sizeof(fp_driver*));

        return jdriver;

    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    } catch (JNINewInstanceError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    } catch (JNISetPointerError& ex) {
        delete p_driver;
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);

        return NULL;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getNumEnrollStages
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return fp_dev_get_nr_enroll_stages(*dev);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jlong JNICALL Java_jfprint_Device_fp_1getDevType
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return static_cast<jlong>(fp_dev_get_devtype(*dev));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0L;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsPrintData
  (JNIEnv *env, jobject obj, jobject printData)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        fp_print_data **data = h.getPointer<fp_print_data>(printData);

        return fp_dev_supports_print_data(*dev, *data) != 0;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsDiscoveredPrint
  (JNIEnv *env, jobject obj, jobject discoveredPrint)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        fp_dscv_print **discovered_print = h.getPointer<fp_dscv_print>(discoveredPrint);

        return fp_dev_supports_dscv_print(*dev, *discovered_print) != 0;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsImaging
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return fp_dev_supports_imaging(*dev) != 0 ? 1 : 0;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jboolean JNICALL Java_jfprint_Device_fp_1supportsIdentification
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return fp_dev_supports_identification(*dev) != 0 ? 1 : 0;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return false;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1imgCapture
  (JNIEnv *env, jobject obj, jboolean unconditional)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_img **p_img;
    fp_img *img;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        jobject jimg = h.newInstance(CLASS_IMG);

        img = NULL;
        int ret = fp_dev_img_capture(*dev, unconditional, &img);

        if (ret != 0) {
            if (NULL != img) {
                fp_img_free(img);
            }

            log("Can not capture image from device. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);
            Util::throwCodeError(env, ret);

            return NULL;
        }

        p_img = new fp_img*;
        *p_img = img;

        Util::setPointerAddress(env, jimg, "pointer", p_img, sizeof(fp_img*));

        return jimg;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    } catch (JNINewInstanceError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    } catch (JNISetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);

        delete p_img;
        fp_img_free(img);

        return NULL;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgWidth
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return fp_dev_get_img_width(*dev);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1getImgHeight
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        return fp_dev_get_img_height(*dev);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFingerImg
  (JNIEnv *env, jobject obj, jobject printDataWrapper, jobject imgWrapper)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    int ret;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);

        fp_print_data *enrolled_print = NULL;
        fp_img *img = NULL;

        ret = fp_enroll_finger_img(*dev, &enrolled_print, &img);

        if (ret < 0) {
            log("Can not enroll finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

            if (NULL != enrolled_print) {
                fp_print_data_free(enrolled_print);
            }

            if (NULL != img) {
                fp_img_free(img);
            }

            Util::throwCodeError(env, ret);

            return 0;
        }

        jobject jimg = NULL;
        jobject jprintData = NULL;
        fp_print_data **p_enrolled_print = NULL;
        fp_img **p_img = NULL;

        try {
            if (NULL != enrolled_print) {
                jprintData = h.newInstance(CLASS_PRINT_DATA);
                p_enrolled_print = new fp_print_data*;
                *p_enrolled_print = enrolled_print;

                h.setPointer(jprintData, p_enrolled_print, sizeof(fp_print_data*));
                h.setWrapperObj(printDataWrapper, jprintData);
            }

            if (NULL != img) {
                jimg = h.newInstance(CLASS_IMG);
                p_img = new fp_img*;
                *p_img = img;

                h.setPointer(jimg, p_img, sizeof(fp_img*));
                h.setWrapperObj(imgWrapper, jimg);
            }
        } catch (JNISetWrapperObjError& ex) {
            // all resources will be cleaned ween java objects goes collected
            throw;
        } catch (JNIGenericError& ex) {
            if (NULL != p_enrolled_print) {
                delete p_enrolled_print;
                p_enrolled_print = NULL;
            }

            if (NULL != enrolled_print) {
                fp_print_data_free(enrolled_print);
                enrolled_print == NULL;
            }

            if (NULL != p_img) {
                delete p_img;
                p_img = NULL;
            }

            if (NULL != img) {
                fp_img_free(img);
                img = NULL;
            }

            throw;
        }

        return ret;

    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    } catch (JNIGenericError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return ret;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1verifyFingerImg
  (JNIEnv *env, jobject obj, jobject enrolled_print, jobject imgWrapper)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    int ret;
    fp_img **p_img;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        fp_print_data **data = h.getPointer<fp_print_data>(enrolled_print);
        fp_img *img = NULL;

        ret = fp_verify_finger_img(*dev, *data, &img);

        if (ret < 0) {
            log("Can not verify finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

            if (NULL != img) {
                fp_img_free(img);
            }

            Util::throwCodeError(env, ret);

            return 0;
        }

        jobject jimg;

        jimg = h.newInstance(CLASS_IMG);

        p_img = new fp_img*;
        *p_img = img;

        h.setPointer(jimg, p_img, sizeof(fp_img*));
        h.setWrapperObj(imgWrapper, jimg);

        return ret;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    } catch (JNINewInstanceError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    } catch (JNISetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);

        if (NULL != *p_img) {
            fp_img_free(*p_img);
        }

        delete p_img;
        return 0;
    } catch (JNISetWrapperObjError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        // img will be freed and p_img deleted when jimg goes collected
        return 0;
    }

    return ret;
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1identifyFingerImg
  (JNIEnv *env, jobject obj, jobject imgWrapper, jobjectArray printGallery)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_print_data **print_data_list = NULL;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        print_data_list = h.toCNULLTerminatedArray<fp_print_data>(printGallery);

        size_t offset;
        fp_img *img = NULL;
        int ret;

        ret = fp_identify_finger_img(*dev, print_data_list, &offset, &img);

        if (ret < 0) {
            delete [] print_data_list;

            if (NULL != img) {
                fp_img_free(img);
            }

            log("fp_identify_finger_img returned ", ret);
            Util::throwCodeError(env, ret);

            return NULL;
        }

        jobject jimg = NULL;
        fp_img **p_img = NULL;

        try {
            if (NULL != img) {
                jimg = h.newInstance(CLASS_IMG);
                p_img = new fp_img*;
                *p_img = img;

                h.setPointer(jimg, p_img, sizeof(fp_img*));
                h.setWrapperObj(imgWrapper, jimg);
            }
        } catch (JNISetWrapperObjError& ex) {
            // all resources will be cleaned ween java objects goes collected
            throw;
        } catch (JNIGenericError& ex) {
            if (NULL != p_img) {
                delete p_img;
                p_img = NULL;
            }

            if (NULL != img) {
                fp_img_free(img);
                img = NULL;
            }

            throw;
        }

        jobject result;

        if (FP_VERIFY_MATCH == ret) {
            fp_print_data *print_data = print_data_list[offset];
            fp_print_data **p_print_data = NULL;

            try {
                jobject jprintData = h.newInstance(CLASS_PRINT_DATA);

                p_print_data = new fp_print_data*;
                *p_print_data = print_data;

                h.setPointer(jprintData, p_print_data, sizeof(fp_print_data*));
                result = h.newResultTuple(jprintData, ret);
            } catch (JNINewInstanceError& ex) {
                if (NULL != p_print_data) {
                    delete p_print_data;
                    p_print_data = NULL;
                }

                throw;
            } catch (JNISetPointerError& ex) {
                // all resources will be cleaned ween java objects goes collected
                delete p_print_data;
                p_print_data = NULL;

                throw;
            }
        } else {
            result = h.newResultTuple(ret);
        }

        delete print_data_list;

        return result;

    } catch (JNIGenericError& ex) {
        if (NULL != print_data_list) {
            delete print_data_list;
            print_data_list = NULL;
        }

        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1enrollFinger
  (JNIEnv *env, jobject obj, jobject printDataWrapper)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_print_data *enrolled_print = NULL;

    try {

        fp_dev **dev = h.getPointer<fp_dev>(obj);

        int ret = fp_enroll_finger(*dev, &enrolled_print);

        if (ret < 0) {
            log("Can not enroll finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);

            if (NULL != enrolled_print) {
                fp_print_data_free(enrolled_print);
            }

            Util::throwCodeError(env, ret);

            return 0;
        }

        if (NULL != enrolled_print) {
            fp_print_data **p_enrolled_print = NULL;

            try {
                jobject jprintData = h.newInstance(CLASS_PRINT_DATA);

                p_enrolled_print = new fp_print_data*;
                *p_enrolled_print = enrolled_print;

                h.setPointer(jprintData, p_enrolled_print, sizeof(fp_print_data*));
                h.setWrapperObj(printDataWrapper, jprintData);
            } catch (JNISetPointerError& ex) {
                if (NULL != p_enrolled_print) {
                    delete p_enrolled_print;
                    p_enrolled_print = NULL;
                }

                if (NULL != enrolled_print) {
                    fp_print_data_free(enrolled_print);
                    enrolled_print = NULL;
                }
            } catch (JNINewInstanceError& ex) {
                throw;
            } catch (JNISetWrapperObjError& ex) {
                // all resources will be cleaned ween java objects goes collected
                throw;
            }
        }

        return ret;
    } catch (JNIGenericError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Device_fp_1verifyFinger
  (JNIEnv *env, jobject obj, jobject enrolled_print) // enroledPrintData)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        fp_print_data **data = h.getPointer<fp_print_data>(enrolled_print);

        int ret = fp_verify_finger(*dev, *data);

        if (ret < 0) {
            log("Can not verify finger. Code Error: ", ret, ". ", LOCATION_INFO, FUNC_DESC);
            Util::throwCodeError(env, ret);
            return 0;
        }

        return ret;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jobject JNICALL Java_jfprint_Device_fp_1identifyFinger
  (JNIEnv *env, jobject obj, jobjectArray printGallery)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);
    fp_print_data **p_print_data_list = NULL;

    try {
        fp_dev **dev = h.getPointer<fp_dev>(obj);
        p_print_data_list = h.toCNULLTerminatedArray<fp_print_data>(printGallery);

        jobject result = NULL;
        size_t offset = -1;
        int ret = -1;

        ret = fp_identify_finger(*dev, p_print_data_list, &offset);

        if (ret < 0) {
            delete p_print_data_list;
            Util::throwCodeError(env, ret);
            return NULL;
        }

        if (FP_VERIFY_MATCH == ret) {
            fp_print_data *print_data = p_print_data_list[offset];
            jobject jprintData = h.newNativeResource(CLASS_PRINT_DATA, print_data);

            // if exception is throw here, the resources in jprintData
            // will be clenead when the object goes collected.
            result = h.newResultTuple(jprintData, ret);
        } else {
            result = h.newResultTuple(ret);
        }

        delete p_print_data_list;

        return result;
    } catch (JNIGenericError& ex) {
        if (NULL != p_print_data_list) {
            delete p_print_data_list;
        }

        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}
