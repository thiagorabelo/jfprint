#include "jfprint_Driver.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT void JNICALL Java_jfprint_Driver_nativeClose
  (JNIEnv *env, jobject obj)
{
    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));
    // Delete only the pointer to pointer.
    delete driver;
    log("Running ", __PRETTY_FUNCTION__);
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_getName
  (JNIEnv *env, jobject obj)
{
    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));
    const char *name = fp_driver_get_name(*driver);
    return env->NewStringUTF(name);
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_getFullName
  (JNIEnv *env, jobject obj)
{
    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));
    if (NULL == driver || NULL == *driver) {
        log("The driver is NULL", __FILE__, ":", __LINE__);
        return NULL;
    }

    const char *name = fp_driver_get_full_name(*driver);
    log(__FILE__, ":", __LINE__, " The full name is: ", name, "\n");
    return env->NewStringUTF(name);
}


JNIEXPORT jlong JNICALL Java_jfprint_Driver_getDriverID
  (JNIEnv *env, jobject obj)
{
    fp_driver **driver = reinterpret_cast<fp_driver**>(Util::getPointerAddress(env, obj, "pointer"));
    jlong driver_id = static_cast<jlong>(fp_driver_get_driver_id(*driver));
    return driver_id;
}
