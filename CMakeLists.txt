set(TARGET_NAME "pico_rotary_encoder")

if (NOT TARGET ${TARGET_NAME})
    add_library(${TARGET_NAME} INTERFACE)

    target_sources(${TARGET_NAME} INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/encoder.c
    )

    target_include_directories(${TARGET_NAME} INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}
    )

    target_link_libraries(${TARGET_NAME} INTERFACE
        pico_stdlib
    )
    
    # Note: Projects using this library must also link the button library
    # The encoder library depends on button.h for the listen() function
endif()
