
#include "jfprint_Img.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Img_nativeClose
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_img_free(*p_img);
    delete p_img;
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jint JNICALL Java_jfprint_Img_getHeight
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<int>(fp_img_get_height(*p_img));
}


JNIEXPORT jint JNICALL Java_jfprint_Img_getWidth
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    return static_cast<int>(fp_img_get_width(*p_img));
}


JNIEXPORT jbyteArray JNICALL Java_jfprint_Img_getData
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    int width = fp_img_get_width(*p_img);
    int height = fp_img_get_height(*p_img);
    int size = width * height;

    signed char* data = reinterpret_cast<signed char*>(fp_img_get_data(*p_img));

    jbyteArray byteArray = env->NewByteArray(size);
    env->SetByteArrayRegion(byteArray, 0, size, data);

    return byteArray;
}


JNIEXPORT jint JNICALL Java_jfprint_Img_saveToFile
  (JNIEnv *env, jobject obj, jstring path)
{
    char *cpath = const_cast<char*>(env->GetStringUTFChars(path, NULL));
    if (NULL == cpath) {
        log("Can not access cpath on. " LOCATION_INFO);
        return Util::throwException(env, "Can not access the path on JNI. " LOCATION_INFO);
    }

    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));

    return fp_img_save_to_file(*p_img, cpath);
}


JNIEXPORT void JNICALL Java_jfprint_Img_standardize
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_img_standardize(*p_img);
}


JNIEXPORT jobject JNICALL Java_jfprint_Img_binarize
  (JNIEnv *env, jobject obj)
{
    fp_img **p_img = reinterpret_cast<fp_img**>(Util::getPointerAddress(env, obj, "pointer"));
    fp_img **p_img2 = new fp_img*;


    *p_img2 = fp_img_binarize(*p_img);

    if (NULL == *p_img2) {
        log("Can not generate binarized image. " LOCATION_INFO);
        Util::throwException(env, "Can not generate binarized image. " LOCATION_INFO);
        delete p_img2;
        return NULL;
    }

    jobject img = Util::newInstance(env, "Ljfprint/Img;");
    Util::setPointerAddress(env, img, "pointer", p_img2, sizeof(fp_img*));

    return img;
}
