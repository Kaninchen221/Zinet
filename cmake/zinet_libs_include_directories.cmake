
function(zinet_libs_include_directories)

	target_include_directories(Sandbox PRIVATE ${ZT_CORE_INCLUDE_DIR})
	target_include_directories(Sandbox PRIVATE ${ZT_SYSTEM_INCLUDE_DIR})
	target_include_directories(ZtSystem PRIVATE ${ZT_CORE_INCLUDE_DIR})

endfunction()