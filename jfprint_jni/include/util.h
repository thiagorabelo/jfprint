
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
#include <ctime>
#include <chrono>


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
	auto today = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(today);

	stream << "[" << t << " " << ctime(&tt) << "] ";
    __log(stream, ts...);
}


/*
 * LOG_LEVEL
 *	debug = 1
 *	warning = 2
 *	error = 3
 */

#if LOG_LEVEL == 1
#define log_debug(head, ...)   __log(std::cout, "DEBUG",   head, ##__VA_ARGS__);
#define log_warning(head, ...) __log(std::cout, "WARNING", head, ##__VA_ARGS__);
#define log_error(head, ...)   __log(std::cerr, "ERROR",  head, ##__VA_ARGS__);
#elif LOG_LEVEL == 2
#define log_debug(head, ...)
#define log_warning(head, ...) __log(std::cout, "WARNING", head, ##__VA_ARGS__);
#define log_error(head, ...)   __log(std::error, "ERROR",  head, ##__VA_ARGS__);
#elif LOG_LEVEL == 3
#define log_debug(head, ...)
#define log_warning(head, ...)
#define log_error(head, ...)   __log(std::error, "ERROR",  head, ##__VA_ARGS__);
#else
#define log_debug(head, ...)
#define log_warning(head, ...)
#define log_error(head, ...)
#endif


namespace Util {

	class JNIHandler
	{
		public:
			JNIHandler(JNIEnv* env);
			virtual ~JNIHandler();

			void* setPointer(jobject obj, void *address, size_t size) noexcept(false);
			jobject newInstance(const char* clsName);
			jobject newInstance(jclass cls);
			jobject newResultTuple(int code) noexcept(false);
			jobject newResultTuple(jobject obj, int code) noexcept(false);
			void setWrapperObj(jobject wrapper, jobject obj) noexcept(false);
			jbyteArray newByteArray(jsize size, jbyte *buf) noexcept(false);
			jbyte *fromByteArray(jbyteArray byteArray) noexcept(false);


			template <typename T>
			T** getPointer(jobject obj) noexcept(false);

			template <typename T>
			T** toCNULLTerminatedArray(jobjectArray javaArrayObject) noexcept(false);

		    template <typename T>
		    jobject newNativeResource(jclass cls, T *ptr) noexcept(false);

		    template <typename T>
		    jobject newNativeResource(const char *clsName, T *ptr) noexcept(false);

		private:
			JNIEnv* env;
	};


    extern void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName) noexcept(false) ;


    extern void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size) noexcept(false);


    extern jobject newInstance(JNIEnv *env, const char *clsName) noexcept(false);


    extern jobject newInstance(JNIEnv *env, jclass cls) noexcept(false);


	template <typename T>
    jobject newNativeResource(JNIEnv *env, const char *clsName, T *ptr) noexcept(false);


    template <typename T>
    jobject newNativeResource(JNIEnv *env, jclass cls, T *ptr) noexcept(false);


    extern jobject newResultTuple(JNIEnv *env, int code) noexcept(false);


    extern jobject newResultTuple(JNIEnv *env, jobject obj, int code) noexcept(false);


	extern jbyteArray newByteArray(JNIEnv *env, jsize size, jbyte* buf) noexcept(false);


	extern jbyte *fromByteArray(JNIEnv *env, jbyteArray byteArray) noexcept(false);


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
                                     const char *message, const char *locationInfo, const char *funcName);
    extern jint throwNativeException(JNIEnv *env, jclass cls,
                                     const char *message, const char *locationInfo, const char *funcName);
    extern jint throwNativeException(JNIEnv *env, jobject obj,
                                     const char *message, const char *locationInfo, const char *funcName);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause,
                                     const char *message, const char *locationInfo, const char *funcName);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause, jobject obj,
                                     const char *message, const char *locationInfo, const char *funcName);
    extern jint throwNativeException(JNIEnv *env, jthrowable cause, jclass cls,
                                     const char *message, const char *locationInfo, const char *funcName);


    namespace DiscoveredItemsList {

        template<typename T>
        size_t getDiscoveredListSize(T **nullTerminatedList);


        template<typename DiscoveredType>
        jobject nativeGet(JNIEnv *env, jobject obj, jint index, const char *clsName) noexcept(false);


        template <typename DiscoveredType, typename DiscoverFunc, typename FreeDiscoveredFunc>
        jobject discover(JNIEnv *env, jclass cls, DiscoverFunc fn, FreeDiscoveredFunc fnFree) noexcept(false);


        template<typename DiscoveredType, typename FreeFunc>
        void nativeClose(JNIEnv *env, jobject obj, FreeFunc fn) noexcept(false);
    };

};




