message(STATUS "*** Create Entry Point executable ***")

add_executable(ZtEntryPoint
	"C:/Users/Kaninchen/Desktop/Zinet2/EntryPoint/include/ZtEntryPoint.h"
	
	
	
	"C:/Users/Kaninchen/Desktop/Zinet2/EntryPoint/source/main.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/EntryPoint/source/ZtEntryPoint.cpp"
)

target_compile_features(ZtEntryPoint PUBLIC cxx_std_20)

set_target_properties(ZtEntryPoint PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

target_include_directories(ZtEntryPoint PRIVATE ${SFML_INCLUDE_DIRS} ${COLONY_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})

target_link_libraries(ZtEntryPoint PUBLIC spdlog Glad glfw ZtGraphicLayer)

target_compile_definitions(ZtEntryPoint PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
