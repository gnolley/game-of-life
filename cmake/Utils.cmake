
if(${ENABLE_WARNINGS})
    include(Warnings)
endif()

if(${ENABLE_LTO})
    include(LTO)
endif()

function(setup_target TARGET_NAME)

	if(${ENABLE_WARNINGS})
	    target_set_warnings(${TARGET_NAME} ${ENABLE_WARNINGS_AS_ERRORS})
    endif()

    if(${ENABLE_LTO})
        target_enable_lto(${TARGET_NAME})
    endif()

endfunction()