message(STATUS "*** Create Zinet Zinet Graphic Layer Test executable ***")

add_executable(ZtGraphicLayerTest
	main.cpp
	
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtElementBufferTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtEventTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtGLContextTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtGLDebugUtilsMessengerTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtGLGLFWTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtGLInstanceTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtGLPhysicalDeviceTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtKeyboardEventTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtKeyboardEventTypeTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtKeyboardKeyTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtKeyboardTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMouseButtonEventTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMouseButtonEventTypeTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMouseButtonTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMousePositionEventTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMouseScrollEventTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtMouseTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtObjectTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtProgramTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtShaderTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtShaderTypeTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtTextureTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtVertexArrayTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtVertexBufferTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtVertexTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/GraphicLayer/tests/include/ZtWindowTests.h"
	
	
	
	
)

target_compile_features(ZtGraphicLayerTest PUBLIC cxx_std_20)

set_target_properties(ZtGraphicLayerTest PROPERTIES LINKER_LANGUAGE CXX)
	
target_compile_definitions(ZtGraphicLayerTest PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

set_target_properties(ZtGraphicLayerTest
    PROPERTIES
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtGraphicLayerTest PUBLIC ${COLONY_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${STB_INCLUDE_DIRS} ${VULKAN_HPP_INCLUDE_DIRS})

target_compile_definitions(ZtGraphicLayerTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ZtGraphicLayerTest PUBLIC spdlog gtest gmock glfw ZtGraphicLayer)
