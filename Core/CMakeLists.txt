message(STATUS "*** Create Zinet Core Lib ***")

file(GLOB_RECURSE ZTCORE_FILES
     "include/*.h"
     "source/*.cpp"
)

add_library(ZtCore SHARED ${ZINET_LIBS_TYPE}
	${ZTCORE_FILES}
)

target_compile_features(ZtCore PUBLIC cxx_std_17)

set_target_properties(ZtCore PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_library(Zinet::Core ALIAS ZtCore)

set_target_properties(ZtCore
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtCore PRIVATE ${SFML_INCLUDE_DIRS})

target_link_libraries(ZtCore PRIVATE sfml-system sfml-window sfml-audio)
target_link_libraries(ZtCore PRIVATE spdlog)
target_link_libraries(ZtCore PRIVATE ImGui-SFML::ImGui-SFML)

# Propagate macro with current dir
set(ZINET_CURRENT_PROJECT_ROOT_PATH ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "*** ZtCore ZINET_CURRENT_PROJECT_ROOT_PATH: ${ZINET_CURRENT_PROJECT_ROOT_PATH} ***")
target_compile_definitions(ZtCore PRIVATE ${ZINET_CURRENT_PROJECT_ROOT_PATH})
unset(${ZINET_CURRENT_PROJECT_ROOT_PATH})

# Tests
add_subdirectory(tests)