#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/jfprint_Core.o \
	${OBJECTDIR}/src/jfprint_Device.o \
	${OBJECTDIR}/src/jfprint_DiscoveredDevice.o \
	${OBJECTDIR}/src/jfprint_DiscoveredDeviceList.o \
	${OBJECTDIR}/src/jfprint_DiscoveredPrint.o \
	${OBJECTDIR}/src/jfprint_DiscoveredPrintList.o \
	${OBJECTDIR}/src/jfprint_Driver.o \
	${OBJECTDIR}/src/jfprint_Img.o \
	${OBJECTDIR}/src/jfprint_PrintData.o \
	${OBJECTDIR}/src/util.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/libfprint/lib -lfprint

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjfprintjni.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjfprintjni.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libjfprintjni.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,--no-undefined -shared -fPIC

${OBJECTDIR}/src/jfprint_Core.o: src/jfprint_Core.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_Core.o src/jfprint_Core.cpp

${OBJECTDIR}/src/jfprint_Device.o: src/jfprint_Device.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_Device.o src/jfprint_Device.cpp

${OBJECTDIR}/src/jfprint_DiscoveredDevice.o: src/jfprint_DiscoveredDevice.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_DiscoveredDevice.o src/jfprint_DiscoveredDevice.cpp

${OBJECTDIR}/src/jfprint_DiscoveredDeviceList.o: src/jfprint_DiscoveredDeviceList.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_DiscoveredDeviceList.o src/jfprint_DiscoveredDeviceList.cpp

${OBJECTDIR}/src/jfprint_DiscoveredPrint.o: src/jfprint_DiscoveredPrint.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_DiscoveredPrint.o src/jfprint_DiscoveredPrint.cpp

${OBJECTDIR}/src/jfprint_DiscoveredPrintList.o: src/jfprint_DiscoveredPrintList.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_DiscoveredPrintList.o src/jfprint_DiscoveredPrintList.cpp

${OBJECTDIR}/src/jfprint_Driver.o: src/jfprint_Driver.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_Driver.o src/jfprint_Driver.cpp

${OBJECTDIR}/src/jfprint_Img.o: src/jfprint_Img.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_Img.o src/jfprint_Img.cpp

${OBJECTDIR}/src/jfprint_PrintData.o: src/jfprint_PrintData.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/jfprint_PrintData.o src/jfprint_PrintData.cpp

${OBJECTDIR}/src/util.o: src/util.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -I/usr/local/libfprint/include -Iinclude -std=c++14 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/util.o src/util.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
