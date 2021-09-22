message(STATUS "*** Create Zinet EntryPoint executable ***")

file(GLOB_RECURSE ZTENTRYPOINT_FILES CONFIGURE_DEPENDS
     "include/*.h"
     "source/*.cpp"
)

add_executable(ZtEntryPoint
	source/main.cpp
	${ZTENTRYPOINT_FILES}
)

target_compile_features(ZtEntryPoint PUBLIC cxx_std_20)

set_target_properties(ZtEntryPoint PROPERTIES 
	LINKER_LANGUAGE CXX
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
	INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set_target_properties(ZtEntryPoint
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtEntryPoint PRIVATE ${SFML_INCLUDE_DIRS} ${COLONY_INCLUDE_DIRS})

target_link_libraries(ZtEntryPoint PRIVATE sfml-system sfml-window sfml-audio)
target_link_libraries(ZtEntryPoint PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(ZtEntryPoint PRIVATE spdlog)
target_link_libraries(ZtEntryPoint PRIVATE ZtCore)

# Propagate macro with current dir
set(ZINET_CURRENT_PROJECT_ROOT_PATH ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "*** ZtEntryPoint ZINET_CURRENT_PROJECT_ROOT_PATH: ${ZINET_CURRENT_PROJECT_ROOT_PATH} ***")
target_compile_definitions(ZtEntryPoint PRIVATE ${ZINET_CURRENT_PROJECT_ROOT_PATH})
unset(${ZINET_CURRENT_PROJECT_ROOT_PATH})
