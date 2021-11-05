message(STATUS "*** Create Zinet Graphic Layer Lib ***")

add_library(ZtGraphicLayer STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtBufferUsage.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtElementBuffer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLContext.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGraphicLayer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboard.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardEventType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardKey.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtObject.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtProgram.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtShader.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtShaderType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtTexture.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertex.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertexArray.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertexBuffer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtWindow.h"
	
	
	
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtElementBuffer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLContext.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGraphicLayer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtKeyboard.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtKeyboardEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtObject.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtProgram.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtShader.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtTexture.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertex.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertexArray.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertexBuffer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtWindow.cpp"
)

target_compile_features(ZtGraphicLayer PUBLIC cxx_std_20)

set_target_properties(ZtGraphicLayer PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

target_include_directories(ZtGraphicLayer PRIVATE ${COLONY_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})

target_link_libraries(ZtGraphicLayer PUBLIC ZtCore spdlog Glad glfw)

target_compile_definitions(ZtGraphicLayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
if(TRUE)
	add_subdirectory(tests)
endif()