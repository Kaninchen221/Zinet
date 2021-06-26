message(STATUS "*** Create Zinet CoreTests executable ***")

file(GLOB_RECURSE ZTCORETESTS_FILES CONFIGURE_DEPENDS
     "include/*.h"
)

add_executable(ZtCoreTests
	main.cpp
	${ZTCORETESTS_FILES}
)

target_compile_features(ZtCoreTests PUBLIC cxx_std_17)

set_target_properties(ZtCoreTests PROPERTIES LINKER_LANGUAGE CXX)
	
target_compile_definitions(ZtCoreTests PUBLIC GTEST_LINKED_AS_SHARED_LIBRARY)

set_target_properties(ZtCoreTests
    PROPERTIES
	LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)

target_include_directories(ZtCoreTests PUBLIC "include/" ${COLONY_INCLUDE_DIRS})

message(STATUS "*** COLONY_INCLUDE_DIRS ${COLONY_INCLUDE_DIRS}")

# Propagate macro with current dir
set(ZINET_CURRENT_PROJECT_ROOT_PATH ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "*** ZtCoreTests ZINET_CURRENT_PROJECT_ROOT_PATH: ${ZINET_CURRENT_PROJECT_ROOT_PATH} ***")
target_compile_definitions(ZtCoreTests PRIVATE ${ZINET_CURRENT_PROJECT_ROOT_PATH})
unset(${ZINET_CURRENT_PROJECT_ROOT_PATH})

target_link_libraries(ZtCoreTests PUBLIC gtest gmock)
target_link_libraries(ZtCoreTests PUBLIC ZtCore)
target_link_libraries(ZtCoreTests PUBLIC sfml-system sfml-window sfml-audio)
target_link_libraries(ZtCoreTests PUBLIC spdlog)
