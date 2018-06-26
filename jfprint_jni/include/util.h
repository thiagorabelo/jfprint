
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


#define __TOSTR(i) #i
#define  _TOSTR(i) __TOSTR(i)
#define LOCATION_INFO __FILE__ ":" _TOSTR(__LINE__)

#ifdef DEBUG

template<typename T>
void __log(T const& t)
{
	std::cout << t;
}


template <typename T, typename... Ts>
void __log(T t, Ts const&... ts)
{
	std::cout << t;
	__log(ts...);
	std::cout << std::endl;
}

#define log(head, ...) __log(head, ##__VA_ARGS__);

#else
#define log(x, ...)
#endif

namespace Util {

	extern void* getPointerAddress(JNIEnv *env, jobject obj, const char *fieldName);
	extern void* setPointerAddress(JNIEnv *env, jobject obj, const char *fieldName, void *address, size_t size);

	template <typename RetType, typename DataType, typename AppliedFunc>
	RetType applyFuncToPointer(JNIEnv *env, jobject obj, const char *fieldName, AppliedFunc fn)
	{
		DataType **data = reinterpret_cast<DataType**>(Util::getPointerAddress(env, obj, fieldName));
		return static_cast<RetType>(fn(*data));
	}

	extern jobject newInstance(JNIEnv *env, const char *clsDescription);
	extern jobject newInstance(JNIEnv *env, jclass cls);

	extern jint throwException(JNIEnv *env, const char *message);


	namespace DiscoveredList {


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
		jobject nativeGet(JNIEnv *env, jobject obj, jint index, const char *clsName, const char *discoveredsName)
		{
		  DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));

		  if (NULL == discovereds) {
			  log(discoveredsName, " is empty. " LOCATION_INFO);
			  Util::throwException(env, "Can not retrieve discovered items. " LOCATION_INFO);
			  return NULL;
		  }

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
		jobject discoverPrints(JNIEnv *env, jclass cls, const char *ClassName, DiscoverFunc fn)
		{
			jfieldID fidSize = env->GetFieldID(cls, "size", "I");
			if (NULL == fidSize) {
				log("Can not access ", ClassName, " attribute 'size'. ", __FILE__, ":", __LINE__);
				Util::throwException(env, "Can not access size field (" LOCATION_INFO ")");
				return NULL;
			}

			// There is no need to create a pointer to pointer,
			// as this is done by the fprint library itself.
			DiscoveredType **discovereds = fn();
			size_t size = Util::DiscoveredList::getDiscoveredListSize(discovereds);

			jobject jdiscovered_list = Util::newInstance(env, cls);

			Util::setPointerAddress(env, jdiscovered_list, "pointer", discovereds, sizeof(DiscoveredType*));
			env->SetIntField(jdiscovered_list, fidSize, static_cast<int>(size));

			return jdiscovered_list;
		}

		template<typename DiscoveredType, typename FreeFunc>
		void nativeClose(JNIEnv *env, jobject obj, FreeFunc fn)
		{
			DiscoveredType **discovereds = reinterpret_cast<DiscoveredType**>(Util::getPointerAddress(env, obj, "pointer"));
			// Do not freed the pointer to pointer.
			// Let fprint do that.
			fn(discovereds);
		}
	};
};


#endif /* UTIL_H */

