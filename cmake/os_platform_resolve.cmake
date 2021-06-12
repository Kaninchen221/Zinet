
if(MSVC OR MSYS) # Windows OS
	
	message(STATUS "*** OS: Windows ***")
	multiple_targets_compile_definitions("${ZINET_LIBS_NAME}" "ZINET_WINDOWS")
	
#elseif(UNIX AND NOT APPLE) # Linux OS
	
	#message(STATUS "*** OS: Linux ***")
	#multiple_targets_compile_definitions("${ZINET_LIBS_NAME}" "ZINET_LINUX")
	
else()

	message(FATAL_ERROR "*** OS: NOT SUPPORTED ***")
	
endif()