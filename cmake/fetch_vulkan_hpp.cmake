
message(STATUS "*** Fetch Vulkan Hpp ***")

FetchContent_Declare(Vulkan_Hpp
  GIT_REPOSITORY https://github.com/Kaninchen221/Vulkan-Hpp.git
  GIT_TAG master
)

FetchContent_MakeAvailable(Vulkan_Hpp)

set_target_properties(RAII_utils PROPERTIES LINKER_LANGUAGE C++) # Fix cmake build time error

set(VULKAN_HPP_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/vulkan_hpp-src/Vulkan-Headers/include
)

set_target_properties(glslang PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

set_target_properties(SPIRV PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive/
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime
)

set(GLM_INCLUDE_DIRS
	${CMAKE_BINARY_DIR}/_deps/vulkan_hpp-src/glm
)

set(GLSLANG_INCLUDE_DIRS
  ${CMAKE_BINARY_DIR}/_deps/vulkan_hpp-src/Vulkan-Headers/vulkan_hpp-src/glslang
)

find_package(Vulkan REQUIRED FATAL_ERROR)
