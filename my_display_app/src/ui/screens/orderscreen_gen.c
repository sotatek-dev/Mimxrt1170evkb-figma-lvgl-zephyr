/**
 * @file orderscreen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "orderscreen_gen.h"
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

lv_obj_t * orderscreen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_order_screen;
    static lv_style_t style_brewing_text;
    static lv_style_t style_progress_bar;
    static lv_style_t style_progress_indicator;
    static lv_style_t style_progress_status;
    static lv_style_t style_selected_drink_image;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_order_screen);
        lv_style_set_bg_color(&style_order_screen, lv_color_hex(0x281414));
        lv_style_set_bg_opa(&style_order_screen, (255 * 100 / 100));
        lv_style_set_pad_all(&style_order_screen, 0);
        lv_style_set_border_width(&style_order_screen, 0);

        lv_style_init(&style_brewing_text);
        lv_style_set_text_color(&style_brewing_text, lv_color_hex(0xc9c0b9));
        lv_style_set_text_font(&style_brewing_text, font_brewing);
        lv_style_set_text_align(&style_brewing_text, LV_TEXT_ALIGN_LEFT);
        lv_style_set_width(&style_brewing_text, 344);
        lv_style_set_height(&style_brewing_text, 112);

        lv_style_init(&style_progress_bar);
        lv_style_set_bg_color(&style_progress_bar, lv_color_hex(0xe0d6d0));
        lv_style_set_bg_opa(&style_progress_bar, (255 * 100 / 100));
        lv_style_set_radius(&style_progress_bar, 8);
        lv_style_set_pad_all(&style_progress_bar, 0);
        lv_style_set_border_width(&style_progress_bar, 0);
        lv_style_set_width(&style_progress_bar, 300);
        lv_style_set_height(&style_progress_bar, 16);

        lv_style_init(&style_progress_indicator);
        lv_style_set_bg_color(&style_progress_indicator, lv_color_hex(0x8b4a3b));
        lv_style_set_bg_opa(&style_progress_indicator, (255 * 100 / 100));
        lv_style_set_radius(&style_progress_indicator, 8);

        lv_style_init(&style_progress_status);
        lv_style_set_bg_opa(&style_progress_status, (255 * 0 / 100));
        lv_style_set_text_color(&style_progress_status, lv_color_hex(0xffffff));
        lv_style_set_text_font(&style_progress_status, font_status);
        lv_style_set_text_align(&style_progress_status, LV_TEXT_ALIGN_LEFT);
        lv_style_set_width(&style_progress_status, 241);
        lv_style_set_height(&style_progress_status, 70);

        lv_style_init(&style_selected_drink_image);
        lv_style_set_radius(&style_selected_drink_image, 0);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "orderscreen_#");
    lv_obj_set_width(lv_obj_0, 1280);
    lv_obj_set_height(lv_obj_0, 720);

    lv_obj_add_style(lv_obj_0, &style_order_screen, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_0, "Brewing");
    lv_obj_set_x(lv_label_0, 217);
    lv_obj_set_y(lv_label_0, 128);
    lv_obj_set_width(lv_label_0, 344);
    lv_obj_set_height(lv_label_0, 112);
    lv_obj_add_style(lv_label_0, &style_brewing_text, 0);
    
    lv_obj_t * brew_progress_bar = lv_bar_create(lv_obj_0);
    lv_obj_set_name(brew_progress_bar, "brew_progress_bar");
    lv_obj_set_x(brew_progress_bar, 171);
    lv_obj_set_y(brew_progress_bar, 273);
    lv_obj_set_width(brew_progress_bar, 285);
    lv_obj_set_height(brew_progress_bar, 16);
    lv_bar_set_value(brew_progress_bar, 35, false);
    lv_obj_add_style(brew_progress_bar, &style_progress_bar, 0);
    lv_obj_add_style(brew_progress_bar, &style_progress_indicator, LV_PART_INDICATOR);
    
    lv_obj_t * brew_progress_status = lv_label_create(lv_obj_0);
    lv_obj_set_name(brew_progress_status, "brew_progress_status");
    lv_label_set_text(brew_progress_status, "Add Coffee...");
    lv_obj_set_x(brew_progress_status, 223);
    lv_obj_set_y(brew_progress_status, 436);
    lv_obj_set_width(brew_progress_status, 241);
    lv_obj_set_height(brew_progress_status, 70);
    lv_obj_add_style(brew_progress_status, &style_progress_status, 0);
    
    lv_obj_t * selected_drink_image = lv_image_create(lv_obj_0);
    lv_obj_set_name(selected_drink_image, "selected_drink_image");
    lv_image_set_src(selected_drink_image, caramel_frappe);
    lv_obj_set_x(selected_drink_image, 640);
    lv_obj_set_y(selected_drink_image, 0);
    lv_obj_set_width(selected_drink_image, 640);
    lv_obj_set_height(selected_drink_image, 720);
    lv_obj_add_style(selected_drink_image, &style_selected_drink_image, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
