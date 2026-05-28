/**
 * @file drink_screen_controller.c
 */

#include "app_ui_internal.h"

static void app_drink_selected_cb(lv_event_t * event)
{
    app_ui_select_drink(lv_event_get_user_data(event));
}

void app_drink_screen_bind(struct app_ui_context * ctx)
{
    if (ctx == NULL || ctx->screens.drink == NULL) {
        return;
    }

    app_prepare_screen(ctx->screens.drink);

    for (uint32_t index = 0U; index < APP_DRINK_COUNT; index++) {
        lv_obj_t * drink_button = lv_obj_get_child_by_type(
            ctx->screens.drink, (int32_t)index, &lv_button_class);

        if (drink_button == NULL) {
            continue;
        }

        lv_obj_add_event_cb(drink_button, app_drink_selected_cb,
                            LV_EVENT_CLICKED, (void *)&app_drinks[index]);
    }
}
