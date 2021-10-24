
include(FetchContent)

# Google Test library
include(cmake/fetch_gtest.cmake)

# Spdlog library
include(cmake/fetch_spdlog.cmake)

# Colony is a cache friendly container (better than standard containers)
include(cmake/fetch_colony.cmake)

# ImGui
include(cmake/fetch_imgui.cmake)

# GLFW
include(cmake/fetch_glfw.cmake)

# GLM
include(cmake/fetch_glm.cmake)

# STB
include(cmake/fetch_stb.cmake)

# Pybind11 library for bind cpp to python
#include(cmake/fetch_pybind11.cmake)

# XML parser
#include(cmake/fetch_nlohmann_json.cmake)

# Box2D is library for 2D physics
#include(cmake/fetch_box2d.cmake)
