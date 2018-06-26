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
    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer", fp_driver_get_name);
    return env->NewStringUTF(name);
}


JNIEXPORT jstring JNICALL Java_jfprint_Driver_getFullName
  (JNIEnv *env, jobject obj)
{
    const char *name = Util::applyFuncToPointer<const char*, fp_driver>(env, obj, "pointer", fp_driver_get_full_name);
    return env->NewStringUTF(name);
}


JNIEXPORT jlong JNICALL Java_jfprint_Driver_getDriverID
  (JNIEnv *env, jobject obj)
{
    return Util::applyFuncToPointer<jlong, fp_driver>(env, obj, "pointer", fp_driver_get_driver_id);
}
