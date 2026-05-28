/**
 * @file home_screen_controller.c
 */

#include "app_ui_internal.h"

static void app_home_start_clicked_cb(lv_event_t * event)
{
    (void)event;

    app_ui_load_drink_screen();
}

void app_home_screen_bind(struct app_ui_context * ctx)
{
    lv_obj_t * start_button;

    if (ctx == NULL || ctx->screens.home == NULL) {
        return;
    }

    app_prepare_screen(ctx->screens.home);

    start_button = lv_obj_get_child_by_type(ctx->screens.home, 0, &lv_button_class);
    if (start_button == NULL) {
        return;
    }

    lv_obj_add_event_cb(start_button, app_home_start_clicked_cb,
                        LV_EVENT_CLICKED, NULL);
}
