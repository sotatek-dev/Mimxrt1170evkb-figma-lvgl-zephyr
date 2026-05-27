/**
 * @file drinkscreen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "drinkscreen_gen.h"
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

lv_obj_t * drinkscreen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_drink_screen;
    static lv_style_t style_drink_title;
    static lv_style_t style_drink_name;
    static lv_style_t style_drink_item;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&style_drink_screen);
        lv_style_set_bg_color(&style_drink_screen, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_drink_screen, (255 * 100 / 100));
        lv_style_set_pad_all(&style_drink_screen, 0);
        lv_style_set_border_width(&style_drink_screen, 0);

        lv_style_init(&style_drink_title);
        lv_style_set_bg_color(&style_drink_title, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&style_drink_title, (255 * 0 / 100));
        lv_style_set_text_color(&style_drink_title, lv_color_hex(0x000000));
        lv_style_set_text_align(&style_drink_title, LV_TEXT_ALIGN_CENTER);
        lv_style_set_width(&style_drink_title, 644);
        lv_style_set_height(&style_drink_title, 95);

        lv_style_init(&style_drink_name);
        lv_style_set_text_color(&style_drink_name, lv_color_hex(0x000000));
        lv_style_set_text_align(&style_drink_name, LV_TEXT_ALIGN_CENTER);
        lv_style_set_width(&style_drink_name, 112);
        lv_style_set_height(&style_drink_name, 25);

        lv_style_init(&style_drink_item);
        lv_style_set_bg_opa(&style_drink_item, (255 * 0 / 100));
        lv_style_set_border_width(&style_drink_item, 0);
        lv_style_set_shadow_width(&style_drink_item, 0);
        lv_style_set_pad_all(&style_drink_item, 0);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "drinkscreen_#");
    lv_obj_set_width(lv_obj_0, 1280);
    lv_obj_set_height(lv_obj_0, 720);

    lv_obj_add_style(lv_obj_0, &style_drink_screen, 0);
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_label_set_text(lv_label_0, "Choose Your Drink!");
    lv_obj_set_x(lv_label_0, 318);
    lv_obj_set_y(lv_label_0, 78);
    lv_obj_set_width(lv_label_0, 644);
    lv_obj_set_height(lv_label_0, 95);
    lv_obj_add_style(lv_label_0, &style_drink_title, 0);
    
    lv_obj_t * lv_button_0 = lv_button_create(lv_obj_0);
    lv_obj_set_x(lv_button_0, 282);
    lv_obj_set_y(lv_button_0, 170);
    lv_obj_set_width(lv_button_0, 199);
    lv_obj_set_height(lv_button_0, 228);
    lv_obj_set_flag(lv_button_0, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_0, &style_drink_item, 0);
    lv_obj_t * lv_image_0 = lv_image_create(lv_button_0);
    lv_image_set_src(lv_image_0, caramel_frappe);
    lv_obj_set_x(lv_image_0, 0);
    lv_obj_set_y(lv_image_0, 0);
    
    lv_obj_t * lv_label_1 = lv_label_create(lv_button_0);
    lv_label_set_text(lv_label_1, "Caramel Frappe");
    lv_obj_set_x(lv_label_1, 0);
    lv_obj_set_y(lv_label_1, 203);
    lv_obj_set_width(lv_label_1, 199);
    lv_obj_set_height(lv_label_1, 25);
    lv_obj_add_style(lv_label_1, &style_drink_name, 0);
    
    lv_obj_t * lv_button_1 = lv_button_create(lv_obj_0);
    lv_obj_set_x(lv_button_1, 786);
    lv_obj_set_y(lv_button_1, 170);
    lv_obj_set_width(lv_button_1, 199);
    lv_obj_set_height(lv_button_1, 228);
    lv_obj_set_flag(lv_button_1, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_1, &style_drink_item, 0);
    lv_obj_t * lv_image_1 = lv_image_create(lv_button_1);
    lv_image_set_src(lv_image_1, latte);
    lv_obj_set_x(lv_image_1, 0);
    lv_obj_set_y(lv_image_1, 0);
    
    lv_obj_t * lv_label_2 = lv_label_create(lv_button_1);
    lv_label_set_text(lv_label_2, "Latte");
    lv_obj_set_x(lv_label_2, 0);
    lv_obj_set_y(lv_label_2, 202);
    lv_obj_set_width(lv_label_2, 199);
    lv_obj_set_height(lv_label_2, 25);
    lv_obj_add_style(lv_label_2, &style_drink_name, 0);
    
    lv_obj_t * lv_button_2 = lv_button_create(lv_obj_0);
    lv_obj_set_x(lv_button_2, 282);
    lv_obj_set_y(lv_button_2, 444);
    lv_obj_set_width(lv_button_2, 199);
    lv_obj_set_height(lv_button_2, 225);
    lv_obj_set_flag(lv_button_2, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_2, &style_drink_item, 0);
    lv_obj_t * lv_image_2 = lv_image_create(lv_button_2);
    lv_image_set_src(lv_image_2, mocha_cream);
    lv_obj_set_x(lv_image_2, 0);
    lv_obj_set_y(lv_image_2, 0);
    
    lv_obj_t * lv_label_3 = lv_label_create(lv_button_2);
    lv_label_set_text(lv_label_3, "Mocha Cream");
    lv_obj_set_x(lv_label_3, 2);
    lv_obj_set_y(lv_label_3, 200);
    lv_obj_set_width(lv_label_3, 199);
    lv_obj_set_height(lv_label_3, 25);
    lv_obj_add_style(lv_label_3, &style_drink_name, 0);
    
    lv_obj_t * lv_button_3 = lv_button_create(lv_obj_0);
    lv_obj_set_x(lv_button_3, 786);
    lv_obj_set_y(lv_button_3, 444);
    lv_obj_set_width(lv_button_3, 199);
    lv_obj_set_height(lv_button_3, 227);
    lv_obj_set_flag(lv_button_3, LV_OBJ_FLAG_CLICKABLE, true);
    lv_obj_add_style(lv_button_3, &style_drink_item, 0);
    lv_obj_t * lv_image_3 = lv_image_create(lv_button_3);
    lv_image_set_src(lv_image_3, caramel_macchiato);
    lv_obj_set_x(lv_image_3, 0);
    lv_obj_set_y(lv_image_3, 0);
    
    lv_obj_t * lv_label_4 = lv_label_create(lv_button_3);
    lv_label_set_text(lv_label_4, "Caramel Macchiato");
    lv_obj_set_x(lv_label_4, 1);
    lv_obj_set_y(lv_label_4, 202);
    lv_obj_set_width(lv_label_4, 199);
    lv_obj_set_height(lv_label_4, 25);
    lv_obj_add_style(lv_label_4, &style_drink_name, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
