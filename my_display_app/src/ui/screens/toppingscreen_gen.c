/**
 * @file toppingscreen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "toppingscreen_gen.h"
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

lv_obj_t * toppingscreen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_topping_screen;
    static lv_style_t style_topping_image;
    static lv_style_t style_topping_label;
    static lv_style_t style_amount_slider;
    static lv_style_t style_amount_slider_indicator;
    static lv_style_t style_amount_slider_knob;
    static lv_style_t style_size_button;
    static lv_style_t style_size_button_checked;
    static lv_style_t style_size_button_text;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_topping_screen);
        lv_style_set_bg_color(&style_topping_screen, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_topping_screen, (255 * 100 / 100));
        lv_style_set_pad_all(&style_topping_screen, 0);
        lv_style_set_border_width(&style_topping_screen, 0);

        lv_style_init(&style_topping_image);
        lv_style_set_width(&style_topping_image, 640);
        lv_style_set_height(&style_topping_image, 720);
        lv_style_set_radius(&style_topping_image, 0);

        lv_style_init(&style_topping_label);
        lv_style_set_bg_opa(&style_topping_label, (255 * 0 / 100));
        lv_style_set_text_color(&style_topping_label, lv_color_hex(0x000000));
        lv_style_set_text_font(&style_topping_label, font_status);
        lv_style_set_text_align(&style_topping_label, LV_TEXT_ALIGN_LEFT);
        lv_style_set_width(&style_topping_label, 120);
        lv_style_set_height(&style_topping_label, 40);

        lv_style_init(&style_amount_slider);
        lv_style_set_bg_color(&style_amount_slider, lv_color_hex(0xdfd4ce));
        lv_style_set_bg_opa(&style_amount_slider, (255 * 100 / 100));
        lv_style_set_radius(&style_amount_slider, 8);
        lv_style_set_pad_all(&style_amount_slider, 0);
        lv_style_set_border_width(&style_amount_slider, 0);
        lv_style_set_width(&style_amount_slider, 296);
        lv_style_set_height(&style_amount_slider, 13);

        lv_style_init(&style_amount_slider_indicator);
        lv_style_set_bg_color(&style_amount_slider_indicator, lv_color_hex(0x7b3f32));
        lv_style_set_bg_opa(&style_amount_slider_indicator, (255 * 100 / 100));
        lv_style_set_radius(&style_amount_slider_indicator, 8);

        lv_style_init(&style_amount_slider_knob);
        lv_style_set_bg_color(&style_amount_slider_knob, lv_color_hex(0x7b3f32));
        lv_style_set_bg_opa(&style_amount_slider_knob, (255 * 100 / 100));
        lv_style_set_radius(&style_amount_slider_knob, 10);
        lv_style_set_border_width(&style_amount_slider_knob, 0);
        lv_style_set_shadow_width(&style_amount_slider_knob, 0);
        lv_style_set_pad_all(&style_amount_slider_knob, 0);
        lv_style_set_width(&style_amount_slider_knob, 20);
        lv_style_set_height(&style_amount_slider_knob, 20);

        lv_style_init(&style_size_button);
        lv_style_set_bg_color(&style_size_button, lv_color_hex(0xd9d9d9));
        lv_style_set_bg_opa(&style_size_button, (255 * 100 / 100));
        lv_style_set_border_width(&style_size_button, 0);
        lv_style_set_radius(&style_size_button, 46);
        lv_style_set_shadow_width(&style_size_button, 0);
        lv_style_set_pad_all(&style_size_button, 0);
        lv_style_set_width(&style_size_button, 92);
        lv_style_set_height(&style_size_button, 92);

        lv_style_init(&style_size_button_checked);
        lv_style_set_bg_color(&style_size_button_checked, lv_color_hex(0x1d9bf0));
        lv_style_set_bg_opa(&style_size_button_checked, (255 * 100 / 100));
        lv_style_set_border_width(&style_size_button_checked, 0);
        lv_style_set_radius(&style_size_button_checked, 46);
        lv_style_set_shadow_width(&style_size_button_checked, 0);
        lv_style_set_pad_all(&style_size_button_checked, 0);
        lv_style_set_width(&style_size_button_checked, 92);
        lv_style_set_height(&style_size_button_checked, 92);

        lv_style_init(&style_size_button_text);
        lv_style_set_bg_opa(&style_size_button_text, (255 * 0 / 100));
        lv_style_set_text_color(&style_size_button_text, lv_color_hex(0x000000));
        lv_style_set_text_font(&style_size_button_text, font_status);
        lv_style_set_text_align(&style_size_button_text, LV_TEXT_ALIGN_CENTER);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "toppingscreen_#");
    lv_obj_set_width(lv_obj_0, 1280);
    lv_obj_set_height(lv_obj_0, 720);

    lv_obj_add_style(lv_obj_0, &style_topping_screen, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_0, "Coffee");
    lv_obj_set_x(lv_label_0, 32);
    lv_obj_set_y(lv_label_0, 112);
    lv_obj_set_width(lv_label_0, 120);
    lv_obj_set_height(lv_label_0, 40);
    lv_obj_add_style(lv_label_0, &style_topping_label, 0);
    
    lv_obj_t * coffee_slider = lv_slider_create(lv_obj_0);
    lv_obj_set_name(coffee_slider, "coffee_slider");
    lv_obj_set_x(coffee_slider, 168);
    lv_obj_set_y(coffee_slider, 126);
    lv_obj_set_width(coffee_slider, 296);
    lv_obj_set_height(coffee_slider, 13);
    lv_slider_set_value(coffee_slider, 38, false);
    lv_slider_set_orientation(coffee_slider, LV_SLIDER_ORIENTATION_HORIZONTAL);
    lv_obj_set_flag(coffee_slider, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_set_ext_click_area(coffee_slider, 22);
    lv_obj_add_style(coffee_slider, &style_amount_slider, 0);
    lv_obj_add_style(coffee_slider, &style_amount_slider_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(coffee_slider, &style_amount_slider_knob, LV_PART_KNOB);
    
    lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_1, "Sugar");
    lv_obj_set_x(lv_label_1, 32);
    lv_obj_set_y(lv_label_1, 250);
    lv_obj_set_width(lv_label_1, 120);
    lv_obj_set_height(lv_label_1, 40);
    lv_obj_add_style(lv_label_1, &style_topping_label, 0);
    
    lv_obj_t * sugar_slider = lv_slider_create(lv_obj_0);
    lv_obj_set_name(sugar_slider, "sugar_slider");
    lv_obj_set_x(sugar_slider, 168);
    lv_obj_set_y(sugar_slider, 264);
    lv_obj_set_width(sugar_slider, 296);
    lv_obj_set_height(sugar_slider, 13);
    lv_slider_set_value(sugar_slider, 38, false);
    lv_slider_set_orientation(sugar_slider, LV_SLIDER_ORIENTATION_HORIZONTAL);
    lv_obj_set_flag(sugar_slider, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_set_ext_click_area(sugar_slider, 22);
    lv_obj_add_style(sugar_slider, &style_amount_slider, 0);
    lv_obj_add_style(sugar_slider, &style_amount_slider_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(sugar_slider, &style_amount_slider_knob, LV_PART_KNOB);
    
    lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_2, "Ice");
    lv_obj_set_x(lv_label_2, 32);
    lv_obj_set_y(lv_label_2, 392);
    lv_obj_set_width(lv_label_2, 120);
    lv_obj_set_height(lv_label_2, 40);
    lv_obj_add_style(lv_label_2, &style_topping_label, 0);
    
    lv_obj_t * ice_slider = lv_slider_create(lv_obj_0);
    lv_obj_set_name(ice_slider, "ice_slider");
    lv_obj_set_x(ice_slider, 168);
    lv_obj_set_y(ice_slider, 406);
    lv_obj_set_width(ice_slider, 296);
    lv_obj_set_height(ice_slider, 13);
    lv_slider_set_value(ice_slider, 38, false);
    lv_slider_set_orientation(ice_slider, LV_SLIDER_ORIENTATION_HORIZONTAL);
    lv_obj_set_flag(ice_slider, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_set_ext_click_area(ice_slider, 22);
    lv_obj_add_style(ice_slider, &style_amount_slider, 0);
    lv_obj_add_style(ice_slider, &style_amount_slider_indicator, LV_PART_INDICATOR);
    lv_obj_add_style(ice_slider, &style_amount_slider_knob, LV_PART_KNOB);
    
    lv_obj_t * lv_label_3 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_3, "Size");
    lv_obj_set_x(lv_label_3, 32);
    lv_obj_set_y(lv_label_3, 565);
    lv_obj_set_width(lv_label_3, 90);
    lv_obj_set_height(lv_label_3, 40);
    lv_obj_add_style(lv_label_3, &style_topping_label, 0);
    
    lv_obj_t * size_small_button = lv_button_create(lv_obj_0);
    lv_obj_set_name(size_small_button, "size_small_button");
    lv_obj_set_x(size_small_button, 141);
    lv_obj_set_y(size_small_button, 532);
    lv_obj_set_width(size_small_button, 92);
    lv_obj_set_height(size_small_button, 92);
    lv_obj_set_flag(size_small_button, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_set_state(size_small_button, LV_STATE_CHECKED, true);
    lv_obj_add_style(size_small_button, &style_size_button, 0);
    lv_obj_add_style(size_small_button, &style_size_button_checked, LV_STATE_CHECKED);
    lv_obj_t * lv_label_4 = lv_label_create(size_small_button);
    lv_label_set_text(lv_label_4, "S");
    lv_obj_set_align(lv_label_4, LV_ALIGN_CENTER);
    lv_obj_add_style(lv_label_4, &style_size_button_text, 0);
    
    lv_obj_t * size_medium_button = lv_button_create(lv_obj_0);
    lv_obj_set_name(size_medium_button, "size_medium_button");
    lv_obj_set_x(size_medium_button, 280);
    lv_obj_set_y(size_medium_button, 532);
    lv_obj_set_width(size_medium_button, 92);
    lv_obj_set_height(size_medium_button, 92);
    lv_obj_set_flag(size_medium_button, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(size_medium_button, &style_size_button, 0);
    lv_obj_add_style(size_medium_button, &style_size_button_checked, LV_STATE_CHECKED);
    lv_obj_t * lv_label_5 = lv_label_create(size_medium_button);
    lv_label_set_text(lv_label_5, "M");
    lv_obj_set_align(lv_label_5, LV_ALIGN_CENTER);
    lv_obj_add_style(lv_label_5, &style_size_button_text, 0);
    
    lv_obj_t * size_large_button = lv_button_create(lv_obj_0);
    lv_obj_set_name(size_large_button, "size_large_button");
    lv_obj_set_x(size_large_button, 418);
    lv_obj_set_y(size_large_button, 532);
    lv_obj_set_width(size_large_button, 92);
    lv_obj_set_height(size_large_button, 92);
    lv_obj_set_flag(size_large_button, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(size_large_button, &style_size_button, 0);
    lv_obj_add_style(size_large_button, &style_size_button_checked, LV_STATE_CHECKED);
    lv_obj_t * lv_label_6 = lv_label_create(size_large_button);
    lv_label_set_text(lv_label_6, "L");
    lv_obj_set_align(lv_label_6, LV_ALIGN_CENTER);
    lv_obj_add_style(lv_label_6, &style_size_button_text, 0);
    
    lv_obj_t * topping_image = lv_image_create(lv_obj_0);
    lv_obj_set_name(topping_image, "topping_image");
    lv_image_set_src(topping_image, caramel_macchiato);
    lv_obj_set_x(topping_image, 640);
    lv_obj_set_y(topping_image, 0);
    lv_obj_set_width(topping_image, 640);
    lv_obj_set_height(topping_image, 720);
    lv_image_set_inner_align(topping_image, LV_IMAGE_ALIGN_STRETCH);
    lv_obj_add_style(topping_image, &style_topping_image, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

