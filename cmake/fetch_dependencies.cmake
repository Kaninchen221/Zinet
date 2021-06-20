
include(FetchContent)

# SFML https://www.sfml-dev.org/
include(cmake/fetch_sfml.cmake)

# Google Test library
include(cmake/fetch_gtest.cmake)

# Spdlog library
include(cmake/fetch_spdlog.cmake)

# Colony is a cache friendly container (better than standard containers)
include(cmake/fetch_colony.cmake)

# ImGui
include(cmake/fetch_imgui.cmake)
# ImGui-SFML
include(cmake/fetch_imgui_sfml.cmake)


# Pybind11 library for bind cpp to python
#include(cmake/fetch_pybind11.cmake)

# XML parser
#include(cmake/fetch_nlohmann_json.cmake)

# Box2D is library for 2D physics
#include(cmake/fetch_box2d.cmake)
