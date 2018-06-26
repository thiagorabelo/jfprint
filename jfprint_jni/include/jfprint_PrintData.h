/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jfprint_PrintData */

#ifndef _Included_jfprint_PrintData
#define _Included_jfprint_PrintData
#ifdef __cplusplus
extern "C" {
#endif
#undef jfprint_PrintData_LEFT_THUMB
#define jfprint_PrintData_LEFT_THUMB 1L
#undef jfprint_PrintData_LEFT_INDEX
#define jfprint_PrintData_LEFT_INDEX 2L
#undef jfprint_PrintData_LEFT_MIDDLE
#define jfprint_PrintData_LEFT_MIDDLE 3L
#undef jfprint_PrintData_LEFT_RING
#define jfprint_PrintData_LEFT_RING 4L
#undef jfprint_PrintData_LEFT_LITTLE
#define jfprint_PrintData_LEFT_LITTLE 5L
#undef jfprint_PrintData_RIGHT_THUMB
#define jfprint_PrintData_RIGHT_THUMB 6L
#undef jfprint_PrintData_RIGHT_INDEX
#define jfprint_PrintData_RIGHT_INDEX 7L
#undef jfprint_PrintData_RIGHT_MIDDLE
#define jfprint_PrintData_RIGHT_MIDDLE 8L
#undef jfprint_PrintData_RIGHT_RING
#define jfprint_PrintData_RIGHT_RING 9L
#undef jfprint_PrintData_RIGHT_LITTLE
#define jfprint_PrintData_RIGHT_LITTLE 10L
/*
 * Class:     jfprint_PrintData
 * Method:    nativeClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jfprint_PrintData_nativeClose
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_PrintData
 * Method:    getData
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_jfprint_PrintData_getData
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_PrintData
 * Method:    fromData
 * Signature: ([B)Ljfprint/PrintData;
 */
JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fromData
  (JNIEnv *, jclass, jbyteArray);

/*
 * Class:     jfprint_PrintData
 * Method:    dataSave
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jfprint_PrintData_dataSave
  (JNIEnv *, jobject, jint);

/*
 * Class:     jfprint_PrintData
 * Method:    dataLoad
 * Signature: (Ljfprint/Device;I)Ljfprint/PrintData;
 */
JNIEXPORT jobject JNICALL Java_jfprint_PrintData_dataLoad
  (JNIEnv *, jclass, jobject, jint);

/*
 * Class:     jfprint_PrintData
 * Method:    delete
 * Signature: (Ljfprint/Device;I)I
 */
JNIEXPORT jint JNICALL Java_jfprint_PrintData_delete
  (JNIEnv *, jclass, jobject, jint);

/*
 * Class:     jfprint_PrintData
 * Method:    fromDiscoveredPrint
 * Signature: (Ljfprint/DiscoveredPrint;)Ljfprint/PrintData;
 */
JNIEXPORT jobject JNICALL Java_jfprint_PrintData_fromDiscoveredPrint
  (JNIEnv *, jclass, jobject);

/*
 * Class:     jfprint_PrintData
 * Method:    getDriverId
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_jfprint_PrintData_getDriverId
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_PrintData
 * Method:    getDevtype
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_jfprint_PrintData_getDevtype
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
