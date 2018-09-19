
#include "jfprint_Img.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Img_nativeClose
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);
        fp_img_free(*p_img);
        delete p_img;
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1getHeight
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);
        return static_cast<int>(fp_img_get_height(*p_img));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1getWidth
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);
        return static_cast<int>(fp_img_get_width(*p_img));
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return 0;
    }
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_Img_fp_1getData
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);

        int width = fp_img_get_width(*p_img);
        int height = fp_img_get_height(*p_img);

        // TODO: Validade array size
        int size = width * height;

        // must not be modified or freed
        signed char* data = reinterpret_cast<signed char*>(fp_img_get_data(*p_img));

        return h.newByteArray(size, reinterpret_cast<jbyte*>(data));
    } catch (JNIGenericError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1saveToFile
  (JNIEnv *env, jobject obj, jstring path)
{
    log("Running ", FUNC_DESC);

    char *cpath = NULL;
    fp_img **p_img = NULL;

    cpath = const_cast<char*>(env->GetStringUTFChars(path, NULL));

    if (NULL == cpath || env->ExceptionCheck()) {
        if (NULL != cpath) {
            env->ReleaseStringUTFChars(path, cpath);
        }

        Util::throwNativeException(env, "On create C String", LOCATION_INFO, FUNC_DESC);
        return 0;
    }

    Util::JNIHandler h(env);

    try {
        p_img = h.getPointer<fp_img>(obj);
        int ret = fp_img_save_to_file(*p_img, cpath);

        env->ReleaseStringUTFChars(path, cpath);

        if (ret != 0) {
            Util::throwCodeError(env, ret);
            return ret;
        }

    } catch (JNIGetPointerError& ex) {
        env->ReleaseStringUTFChars(path, cpath);
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return -1;
    }
}


JNIEXPORT void JNICALL Java_jfprint_Img_fp_1standardize
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);
        fp_img_standardize(*p_img);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
    }

}


JNIEXPORT jobject JNICALL Java_jfprint_Img_fp_1binarize
  (JNIEnv *env, jobject obj)
{
    log("Running ", FUNC_DESC);

    fp_img *binarized_img = NULL;
    Util::JNIHandler h(env);

    try {
        fp_img **p_img = h.getPointer<fp_img>(obj);
        binarized_img = fp_img_binarize(*p_img);

        if (NULL == binarized_img) {
            log("Can not generate binarized image - " LOCATION_INFO ", ", FUNC_DESC);
            Util::throwOperationError(env);
            return NULL;
        }

        return h.newNativeResource(CLASS_IMG, binarized_img);
    } catch (JNIGetPointerError& ex) {
        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    } catch (JNINewInstanceError& ex) {
        if (NULL != binarized_img) {
            fp_img_free(binarized_img);
        }

        Util::throwNativeException(env, obj, ex.get_msg(), LOCATION_INFO, FUNC_DESC);
        return NULL;
    }
}
