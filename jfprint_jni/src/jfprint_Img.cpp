
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
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj,
                                     "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_img_free(*p_img);
    delete p_img;
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1getHeight
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<int>(fp_img_get_height(*p_img));
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1getWidth
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    return static_cast<int>(fp_img_get_width(*p_img));
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_Img_fp_1getData
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    int width = fp_img_get_width(*p_img);
    int height = fp_img_get_height(*p_img);
    int size = width * height;

    signed char* data = reinterpret_cast<signed char*>(fp_img_get_data(*p_img));

    jbyteArray byteArray = env->NewByteArray(size);

    if (Util::checkAndThrowException(env, byteArray, obj,
                                     "Can not instantiate byte array", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    env->SetByteArrayRegion(byteArray, 0, size, data);

    if (Util::checkAndThrowException(env, obj, "Unable to populate the byte array", LOCATION_INFO, FUNC_DESC)) {
        return NULL;
    }

    return byteArray;
}


JNIEXPORT jint JNICALL Java_jfprint_Img_fp_1saveToFile
  (JNIEnv *env, jobject obj, jstring path)
{
    char *cpath = const_cast<char*>(env->GetStringUTFChars(path, NULL));

    if (Util::checkAndThrowException(env, cpath, obj, "Can not create C style string", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        env->ReleaseStringUTFChars(path, cpath);
        return 0;
    }

    return fp_img_save_to_file(*p_img, cpath);
}


JNIEXPORT void JNICALL Java_jfprint_Img_fp_1standardize
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return;
    }

    fp_img_standardize(*p_img);
}


JNIEXPORT jobject JNICALL Java_jfprint_Img_fp_1binarize
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    if (Util::checkAndThrowException(env, p_img, obj,
                                     "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        return 0;
    }

    fp_img **p_img2 = new fp_img*;
    *p_img2 = fp_img_binarize(*p_img);

    if (NULL == *p_img2) {
        log("Can not generate binarized image - " LOCATION_INFO ", ", FUNC_DESC);
        Util::throwOperationError(env);
        delete p_img2;
        return NULL;
    }

    jobject img = Util::newInstance(env, "Ljfprint/Img;");

    if (Util::checkAndThrowException(env, img, obj,
                                     "Can not instantiate Img", LOCATION_INFO, FUNC_DESC)) {
        fp_img_free(*p_img2);
        delete p_img2;

        return NULL;
    }

    Util::setPointerAddress(env, img, "pointer", p_img2, sizeof(fp_img*));

    if (Util::checkAndThrowException(env, obj, "Can not access Img 'pointer'", LOCATION_INFO, FUNC_DESC)) {
        fp_img_free(*p_img2);
        delete p_img2;

        return NULL;
    }

    return img;
}
