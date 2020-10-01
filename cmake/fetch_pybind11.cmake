
message(STATUS "*** Fetch PyBind11 ***")

FetchContent_Declare(PyBind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(PyBind11)

set(PYBIND11_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/pybind11-src/include
)