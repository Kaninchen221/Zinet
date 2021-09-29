message(STATUS "*** Create Glad library Lib ***")

add_library(Glad STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/Glad/Debug/include/glad/glad.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Glad/Debug/include/KHR/khrplatform.h"
	
	
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Glad/Debug/src/glad.c"
)

target_compile_features(Glad PUBLIC cxx_std_20)

set_target_properties(Glad PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Debug/include
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Debug/include
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

target_include_directories(Glad PRIVATE ${SFML_INCLUDE_DIRS} ${COLONY_INCLUDE_DIRS})

target_link_libraries(Glad PUBLIC spdlog)

target_compile_definitions(Glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
if(FALSE)
	add_subdirectory(tests)
endif()