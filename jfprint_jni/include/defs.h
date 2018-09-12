
/*
 * File:   defs.h
 * Author: thiago
 *
 * Created on 12 de Setembro de 2018, 11:40
 */

#ifndef DEFS_H
#define DEFS_H

/** For location log/error information **/

#define __TOSTR(i) #i
#define  _TOSTR(i) __TOSTR(i)
#define LOCATION_INFO __FILE__ ":" _TOSTR(__LINE__)
#define FUNC_DESC __PRETTY_FUNCTION__


/** Helper to build Java Class JNI style name **/

#define CLASS_PATH(cls) "Ljfprint/" #cls ";"


/** Java Class JNI style name **/

#define CLASS_NATIVE_RESOURCE                    CLASS_PATH(base/NativeResource)

#define CLASS_CORE                               CLASS_PATH(Core)
#define CLASS_DEVICE                             CLASS_PATH(Device)
#define CLASS_DISCOVERED_DEVICE                  CLASS_PATH(DiscoveredDevice)
#define CLASS_DISCOVERED_PRINT_LIST              CLASS_PATH(DiscoveredPrintList)
#define CLASS_DISCOVERED_PRINT                   CLASS_PATH(DiscoveredPrint)
#define CLASS_DISCOVERED_DEVICE_LIST             CLASS_PATH(DiscoveredDeviceList)
#define CLASS_DRIVER                             CLASS_PATH(Driver)
#define CLASS_IMG                                CLASS_PATH(Img)
#define CLASS_PRINT_DATA                         CLASS_PATH(PrintData)

#define CLASS_CODE_ERROR                         CLASS_PATH(exception/CodeError)
#define CLASS_CLASS_NATIVE_EXCEPTION             CLASS_PATH(exception/ClassNativeException)
#define CLASS_NATIVE_EXCEPTION                   CLASS_PATH(exception/NativeException)
#define CLASS_NATIVE_CAN_NOT_FIND_EXCEPTION      CLASS_PATH(exception/NativeCanNotFindException)
#define CLASS_OPERATION_ERROR                    CLASS_PATH(exception/OperationError)
#define CLASS_RESOURCE_ALREADY_CLOSED_EXCEPTION  CLASS_PATH(exception/ResourceAlreadyClosedException)

#define CLASS_WRAPPER                            CLASS_PATH(util/Wrapper)
#define CLASS_RESULT_TUPLE                       CLASS_PATH(util/ResultTuple)



/** Error messages **/

#define CAN_NOT_ACCESS_POINTER(cls)          "Can not access " cls " 'pointer'"
#define CAN_NOT_SET_POINTER(cls)             "Can not set " cls " 'pointer'"
#define CAN_NOT_RETRIEVE_POINTER(txt)        "Can not retrieve native " txt
#define CAN_NOT_INSTANTIATE(cls)             "Can not instantiate " cls
#define CAN_NOT_RETRIEVE_CLASS(cls)          "Can not retrieve " cls ".class"
#define CAN_NOT_RETRIEVE_WRAPPER_CLASS(cls)  "Can not retrieve Class<Wrapper<" cls ">>"
#define CAN_NOT_ACCESS_OBJ_IN_WRAPPER(cls)   "Can not access 'obj' field in Wrapper<" cls ">"
#define CAN_NOT_SET_OBJ_IN_WRAPPER(cls)      "Can not set 'obj' field in Wrapper<" cls ">"


/** Generic Error messages **/

#define UNABLE_OPEN_DEVICE                   "Unable to open native device"
#define CAN_NOT_RETRIEVE_DRIVER_ID           "Can not retrieve driver id"
#define CAN_NOT_RETRIEVE_DRIVER_ID           "Can not retrieve driver id"
#define CAN_NOT_RETRIEVE_DRIVER_TYPE         "Can not retrieve driver type"
#define CAN_NOT_RETRIEVE_DRIVER_NAME         "Can not retrieve driver name"
#define CAN_NOT_RETRIEVE_DRIVER_FULL_NAME    "Can not retrieve driver full name"
#define UNABLE_POPULATE_BYTE_ARRAY           "Unable to populate the Java byte array"
#define CAN_NOT_CREATE_C_STRING              "Can not create C style string"
#define UNABLE_GET_PRINT_DATA                "Unable to get native print data"
#define CAN_NOT_LOAD_PRINT_DATA              "Can not load fp_print_data"

#define CAN_NOT_ACCESS_DISCOVERED(txt)       "Can not access " txt
#define CAN_NOT_ACCESS_DISCOVERED_LIST(txt)  "Can not access the list of " txt


#endif /* DEFS_H */

