/**
 * @file app_ui_internal.h
 */

#ifndef APP_UI_INTERNAL_H
#define APP_UI_INTERNAL_H

#include <stdint.h>

#include <lvgl.h>
#include <zephyr/logging/log.h>

#include "real_xml_project.h"

#ifndef __has_include
#define __has_include(x) 0
#endif

#if __has_include("screens/toppingscreen_gen.h")
#include "screens/toppingscreen_gen.h"
#define APP_HAS_TOPPING_SCREEN 1
#else
#define APP_HAS_TOPPING_SCREEN 0
#endif

LOG_MODULE_DECLARE(app, CONFIG_LOG_DEFAULT_LEVEL);

#define APP_UI_SCREEN_WIDTH 1280
#define APP_UI_SCREEN_HEIGHT 720

#define APP_DRINK_COUNT 4U
#define APP_TOPPING_DEFAULT_AMOUNT 38

enum app_drink_id {
    APP_DRINK_CARAMEL_FRAPPE,
    APP_DRINK_LATTE,
    APP_DRINK_MOCHA_CREAM,
    APP_DRINK_CARAMEL_MACCHIATO,
};

enum app_drink_size {
    APP_DRINK_SIZE_SMALL,
    APP_DRINK_SIZE_MEDIUM,
    APP_DRINK_SIZE_LARGE,
};

struct app_drink {
    enum app_drink_id id;
    const char * name;
};

struct app_topping_options {
    int32_t coffee;
    int32_t sugar;
    int32_t ice;
    enum app_drink_size size;
};

struct app_ui_screens {
    lv_obj_t * home;
    lv_obj_t * drink;
    lv_obj_t * topping;
    lv_obj_t * order;
    lv_obj_t * final;
};

struct app_ui_context {
    struct app_ui_screens screens;
    const struct app_drink * selected_drink;
    struct app_topping_options toppings;
};

extern const struct app_drink app_drinks[APP_DRINK_COUNT];

void app_ui_context_init(struct app_ui_context * ctx);
void app_prepare_screen(lv_obj_t * screen);
void app_configure_background(lv_obj_t * screen, const void * src);
const void * app_drink_image(const struct app_drink * drink);
const char * app_drink_name(const struct app_drink * drink);
const char * app_drink_size_name(enum app_drink_size size);

void app_home_screen_bind(struct app_ui_context * ctx);
void app_drink_screen_bind(struct app_ui_context * ctx);
void app_topping_screen_bind(struct app_ui_context * ctx);
void app_topping_screen_show(struct app_ui_context * ctx);
void app_order_screen_bind(struct app_ui_context * ctx);
void app_order_screen_start(struct app_ui_context * ctx);
void app_order_screen_stop(void);
void app_final_screen_bind(struct app_ui_context * ctx);

void app_ui_load_home_screen(void);
void app_ui_load_drink_screen(void);
void app_ui_select_drink(const struct app_drink * drink);
void app_ui_start_order_screen(void);
void app_ui_load_final_screen(void);

#endif /* APP_UI_INTERNAL_H */
