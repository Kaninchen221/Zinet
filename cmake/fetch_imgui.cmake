
message(STATUS "*** Fetch ImGui ***")

FetchContent_Declare(imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.83
)

FetchContent_MakeAvailable(imgui)

set(IMGUI_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/imgui-src
)