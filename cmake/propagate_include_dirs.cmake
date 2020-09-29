
function(propagate_include_dirs)

	get_property(ZT_CORE_INCLUDE_DIR TARGET ZtCore PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
	message(STATUS "*** ZtCore include path: ${ZT_CORE_INCLUDE_DIR} ***")
	
	get_property(ZT_SYSTEM_INCLUDE_DIR TARGET ZtSystem PROPERTY INCLUDE_DIRECTORIES)
	message(STATUS "*** ZtSystem include path: ${ZT_SYSTEM_INCLUDE_DIR} ***")

endfunction()