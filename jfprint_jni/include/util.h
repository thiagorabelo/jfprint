
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


extern "C" {
#include <libfprint/fprint.h>
}

#include "exception/JNIError.h"
#include "exception/FPrintError.h"
#include "defs.h"

#include <utility>


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

	class JNIHandler
	{
		public:
			JNIHandler(JNIEnv* env);
			~JNIHanlder();

			template <typename T>
			T** getPointer(jobject obj) noexcept(false)
			{
				try {
					return reinterpret_cast<T**>Util::getPointerAddress(env, obj, "pointer");
				} catch (JNIError& error) {
					throw JNIPointerError(error);
				}
			}
		private:
			JNIEnv* env;
	};

    /**
	 *
	 * @param env
	 * @param obj
	 * @param fieldName
	 * @return
	 *
	 * @throws JNIGetObjectClassError
	 * @throws JNIGetIdError
	 * @throws JNIGetFieldValueError
	 */
    extern void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName) noexcept(false) ;

	/**
	 *
	 * @param env
	 * @param obj
	 * @param fieldName
	 * @param address
	 * @param size
	 * @return
	 *
	 * @throws JNIGetObjectClassError
	 * @throws JNIGetIdError
	 * @throws JNIGetFieldValueError
	 * @throws JNISetFieldValueError
	 */
    extern void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size) noexcept(false);


	/**
	 *
	 * @param env
	 * @param clsName
	 * @return
	 *
	 * @throws JNIFindClassError
	 * @throws JNIGetIdError
	 * @throws JNINewObjectError
	 */
    extern jobject newInstance(JNIEnv *env, const char *clsName) noexcept(false);

	/**
	 *
	 * @param env
	 * @param cls
	 * @return
	 *
	 * @throws JNIGetIdError
	 * @throws JNINewObjectError
	 */
    extern jobject newInstance(JNIEnv *env, jclass cls) noexcept(false);

	/**
	 *
	 * @param env
	 * @param code
	 * @return
	 *
	 * @throws JNIFindClassError
	 * @throws JNIGetIdError
	 * @throws JNINewObjectError
	 */
    extern jobject newResultTuple(JNIEnv *env, int code) noexcept(false);

	/**
	 *
	 * @param env
	 * @param obj
	 * @param code
	 * @return
	 *
	 * @throws JNIFindClassError
	 * @throws JNIGetIdError
	 * @throws JNINewObjectError
	 */
    extern jobject newResultTuple(JNIEnv *env, jobject obj, int code) noexcept(false);


	/**
	 *
	 * @param env
	 * @param clsName
	 * @param ptr
	 * @return
	 *
	 * @throws JNIFindClassError
	 * @throws JNIGetIdError
	 * @throws JNINewObjectError
	 * @throws JNIGetObjectClassError
	 * @throws JNIGetFieldValueError
	 * @throws JNISetFieldValueError
	 */
    template <typename T>
    jobject newNativeResource(JNIEnv *env, const char *clsName, T *ptr) noexcept(false)
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


	/**
	 *
	 * @param env
	 * @param wrapper
	 * @param obj
	 *
	 * @throws JNIGetObjectClassError
	 * @throws JNIGetIdError
	 * @throws JNISetFieldValueError
	 */
    extern void setWrapperObj(JNIEnv *env, jobject wrapper, jobject obj) noexcept(false);


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

	/**
	 *
	 * @param env
	 * @param array
	 * @return
	 *
	 * @throws JNIGetObjectClassError
	 * @throws JNIGetIdError
	 * @throws JNIGetFieldValueError
	 */
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
