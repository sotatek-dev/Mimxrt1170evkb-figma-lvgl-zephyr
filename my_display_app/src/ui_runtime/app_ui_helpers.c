/**
 * @file app_ui_helpers.c
 */

#include "app_ui_internal.h"

#include <string.h>

const struct app_drink app_drinks[APP_DRINK_COUNT] = {
    { APP_DRINK_CARAMEL_FRAPPE, "Caramel Frappe" },
    { APP_DRINK_LATTE, "Latte" },
    { APP_DRINK_MOCHA_CREAM, "Mocha Cream" },
    { APP_DRINK_CARAMEL_MACCHIATO, "Caramel Macchiato" },
};

void app_ui_context_init(struct app_ui_context * ctx)
{
    if (ctx == NULL) {
        return;
    }

    memset(ctx, 0, sizeof(*ctx));
    ctx->selected_drink = &app_drinks[0];
    ctx->toppings.coffee = APP_TOPPING_DEFAULT_AMOUNT;
    ctx->toppings.sugar = APP_TOPPING_DEFAULT_AMOUNT;
    ctx->toppings.ice = APP_TOPPING_DEFAULT_AMOUNT;
    ctx->toppings.size = APP_DRINK_SIZE_SMALL;
}

void app_prepare_screen(lv_obj_t * screen)
{
    if (screen == NULL) {
        return;
    }

    lv_obj_set_size(screen, APP_UI_SCREEN_WIDTH, APP_UI_SCREEN_HEIGHT);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
}

void app_configure_background(lv_obj_t * screen, const void * src)
{
    lv_obj_t * background;

    if (screen == NULL) {
        return;
    }

    background = lv_obj_get_child_by_type(screen, 0, &lv_image_class);
    if (background == NULL) {
        return;
    }

    lv_image_set_src(background, src);
    lv_obj_set_size(background, APP_UI_SCREEN_WIDTH, APP_UI_SCREEN_HEIGHT);
    lv_obj_set_align(background, LV_ALIGN_CENTER);
    lv_obj_set_pos(background, 0, 0);
    lv_image_set_inner_align(background, LV_IMAGE_ALIGN_CONTAIN);
    lv_obj_clear_flag(background, LV_OBJ_FLAG_CLICKABLE);
}

const void * app_drink_image(const struct app_drink * drink)
{
    if (drink == NULL) {
        drink = &app_drinks[0];
    }

    switch (drink->id) {
    case APP_DRINK_CARAMEL_FRAPPE:
        return caramel_frappe;
    case APP_DRINK_LATTE:
        return latte;
    case APP_DRINK_MOCHA_CREAM:
        return mocha_cream;
    case APP_DRINK_CARAMEL_MACCHIATO:
        return caramel_macchiato;
    default:
        return caramel_frappe;
    }
}

const char * app_drink_name(const struct app_drink * drink)
{
    if (drink == NULL) {
        return app_drinks[0].name;
    }

    return drink->name;
}

const char * app_drink_size_name(enum app_drink_size size)
{
    switch (size) {
    case APP_DRINK_SIZE_SMALL:
        return "S";
    case APP_DRINK_SIZE_MEDIUM:
        return "M";
    case APP_DRINK_SIZE_LARGE:
        return "L";
    default:
        return "S";
    }
}
