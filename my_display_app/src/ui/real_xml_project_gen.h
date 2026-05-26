/**
 * @file real_xml_project_gen.h
 */

#ifndef REAL_XML_PROJECT_GEN_H
#define REAL_XML_PROJECT_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
    #include "lvgl_private.h"
#else
    #include "lvgl/lvgl.h"
    #include "lvgl/lvgl_private.h"
#endif

#ifdef LV_USE_XML
    #include "lv_xml/lv_xml.h"
#endif



/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

extern lv_font_t * font_brewing;

extern lv_font_t * font_status;

/*----------------
 * Images
 *----------------*/

extern const void * coffee_maker_hero;
extern const void * caramel_frappe;
extern const void * latte;
extern const void * mocha_cream;
extern const void * caramel_macchiato;
extern const void * frame_3;

/*----------------
 * Subjects
 *----------------*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void real_xml_project_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widgets, components and screens of this library*/
#include "screens/drinkscreen_gen.h"
#include "screens/finalscreen_gen.h"
#include "screens/homescreen_gen.h"
#include "screens/orderscreen_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*REAL_XML_PROJECT_GEN_H*/