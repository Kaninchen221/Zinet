###########################
# SFML

message(STATUS "*** Fetch SFML ***")

FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(SFML)

# Create var contains SFML include dir
set(SFML_INCLUDE_DIRS PUBLIC 
	build/_deps/sfml-src/include
)

###########################
# Google Test

message(STATUS "*** Fetch Google Test ***")

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

# Create var contains Google Test include dir
set(GOOGLETEST_INCLUDE_DIRS PRIVATE 
	build/_deps/googletest-src/googletest/include
)

# Create var contains Google Mock include dir
set(GOOGLEMOCK_INCLUDE_DIRS PRIVATE 
	build/_deps/googletest-src/googlemock/include
)

###########################
# SPDLOG

message(STATUS "*** Fetch SPDLOG ***")

FetchContent_Declare(SPDLOG
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.5.0
)

FetchContent_MakeAvailable(SPDLOG)

# Create var contains SPDLOG include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/spdlog-src/include
)

###########################
# PyBind11

message(STATUS "*** Fetch PyBind11 ***")

FetchContent_Declare(PyBind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(PyBind11)

# Create var contains PyBind11 include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/PyBind11-src/include
)