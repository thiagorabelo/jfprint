/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jfprint_Img */

#ifndef _Included_jfprint_Img
#define _Included_jfprint_Img
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jfprint_Img
 * Method:    nativeClose
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jfprint_Img_nativeClose
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Img
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jfprint_Img_getHeight
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Img
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jfprint_Img_getWidth
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Img
 * Method:    getData
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_jfprint_Img_getData
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Img
 * Method:    saveToFile
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_jfprint_Img_saveToFile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     jfprint_Img
 * Method:    standardize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jfprint_Img_standardize
  (JNIEnv *, jobject);

/*
 * Class:     jfprint_Img
 * Method:    binarize
 * Signature: ()Ljfprint/Img;
 */
JNIEXPORT jobject JNICALL Java_jfprint_Img_binarize
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif