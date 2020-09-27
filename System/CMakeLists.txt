message(STATUS "*** Create Zinet System Lib ***")

add_library(ZtSystem ${ZINET_LIBS_TYPE}
	include/Zinet/System/ZtSystem.h
)

set_target_properties(ZtSystem PROPERTIES 
	LINKER_LANGUAGE CXX
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::System ALIAS ZtSystem)

target_compile_definitions(ZtSystem PUBLIC ZINET_SYSTEM_EXPORT)