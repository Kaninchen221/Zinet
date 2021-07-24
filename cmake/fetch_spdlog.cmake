
message(STATUS "*** Fetch SPDLOG ***")

FetchContent_Declare(SPDLOG
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.9.0
)

FetchContent_MakeAvailable(SPDLOG)

set(SPDLOG_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/spdlog-src/include
)

set_target_properties( spdlog
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)