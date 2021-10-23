message(STATUS "*** Create Zinet Zinet Renderer Test executable ***")

add_executable(ZtRendererTest
	main.cpp
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtElementBufferTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtProgramTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtShaderTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtShaderTypeTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtVertexArrayTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtVertexBufferTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtVertexTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/tests/include/ZtWindowTests.h"
	
	
	
	
)

target_compile_features(ZtRendererTest PUBLIC cxx_std_20)

set_target_properties(ZtRendererTest PROPERTIES LINKER_LANGUAGE CXX)
	
target_compile_definitions(ZtRendererTest PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

set_target_properties(ZtRendererTest
    PROPERTIES
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtRendererTest PUBLIC ${COLONY_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

target_compile_definitions(ZtRendererTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ZtRendererTest PUBLIC spdlog gtest gmock Glad glfw ZtRenderer)
