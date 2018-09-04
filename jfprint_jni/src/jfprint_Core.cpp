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
    log("libfprint initialized.\n");

    return ret_code;
}


JNIEXPORT void JNICALL Java_jfprint_Core_fp_1exit
  (JNIEnv *env, jclass cls)
{
    fp_exit();
    log("libfprint finished.\n");
}


/*
 * Class:     jfprint_Core
 * Method:    fp_set_debug
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jfprint_Core_fp_1set_1debug
  (JNIEnv *env, jclass cls, jint level)
{
    fp_set_debug(level);
    log("Setting debug to log level ", level);
}
