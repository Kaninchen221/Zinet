message(STATUS "*** Create Zinet Zinet Core Test executable ***")

add_executable(ZtCoreTest
	main.cpp
	
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtClockTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtEventBroadcasterTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtFileFinderTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtFileTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtIdentifierTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtLoggerTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtTimeTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/ZtUniqueIdentifierMakerTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/OCS/ZtComponentTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/OCS/ZtObjectTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/OCS/ZtSystemTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedClassMacroTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedClassTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedCollectionTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedMemberFunctionMacroTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedMemberFunctionTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedMemberPropertyMacroTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectedMemberPropertyTests.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectionTestStruct.h"
	"C:/Users/Kaninchen/Desktop/Zinet2/Core/tests/include/Reflection/ZtReflectionUtilitiesTests.h"
	
	
	
	
)

target_compile_features(ZtCoreTest PUBLIC cxx_std_20)

set_target_properties(ZtCoreTest PROPERTIES LINKER_LANGUAGE CXX)
	
target_compile_definitions(ZtCoreTest PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

set_target_properties(ZtCoreTest
    PROPERTIES
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtCoreTest PUBLIC ${CONAN_INCLUDE_DIRS_SPDLOG} ${CONAN_INCLUDE_DIRS_GTEST} ${CONAN_INCLUDE_DIRS_PLF_COLONY} ${CONAN_INCLUDE_DIRS_FMT})

target_compile_definitions(ZtCoreTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ZINET_WINDOWS ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(ZtCoreTest PUBLIC ZtCore ${CONAN_LIBS_SPDLOG} ${CONAN_LIBS_GTEST} ${CONAN_LIBS_FMT})
