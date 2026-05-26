/**
 * @file finalscreen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "finalscreen_gen.h"
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

lv_obj_t * finalscreen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_final_screen;
    static lv_style_t style_final_text;
    static lv_style_t style_final_button;
    static lv_style_t style_final_arrow;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_final_screen);
        lv_style_set_bg_color(&style_final_screen, lv_color_hex(0x281414));
        lv_style_set_bg_opa(&style_final_screen, (255 * 100 / 100));
        lv_style_set_pad_all(&style_final_screen, 0);
        lv_style_set_border_width(&style_final_screen, 0);

        lv_style_init(&style_final_text);
        lv_style_set_bg_color(&style_final_text, lv_color_hex(0xd9d9d9));
        lv_style_set_bg_opa(&style_final_text, (255 * 100 / 100));
        lv_style_set_text_color(&style_final_text, lv_color_hex(0x000000));
        lv_style_set_text_font(&style_final_text, font_brewing);
        lv_style_set_text_align(&style_final_text, LV_TEXT_ALIGN_CENTER);
        lv_style_set_width(&style_final_text, 454);
        lv_style_set_height(&style_final_text, 154);

        lv_style_init(&style_final_button);
        lv_style_set_bg_color(&style_final_button, lv_color_hex(0x1ee6e2));
        lv_style_set_bg_opa(&style_final_button, (255 * 100 / 100));
        lv_style_set_border_color(&style_final_button, lv_color_hex(0x8bc9ff));
        lv_style_set_border_opa(&style_final_button, (255 * 100 / 100));
        lv_style_set_border_width(&style_final_button, 3);
        lv_style_set_radius(&style_final_button, 58);
        lv_style_set_width(&style_final_button, 119);
        lv_style_set_height(&style_final_button, 116);

        lv_style_init(&style_final_arrow);
        lv_style_set_bg_opa(&style_final_arrow, (255 * 0 / 100));
        lv_style_set_text_color(&style_final_arrow, lv_color_hex(0x0023c7));
        lv_style_set_text_align(&style_final_arrow, LV_TEXT_ALIGN_CENTER);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "finalscreen_#");
    lv_obj_set_width(lv_obj_0, 720);
    lv_obj_set_height(lv_obj_0, 1280);

    lv_obj_add_style(lv_obj_0, &style_final_screen, 0);
    lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
    lv_image_set_src(lv_image_0, frame_3);
    lv_obj_set_align(lv_image_0, LV_ALIGN_CENTER);
    lv_obj_set_width(lv_image_0, 720);
    lv_obj_set_height(lv_image_0, 1280);
    lv_image_set_inner_align(lv_image_0, LV_IMAGE_ALIGN_CONTAIN);
    
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_0, "Thanks for using\nour coffee");
    lv_obj_set_x(lv_label_0, 115);
    lv_obj_set_y(lv_label_0, 460);
    lv_obj_set_width(lv_label_0, 490);
    lv_obj_set_height(lv_label_0, 210);
    lv_obj_add_style(lv_label_0, &style_final_text, 0);
    
    lv_obj_t * lv_button_0 = lv_button_create(lv_obj_0);
    lv_obj_set_x(lv_button_0, 300);
    lv_obj_set_y(lv_button_0, 760);
    lv_obj_set_width(lv_button_0, 119);
    lv_obj_set_height(lv_button_0, 116);
    lv_obj_set_flag(lv_button_0, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_0, &style_final_button, 0);
    lv_obj_t * lv_label_1 = lv_label_create(lv_button_0);
    lv_label_set_text(lv_label_1, "Menu");
    lv_obj_set_align(lv_label_1, LV_ALIGN_CENTER);
    lv_obj_add_style(lv_label_1, &style_final_arrow, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
