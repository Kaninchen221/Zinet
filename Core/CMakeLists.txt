message(STATUS "*** Create Zinet Core Lib ***")

add_library(ZtCore SHARED STATIC
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtBeginPlayReason.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtClock.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtColor.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtCore.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtEndPlayReason.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtEventBroadcaster.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtEventCallback.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtFileFinder.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtFunctor.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtIdentifier.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtLevel.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtLogger.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtLoop.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtMacroUtilities.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtRenderer.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtRenderType.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtSprite.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtTime.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtUniqueIdentifierMaker.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/ZtWorld.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/OCS/ZtComponent.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/OCS/ZtObject.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/OCS/ZtSystem.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedClass.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedClassMacro.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedCollection.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedMemberFunctionMacro.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectedMemberPropertyMacro.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectionUtilities.h"
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/include/Zinet/Core/Reflection/ZtReflectionUtilities.inl"
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtClock.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtFileFinder.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtIdentifier.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtLevel.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtLogger.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtLoop.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtRenderer.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtSprite.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtTime.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtUniqueIdentifierMaker.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/ZtWorld.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/OCS/ZtComponent.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/OCS/ZtObject.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/OCS/ZtSystem.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedClass.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedClassMacro.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedCollection.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedMemberFunction.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedMemberFunctionMacro.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedMemberProperty.cpp"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/source/Reflection/ZtReflectedMemberPropertyMacro.cpp"
)

target_compile_features(ZtCore PUBLIC cxx_std_20)

set_target_properties(ZtCore PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

target_include_directories(ZtCore PRIVATE ${SFML_INCLUDE_DIRS} ${COLONY_INCLUDE_DIRS})

target_link_libraries(ZtCore PUBLIC sfml-system sfml-window sfml-audio spdlog ImGui-SFML::ImGui-SFML)

target_compile_definitions(ZtCore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

# Tests
add_subdirectory(tests)