message(STATUS "*** Create Zinet Graphic Layer Lib ***")

add_library(ZtGraphicLayer STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtBufferUsage.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtElementBuffer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLContext.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLDebugUtilsMessenger.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLDevice.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLGLFW.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLImageView.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLInstance.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLPipeline.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLPipelineLayout.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLProgram.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLQueue.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLRenderer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLRenderPass.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLShader.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLShaderModule.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLShaderType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLSurface.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLSwapChain.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGLWindow.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtGraphicLayer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboard.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardEventType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtKeyboardKey.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMouse.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMouseButton.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMouseButtonEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMouseButtonEventType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMousePositionEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtMouseScrollEvent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtObject.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtTexture.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertex.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertexArray.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/include/Zinet/GraphicLayer/ZtVertexBuffer.h"

	

	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtElementBuffer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLContext.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLDebugUtilsMessenger.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLDevice.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLGLFW.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLImageView.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLInstance.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLPhysicalDevice.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLPipeline.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLPipelineLayout.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLProgram.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLQueue.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLRenderer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLRenderPass.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLShader.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLShaderModule.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLShaderType.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLSurface.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLSwapChain.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLSwapChainSupportDetails.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGLWindow.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtGraphicLayer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtKeyboard.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtKeyboardEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtMouse.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtMouseButtonEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtMousePositionEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtMouseScrollEvent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtObject.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtTexture.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertex.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertexArray.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/source/ZtVertexBuffer.cpp"
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

target_include_directories(ZtGraphicLayer PUBLIC ${CONAN_INCLUDE_DIRS_SPDLOG} ${CONAN_INCLUDE_DIRS_PLF_COLONY} ${CONAN_INCLUDE_DIRS_FMT} ${CONAN_INCLUDE_DIRS_GLFW} ${CONAN_INCLUDE_DIRS_GLM} ${CONAN_INCLUDE_DIRS_STB} ${Vulkan_INCLUDE_DIRS})

target_link_libraries(ZtGraphicLayer PUBLIC ZtCore)

target_compile_definitions(ZtGraphicLayer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
if(TRUE)
	add_subdirectory(tests)
endif()
