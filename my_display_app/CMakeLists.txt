cmake_minimum_required(VERSION 3.20.0)

set(BOARD "mimxrt1170_evk@B/mimxrt1176/cm7" CACHE STRING "Zephyr board target")
set(SHIELD "rk055hdmipi4ma0" CACHE STRING "Zephyr display shield")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(my_display_app)

target_sources(app PRIVATE src/main.c)
target_compile_definitions(app PRIVATE LV_LVGL_H_INCLUDE_SIMPLE=1)

set(UI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/ui)
set(UI_SQUARELINE_FILE ${UI_DIR}/ui.c)
set(UI_LV_EDITOR_FILE_LIST ${UI_DIR}/file_list_gen.cmake)
set(UI_LV_EDITOR_ENTRY ${UI_DIR}/testtool.c)
set(UI_PUBLIC_INCLUDE_DIR ${UI_DIR}/include)
set(UI_PRIVATE_INCLUDE_DIR ${UI_DIR}/priv_include)
set(UI_SOURCE_DIR ${UI_DIR}/src)
set(UI_PRIVATE_SOURCE_DIR ${UI_DIR}/priv_src)
set(UI_GENERATED_DIR ${UI_SOURCE_DIR}/generated)
set(UI_CUSTOM_DIR ${UI_SOURCE_DIR}/custom)

if(EXISTS ${UI_SQUARELINE_FILE} AND EXISTS ${UI_DIR}/ui.h)
    file(GLOB_RECURSE UI_SQUARELINE_SOURCES CONFIGURE_DEPENDS
        ${UI_DIR}/*.c
    )

    target_include_directories(app PRIVATE
        ${UI_DIR}
    )

    target_sources(app PRIVATE ${UI_SQUARELINE_SOURCES})
    target_compile_definitions(app PRIVATE APP_HAS_SQUARELINE_UI=1)
elseif(EXISTS ${UI_LV_EDITOR_FILE_LIST})
    include(${UI_LV_EDITOR_FILE_LIST})
    include(${UI_DIR}/user_config.cmake OPTIONAL)

    target_include_directories(app PRIVATE
        ${UI_DIR}
    )

    target_sources(app PRIVATE ${LV_EDITOR_PROJECT_SOURCES})
    if(EXISTS ${UI_LV_EDITOR_ENTRY} AND EXISTS ${UI_DIR}/testtool.h)
        target_compile_definitions(app PRIVATE APP_HAS_LV_EDITOR_UI=1)
    else()
        target_compile_definitions(app PRIVATE APP_HAS_REAL_XML_UI=1)
    endif()
else()
    file(GLOB_RECURSE UI_SOURCES CONFIGURE_DEPENDS
        ${UI_SOURCE_DIR}/*.c
        ${UI_PRIVATE_SOURCE_DIR}/*.c
    )

    if(UI_SOURCES)
        target_include_directories(app PRIVATE
            ${UI_PUBLIC_INCLUDE_DIR}
            ${UI_PRIVATE_INCLUDE_DIR}
            ${UI_SOURCE_DIR}
            ${UI_GENERATED_DIR}
            ${UI_GENERATED_DIR}/guider_customer_fonts
            ${UI_GENERATED_DIR}/guider_fonts
            ${UI_GENERATED_DIR}/images
            ${UI_CUSTOM_DIR}
        )

        target_sources(app PRIVATE ${UI_SOURCES})
    endif()

    if(EXISTS ${UI_SOURCE_DIR}/ui_frame_1.c)
        target_compile_definitions(app PRIVATE APP_HAS_FRAME_UI=1)
    endif()

    if(EXISTS ${UI_GENERATED_DIR}/gui_guider.c AND
       EXISTS ${UI_GENERATED_DIR}/gui_guider.h AND
       EXISTS ${UI_GENERATED_DIR}/events_init.c AND
       EXISTS ${UI_GENERATED_DIR}/events_init.h)
        target_compile_definitions(app PRIVATE APP_HAS_GENERATED_UI=1)
    endif()
endif()
