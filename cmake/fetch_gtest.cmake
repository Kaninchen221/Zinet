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