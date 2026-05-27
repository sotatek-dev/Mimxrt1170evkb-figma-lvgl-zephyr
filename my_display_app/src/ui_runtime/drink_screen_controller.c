/**
 * @file drink_screen_controller.c
 */

#include "app_ui_internal.h"

#define DRINK_BUTTON_WIDTH 199
#define DRINK_BUTTON_HEIGHT 228

static void app_configure_drink_button(lv_obj_t * button, lv_coord_t x, lv_coord_t y)
{
    if (button == NULL) {
        return;
    }

    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, DRINK_BUTTON_WIDTH, DRINK_BUTTON_HEIGHT);
    lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_all(button, 0, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_TRANSP, 0);
}

static void app_drink_selected_cb(lv_event_t * event)
{
    app_ui_select_drink(lv_event_get_user_data(event));
}

void app_drink_screen_bind(struct app_ui_context * ctx)
{
    lv_obj_t * title_label;

    if (ctx == NULL || ctx->screens.drink == NULL) {
        return;
    }

    app_prepare_screen(ctx->screens.drink);

    title_label = lv_obj_get_child_by_type(ctx->screens.drink, 0, &lv_label_class);
    if (title_label != NULL) {
        lv_obj_set_x(title_label, 318);
        lv_obj_set_y(title_label, 80);
        lv_obj_set_width(title_label, 644);
        lv_obj_set_height(title_label, 95);
    }

    for (uint32_t index = 0U; index < APP_DRINK_COUNT; index++) {
        lv_obj_t * drink_button = lv_obj_get_child_by_type(
            ctx->screens.drink, (int32_t)index, &lv_button_class);

        if (drink_button == NULL) {
            continue;
        }

        switch (index) {
        case 0U:
            app_configure_drink_button(drink_button, 130, 300);
            break;
        case 1U:
            app_configure_drink_button(drink_button, 390, 300);
            break;
        case 2U:
            app_configure_drink_button(drink_button, 650, 300);
            break;
        default:
            app_configure_drink_button(drink_button, 910, 300);
            break;
        }

        lv_obj_add_event_cb(drink_button, app_drink_selected_cb,
                            LV_EVENT_CLICKED, (void *)&app_drinks[index]);
    }
}
