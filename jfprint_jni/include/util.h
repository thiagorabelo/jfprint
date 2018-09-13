
/*
 * File:   util.h
 * Author: thiago
 *
 * Created on 18 de Junho de 2018, 10:54
 */

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <jni.h>

/*
extern "C" {
#include <libfprint/fprint.h>
}
*/

#include "exception/JNIError.h"
#include "exception/FPrintError.h"
#include "defs.h"

#include <utility>


/*
 *
 * Tipos de erros:
 *
 * - JNI
 *     - get object class
 *     - get field id
 *     - get field value
 *     - set field value
 *     - get method id
 *     - call method
 *     - populate byte array
 *     - create c string
 *     - ERRORS ESPECIALIZADOS
 *           - instanciar objetos
 *           - set pointer
 *           - get pointer
 *           - get wrapper class
 *           - get obj em wrapper class
 *           - set obj em wrapper class
 *
 * - fprint
 *     - impossível abrir dispositivo
 *     - impossível obter dados do driver: id, type, name, full name
 *     - impossível obter print data
 *     - impossível ler print data
 *     - impossível obter device ou print descobertos
 *     - impossível descobrir devices prints
 *
 */



template<typename T>
static void __log(std::ostream &stream, T const& t)
{
    stream << t << std::endl;
}


template <typename T, typename... Ts>
static void __log(std::ostream &stream, T t, Ts const&... ts)
{
    stream << t;
    __log(stream, ts...);
}


#define err(head, ...) __log(std::cerr, "NATIVE ERROR: ", head, ##__VA_ARGS__);


#ifdef DEBUG
#define log(head, ...) __log(std::cout, "    NATIVE >> ", head, ##__VA_ARGS__);
#else
#define log(x, ...)
#endif


namespace Util {

//    class JNIHelper
//    {
//        public:
//            JNIHelper(JNIEnv* env);
//            JNIHelper(JNIHelper& orig);
//            virtual ~JNIHelper();
//
//            jclass getObjectClass(jobject obj);
//            jclass findClass(const char clsName);
//
//            template <typename F>
//            F getFieldValue(jobject obj, const char* fieldName){ return nullptr; }
//
//            template <typename F, typename V>
//            void setFieldValue(jobject obj, const char* fieldName, V value) {}
//
//            template <typename... Args>
//            jboolean callMethod(jobject obj, const char *methodName, Args&&... args)
//            {
//                return env->CallBooleanMethod(obj, nullptr, std::forward<Args>(args)...);
//            }
//
//            jobject CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jboolean CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jbyte CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jchar CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jshort CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jint CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jlong CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jfloat CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            jdouble CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//            void CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
//
//
//            jobject CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...)
//            jboolean CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...)
//            jbyte CallStaticByteMethod(jclass clazz, jmethodID methodID, ...)
//            jchar CallStaticCharMethod(jclass clazz, jmethodID methodID, ...)
//            jshort CallStaticShortMethod(jclass clazz, jmethodID methodID, ...)
//            jint CallStaticIntMethod(jclass clazz, jmethodID methodID, ...)
//            jlong CallStaticLongMethod(jclass clazz, jmethodID methodID, ...)
//            jfloat CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...)
//            jdouble CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...)
//            void CallStaticVoidMethod(jclass cls, jmethodID methodID, ...)
//
//
//            jobject CallObjectMethod(jobject obj, jmethodID methodID, ...)
//            jboolean CallBooleanMethod(jobject obj, jmethodID methodID, ...)
//            jbyte CallByteMethod(jobject obj, jmethodID methodID, ...)
//            jchar CallCharMethod(jobject obj, jmethodID methodID, ...)
//            jshort CallShortMethod(jobject obj, jmethodID methodID, ...)
//            jint CallIntMethod(jobject obj, jmethodID methodID, ...)
//            jlong CallLongMethod(jobject obj, jmethodID methodID, ...)
//            jfloat CallFloatMethod(jobject obj, jmethodID methodID, ...)
//            jdouble CallDoubleMethod(jobject obj, jmethodID methodID, ...)
//            void CallVoidMethod(jobject obj, jmethodID methodID, ...)
//
//        private:
//            JNIEnv* env;
//    };

