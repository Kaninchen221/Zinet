
set(ZINET_LIBS_TYPE "SHARED" CACHE STRING "Must be SHARED or STATIC")

if(${ZINET_LIBS_TYPE} STREQUAL "SHARED" OR ${ZINET_LIBS_TYPE} STREQUAL "STATIC")
	message(STATUS "*** Zinet Libs Type : ${ZINET_LIBS_TYPE} ***")
else()
	message(FATAL_ERROR "*** INVALID Zinet Libs Type : ${ZINET_LIBS_TYPE} ***")
endif()