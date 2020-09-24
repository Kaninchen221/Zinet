
message(STATUS "*** Fetch PyBind11 ***")

FetchContent_Declare(PyBind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(PyBind11)

# Create var contains PyBind11 include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/pybind11-src/include
)