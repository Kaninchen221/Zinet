
target_include_directories(Sandbox PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(Sandbox PRIVATE ${ZT_SYSTEM_INCLUDE_DIR})

target_include_directories(ZtMain PRIVATE ${ZT_CORE_INCLUDE_DIR})
target_include_directories(ZtMain PRIVATE ${SPDLOG_INCLUDE_DIRS})
