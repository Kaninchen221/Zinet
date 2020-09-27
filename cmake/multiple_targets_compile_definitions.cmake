
function(multiple_targets_compile_definitions TARGETS_NAME DEFINITIONS)
	
	foreach(TARGET_NAME IN LISTS TARGETS_NAME)
	
		#message(STATUS "Target: ${TARGET_NAME}")
	
		foreach(DEFINITION IN LISTS DEFINITIONS)
		
			#message(STATUS "Definition: ${DEFINITION}")
		
			target_compile_definitions(${TARGET_NAME} PUBLIC ${DEFINITION})
		
		endforeach()
	
	endforeach()

endfunction()