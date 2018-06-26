#include "jfprint_Core.h"
#include "util.h"

extern "C"
{
#include <libfprint/fprint.h>
}


JNIEXPORT jint JNICALL Java_jfprint_Core_fp_1init
  (JNIEnv *env, jclass cls)
{
    int ret_code = fp_init();

    log("libfprint inicializada.");

    return (int)ret_code;
}


JNIEXPORT void JNICALL Java_jfprint_Core_fp_1exit
  (JNIEnv *env, jclass cls)
{
    fp_exit();
    log("libfprint finalizada.");
}