    /**
     *
     * @param env
     * @param obj
     * @param fieldName
     * @return
     */
    extern void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName);
    extern void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size);

    extern jobject newInstance(JNIEnv *env, const char *clsName);
    extern jobject newInstance(JNIEnv *env, jclass cls);

    extern jobject newResultTuple(JNIEnv *env, int code);
    extern jobject newResultTuple(JNIEnv *env, jobject obj, int code);


    template <typename T>
    jobject newNativeResource(JNIEnv *env, const char *clsName, T *ptr) noexcept(false)
    // throws: JNIFindClassError, JNIGetIdError, JNINewObjectError,
    //         JNIGetObjectClassError, JNIGetFieldValueError, JNISetFieldValueError
    {
        jobject jobj = Util::newInstance(env, clsName);

        T **p_ptr = new T*;
        *p_ptr = ptr;

        try {
            Util::setPointerAddress(env, jobj, "pointer", p_ptr, sizeof(T*));
        } catch (JNIError& ex) {
            delete p_ptr;
            throw;
        }

        return jobj;
    }


    extern void setWrapperObj(JNIEnv *env, jobject wrapper, jobject obj);


    inline jthrowable stopExceptionPropagation(JNIEnv *env)
    {
        jthrowable cause = env->ExceptionOccurred();
        env->ExceptionClear();
        return cause;
    }

    extern jint throwCodeError(JNIEnv *env, jint code);
    extern jint throwOperationError(JNIEnv *env);
    extern jint throwOperationError(JNIEnv *env, const char *msg);

    extern jint throwException(JNIEnv *env, const char *message);
    extern jint throwException(JNIEnv *env, const char *clsName, const char *message);

    extern jint throwNativeException(JNIEnv *env,
                                     const char *message, const char *funcName, const char *locationInfo);
    extern jint throwNativeException(JNIEnv *env, jclass cls,
                                     const char *message, const char *funcName, const char *locationInfo);
    extern jint throwNativeException(JNIEnv *env, jobject obj,
                                     const char *message, const char *funcName, const char *locationInfo);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause,
                                     const char *message, const char *funcName, const char *locationInfo);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause, jobject obj,
                                     const char *message, const char *funcName, const char *locationInfo);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause, jclass cls,
                                     const char *message, const char *funcName, const char *locationInfo);


    extern bool checkAndThrowException(JNIEnv *env,
                                       const char *message, const char *locationInfo, const char *funcName);
    extern bool checkAndThrowException(JNIEnv *env, jobject obj,
                                       const char *message, const char *locationInfo, const char *funcName);
    extern bool checkAndThrowException(JNIEnv *env, jclass cls,
                                       const char *message, const char *locationInfo, const char *funcName);
    extern bool checkAndThrowException(JNIEnv *env, const void *to_verify,
                                       const char *message, const char *locationInfo, const char *funcName);
    extern bool checkAndThrowException(JNIEnv *env, const void *to_verify, jclass cls,
                                       const char *message, const char *locationInfo, const char *funcName);
    extern bool checkAndThrowException(JNIEnv *env, const void *to_verify, jobject obj,
                                       const char *message, const char *locationInfo, const char *funcName);


    template <typename RetType, typename DataType, typename AppliedFunc>
    RetType applyFuncToPointer(JNIEnv *env, jobject obj, const char *fieldName, AppliedFunc fn, RetType nullVal) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError
    {
        DataType **data = reinterpret_cast<DataType**>(Util::getPointerAddress(env, obj, fieldName));
        return static_cast<RetType>(fn(*data));
    }


    namespace DiscoveredItemsList {

        template<typename T>
        size_t getDiscoveredListSize(T **nullTerminatedList)
        {
            size_t size = 0;

            if (nullTerminatedList) {
                T *dev = nullTerminatedList[0];

                while (NULL != dev) {
                    size += 1;
                    dev = nullTerminatedList[size];
                }
            }

            return size;
        }


        template<typename DiscoveredType>
        jobject nativeGet(JNIEnv *env, jobject obj, jint index, const char *clsName) noexcept(false)
        // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError,
        //         JNISetFieldValueError, JNIFindClassError, JNINewObjectError
        {
          DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));

          // By not having access to the structures defined in libfprint we
          // must pass a pointer to pointer to the JNI.
          // And we should remember to not delete the contents of this
          // pointer when the close method is triggered.
          DiscoveredType **p_discovered = &discovereds[index];

          jobject jdicovered = Util::newInstance(env, clsName);
          Util::setPointerAddress(env, jdicovered, "pointer", p_discovered, sizeof(DiscoveredType*));

          return jdicovered;
        }


        /**
         *
         *
         * @param env
         * @param cls
         * @param ClassName
         * @param fn
         * @return
         */
        template <typename DiscoveredType, typename DiscoverFunc>
        jobject discover(JNIEnv *env, jclass cls, DiscoverFunc fn) noexcept(false)
        // throws: JNINewObjectError, JNIGetObjectClassError, JNIGetIdError,
        //         JNIGetFieldValueError, JNISetFieldValueError
        {
            jfieldID fidSize = env->GetFieldID(cls, "size", "I");
            if (NULL == fidSize) {
                err("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
                throw JNIGetIdError(LOCATION_INFO, FUNC_DESC);
            }

            jobject jdiscovered_list = Util::newInstance(env, cls);

            // There is no need to create a pointer to pointer,
            // as this is done by the fprint library itself.
            DiscoveredType **discovereds = fn();
            size_t size = Util::DiscoveredItemsList::getDiscoveredListSize(discovereds);

            Util::setPointerAddress(env, jdiscovered_list, "pointer", discovereds, sizeof(DiscoveredType*));

            env->SetIntField(jdiscovered_list, fidSize, static_cast<int>(size));
            if (env->ExceptionCheck()) {
                err("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
                throw JNISetFieldValueError(LOCATION_INFO, FUNC_DESC);
            }

            return jdiscovered_list;
        }

        template<typename DiscoveredType, typename FreeFunc>
        void nativeClose(JNIEnv *env, jobject obj, FreeFunc fn) noexcept(false)
        // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError
        {
            DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));

            // Do not freed the pointer to pointer.
            // Let fprint do that.
            fn(discovereds);
        }
    };


    template <typename T>
    T** jobjectArrayToCNULLTerminatedArray(JNIEnv *env, jobjectArray array) noexcept(false)
    // throws: JNIGetObjectClassError, JNIGetIdError, JNIGetFieldValueError
    {
        jsize size = env->GetArrayLength(array);
        T **data = new T*[size + 1];

        for (jsize i = 0; i < size; i++) {
            jobject obj = env->GetObjectArrayElement(array, i);

            try {
                T **print_data = reinterpret_cast<T**>(Util::getPointerAddress(env, obj, "pointer"));
                data[i] = *print_data;
            } catch (JNIError& ex) {
                delete [] data;
                throw;
            }
        }

        data[size] = NULL;

        return data;
    }
};


#endif /* UTIL_H */
