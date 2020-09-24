
message(STATUS "*** Fetch Box2D ***")

FetchContent_Declare(Box2D
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v2.4.0
)

FetchContent_MakeAvailable(Box2D)

# Create var contains SPDLOG include dir
set(SPDLOG_INCLUDE_DIRS PRIVATE 
	build/_deps/spdlog-src/include
)