namespace Util {

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
        {
			DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));

			// By not having access to the structures defined in libfprint we
			// must pass a pointer to pointer to the JNI.
			// And we should remember to not delete the content of this
			// pointer when the close method is triggered.
			DiscoveredType *discovered = discovereds[index];
			jobject jdiscovered = Util::newNativeResource(env, clsName, discovered);

			return jdiscovered;
        }


        template <typename DiscoveredType, typename DiscoverFunc, typename FreeDiscoveredFunc>
        jobject discover(JNIEnv *env, jclass cls, DiscoverFunc fn, FreeDiscoveredFunc fnFree) noexcept(false)
        {
			jfieldID fidSize = env->GetFieldID(cls, "size", "I");
			if (NULL == fidSize) {
				log_error("On get field id - " LOCATION_INFO ", ", FUNC_DESC);
				throw JNIError("On get field id", LOCATION_INFO, FUNC_DESC);
			}

			jobject jdiscovered_list = Util::newInstance(env, cls);

			// There is no need to create a pointer to pointer,
			// as this is done by the fprint library itself.
			DiscoveredType **discovereds = fn();
			size_t size = Util::DiscoveredItemsList::getDiscoveredListSize(discovereds);

			try {
				Util::setPointerAddress(env, jdiscovered_list, "pointer", discovereds, sizeof(DiscoveredType*));
			} catch (JNIError& error) {
				fnFree(discovereds);
				throw;
			}

			env->SetIntField(jdiscovered_list, fidSize, static_cast<int>(size));
			if (env->ExceptionCheck()) {
				log_error("On set field value - " LOCATION_INFO ", ", FUNC_DESC);
				fnFree(discovereds);
				throw JNIError("On set field value", LOCATION_INFO, FUNC_DESC);
			}

			return jdiscovered_list;
        }

        template<typename DiscoveredType, typename FreeFunc>
        void nativeClose(JNIEnv *env, jobject obj, FreeFunc fn) noexcept(false)
        {
			DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));

			// Do not freed the pointer to pointer.
			// Let fprint do that.
			fn(discovereds);
        }
    };




    template <typename T>
    T** jobjectArrayToCNULLTerminatedArray(JNIEnv *env, jobjectArray array) noexcept(false)
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



	template <typename T>
    jobject newNativeResource(JNIEnv *env, const char *clsName, T *ptr) noexcept(false)
    {
		jclass cls = env->FindClass(clsName);

        if (NULL == cls) {
            log_error("On find class - " LOCATION_INFO ", ", FUNC_DESC);
            throw JNIError("On find class", LOCATION_INFO, FUNC_DESC);
        }

		return Util::newNativeResource(env, cls, ptr);
    }


    template <typename T>
    jobject newNativeResource(JNIEnv *env, jclass cls, T *ptr) noexcept(false)
    {
        jobject jobj = Util::newInstance(env, cls);

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




	template <typename T>
	T** JNIHandler::getPointer(jobject obj) noexcept(false)
	{
		try {
			return reinterpret_cast<T**>(Util::getPointerAddress(env, obj, "pointer"));
		} catch (JNIError& error) {
			throw JNIGetPointerError(error);
		}
	}

	template <typename T>
	T** JNIHandler::toCNULLTerminatedArray(jobjectArray javaArrayObject) noexcept(false)
	{
		try {
			return Util::jobjectArrayToCNULLTerminatedArray<T>(env, javaArrayObject);
		} catch (JNIError& error) {
			throw JNICNULLTerminatedError(error);
		}
	}

	template <typename T>
	jobject JNIHandler::newNativeResource(const char *clsName, T *ptr) noexcept(false)
	{
		try {
			return Util::newNativeResource(env, clsName, ptr);
		} catch (JNIError& ex) {
			throw JNINewInstanceError(ex);
		}
	}

	template <typename T>
	jobject JNIHandler::newNativeResource(jclass cls, T *ptr) noexcept(false)
	{
		try {
			return Util::newNativeResource(env, cls, ptr);
		} catch (JNIError& ex) {
			throw JNINewInstanceError(ex);
		}
	}
};


#endif /* UTIL_H */
