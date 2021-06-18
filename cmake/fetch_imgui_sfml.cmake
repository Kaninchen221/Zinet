
message(STATUS "*** Fetch ImGui-SFML ***")

FetchContent_Declare(imgui-sfml
	GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml.git
	GIT_TAG v2.3
)

# Can't use IMGUI_INCLUDE_DIRS because the imgui-sfml must be build before imgui
set(IMGUI_DIR ${CMAKE_BINARY_DIR}/_deps/imgui-src)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

set(IMGUI-SFML_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/imgui-sfml-src/include
)

set_target_properties(ImGui-SFML
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime"
)