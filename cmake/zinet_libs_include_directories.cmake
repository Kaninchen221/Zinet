
# Sandbox
target_include_directories(Sandbox PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(Sandbox PRIVATE ${ZT_FRAME_INCLUDE_DIR})

# ZtMain
target_include_directories(ZtMain PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(ZtMain PRIVATE ${SPDLOG_INCLUDE_DIRS})

# ZtFrame
target_include_directories(ZtFrame PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(ZtFrame PRIVATE ${ZT_MAIN_INCLUDE_DIR})
target_include_directories(ZtFrame PRIVATE ${SFML_INCLUDE_DIRS})