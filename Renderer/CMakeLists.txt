message(STATUS "*** Create Zinet Renderer Lib ***")

add_library(ZtRenderer STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/ZtRenderer.h"
	
	
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtRender.cpp"
)

target_compile_features(ZtRenderer PUBLIC cxx_std_20)

set_target_properties(ZtRenderer PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

target_include_directories(ZtRenderer PRIVATE ${COLONY_INCLUDE_DIRS})

target_link_libraries(ZtRenderer PUBLIC ZtCore spdlog)

target_compile_definitions(ZtRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
if(TRUE)
	add_subdirectory(tests)
endif()