/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jfprint_Device */

#ifndef _Included_jfprint_Device
#define _Included_jfprint_Device
#ifdef __cplusplus
extern "C" {
#endif
#undef jfprint_Device_FP_ENROLL_COMPLETE
#define jfprint_Device_FP_ENROLL_COMPLETE 1L
#undef jfprint_Device_FP_ENROLL_FAIL
#define jfprint_Device_FP_ENROLL_FAIL 2L
#undef jfprint_Device_FP_ENROLL_PASS
#define jfprint_Device_FP_ENROLL_PASS 3L
#undef jfprint_Device_FP_ENROLL_RETRY
#define jfprint_Device_FP_ENROLL_RETRY 100L
#undef jfprint_Device_FP_ENROLL_RETRY_TOO_SHORT
#define jfprint_Device_FP_ENROLL_RETRY_TOO_SHORT 101L
#undef jfprint_Device_FP_ENROLL_RETRY_CENTER_FINGER
#define jfprint_Device_FP_ENROLL_RETRY_CENTER_FINGER 102L
#undef jfprint_Device_FP_ENROLL_RETRY_REMOVE_FINGER
#define jfprint_Device_FP_ENROLL_RETRY_REMOVE_FINGER 103L
#undef jfprint_Device_FP_VERIFY_NO_MATCH
#define jfprint_Device_FP_VERIFY_NO_MATCH 0L
#undef jfprint_Device_FP_VERIFY_MATCH
#define jfprint_Device_FP_VERIFY_MATCH 1L
#undef jfprint_Device_FP_VERIFY_RETRY
#define jfprint_Device_FP_VERIFY_RETRY 100L
#undef jfprint_Device_FP_VERIFY_RETRY_TOO_SHORT
#define jfprint_Device_FP_VERIFY_RETRY_TOO_SHORT 101L
#undef jfprint_Device_FP_VERIFY_RETRY_CENTER_FINGER
#define jfprint_Device_FP_VERIFY_RETRY_CENTER_FINGER 102L
#undef jfprint_Device_FP_VERIFY_RETRY_REMOVE_FINGER
#define jfprint_Device_FP_VERIFY_RETRY_REMOVE_FINGER 103L
/*
 * Class:     jfprint_Device
 * Method:    nativeClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jfprint_Device_nativeClose
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    getDriver
 * Signature: ()Ljfprint/Driver;
 */
JNIEXPORT jobject JNICALL Java_jfprint_Device_getDriver
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    getNumEnrollStages
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jfprint_Device_getNumEnrollStages
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    getDevType
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_jfprint_Device_getDevType
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    supportsPrintData
 * Signature: (Ljfprint/PrintData;)Z
 */
JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsPrintData
  (JNIEnv *, jobject, jobject);

/*
 * Class:     jfprint_Device
 * Method:    supportsDiscoveredPrint
 * Signature: (Ljfprint/DiscoveredPrint;)Z
 */
JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsDiscoveredPrint
  (JNIEnv *, jobject, jobject);

/*
 * Class:     jfprint_Device
 * Method:    supportsImaging
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsImaging
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    supportsIdentification
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_jfprint_Device_supportsIdentification
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    imgCapture
 * Signature: (Z)Ljfprint/Img;
 */
JNIEXPORT jobject JNICALL Java_jfprint_Device_imgCapture
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     jfprint_Device
 * Method:    getImgWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jfprint_Device_getImgWidth
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    getImgHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jfprint_Device_getImgHeight
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Device
 * Method:    enrollFingerImg
 * Signature: (Ljfprint/util/Wrapper;Ljfprint/util/Wrapper;)I
 */
JNIEXPORT jint JNICALL Java_jfprint_Device_enrollFingerImg
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     jfprint_Device
 * Method:    verifyFingerImg
 * Signature: (Ljfprint/PrintData;Ljfprint/util/Wrapper;)I
 */
JNIEXPORT jint JNICALL Java_jfprint_Device_verifyFingerImg
  (JNIEnv *, jobject, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
