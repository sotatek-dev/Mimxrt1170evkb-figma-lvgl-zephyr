/**
 * @file homescreen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "homescreen_gen.h"
#include "../real_xml_project.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * homescreen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;
    static lv_style_t style_home_button;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_main);
        lv_style_set_bg_color(&style_main, lv_color_hex(0x000000));
        lv_style_set_bg_opa(&style_main, (255 * 100 / 100));
        lv_style_set_pad_all(&style_main, 0);
        lv_style_set_border_width(&style_main, 0);

        lv_style_init(&style_home_button);
        lv_style_set_bg_color(&style_home_button, lv_color_hex(0x2c2c2c));
        lv_style_set_bg_opa(&style_home_button, (255 * 100 / 100));
        lv_style_set_border_color(&style_home_button, lv_color_hex(0x2c2c2c));
        lv_style_set_border_opa(&style_home_button, (255 * 100 / 100));
        lv_style_set_border_width(&style_home_button, 1);
        lv_style_set_radius(&style_home_button, 8);
        lv_style_set_pad_all(&style_home_button, 12);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "homescreen_#");
    lv_obj_set_width(lv_obj_0, 1280);
    lv_obj_set_height(lv_obj_0, 720);

    lv_obj_add_style(lv_obj_0, &style_main, 0);
    lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
    lv_image_set_src(lv_image_0, coffee_maker_hero);
    lv_obj_set_align(lv_image_0, LV_ALIGN_CENTER);
    lv_obj_set_x(lv_image_0, -4);
    lv_obj_set_y(lv_image_0, -19);
    
    lv_obj_t * lv_button_0 = lv_button_create(lv_obj_0);
    lv_obj_set_width(lv_button_0, 246);
    lv_obj_set_height(lv_button_0, 43);
    lv_obj_set_x(lv_button_0, 41);
    lv_obj_set_y(lv_button_0, 579);
    lv_obj_set_flag(lv_button_0, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_0, &style_home_button, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
    lv_label_set_text(lv_label_0, "Start brewing today.");
    lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
