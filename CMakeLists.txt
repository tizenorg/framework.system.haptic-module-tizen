CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(haptic-module C)

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(EXEC_PREFIX "\${prefix}")
SET(LIBDIR "\${prefix}/lib")
SET(INCLUDEDIR "\${prefix}/include/${PROJECT_NAME}")
SET(VERSION 0.1)

INCLUDE(FindPkgConfig)
pkg_check_modules(rpkgs REQUIRED
                dlog
                vconf
                haptic-plugin
				devman)
ADD_DEFINITIONS(${rpkgs_CFLAGS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

FIND_PROGRAM(UNAME NAMES uname)
EXEC_PROGRAM("${UNAME}" ARGS "-m" OUTPUT_VARIABLE "ARCH")

IF("${ARCH}" MATCHES "^arm.*")
	SET(TIZEN_TARGET "ARM")
ELSE("${ARCH}" MATCHES "^arm.*")
	SET(TIZEN_TARGET "SIMULATOR")
ENDIF("${ARCH}" MATCHES "^arm.*")

SET(TIZEN_PATH_PREFIX tizen/${TIZEN_TARGET})

SET(SRCS
	${TIZEN_PATH_PREFIX}/src/haptic_module_internal.c)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -fvisibility=hidden")
SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -g -fno-omit-frame-pointer -finstrument-functions")
SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -Wl,--no-as-needed")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${rpkgs_LDFLAGS} ${GLES_LDFLAGS})

ADD_DEFINITIONS("-DPREFIX=\"${PREFIX}\"")
ADD_DEFINITIONS("-DFACTORYFS=\"$ENV{FACTORYFS}\"")

ADD_EXECUTABLE(test1 test/test.c)
TARGET_LINK_LIBRARIES(test1 "-ldl")

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION lib/haptic)
INSTALL(TARGETS test1 DESTINATION bin)
