message(STATUS "*** Create Zinet Renderer Lib ***")

add_library(ZtRenderer STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtBufferUsage.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtElementBuffer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtProgram.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtRenderer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtShader.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtShaderType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtVertex.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtVertexArray.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtVertexBuffer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/include/Zinet/Renderer/ZtWindow.h"
	
	
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtElementBuffer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtProgram.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtRender.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtShader.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtVertex.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtVertexArray.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtVertexBuffer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Renderer/source/ZtWindow.cpp"
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

target_include_directories(ZtRenderer PRIVATE ${COLONY_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})

target_link_libraries(ZtRenderer PUBLIC ZtCore spdlog Glad glfw)

target_compile_definitions(ZtRenderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
if(TRUE)
	add_subdirectory(tests)
endif()