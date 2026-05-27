/**
 * @file final_screen_controller.c
 */

#include "app_ui_internal.h"

static void app_final_menu_clicked_cb(lv_event_t * event)
{
    (void)event;

    app_ui_load_home_screen();
}

void app_final_screen_bind(struct app_ui_context * ctx)
{
    lv_obj_t * final_label;
    lv_obj_t * menu_button;

    if (ctx == NULL || ctx->screens.final == NULL) {
        return;
    }

    app_prepare_screen(ctx->screens.final);
    app_configure_background(ctx->screens.final, frame_3);

    final_label = lv_obj_get_child_by_type(ctx->screens.final, 0,
                                           &lv_label_class);
    menu_button = lv_obj_get_child_by_type(ctx->screens.final, 0,
                                           &lv_button_class);

    if (final_label != NULL) {
        lv_obj_set_x(final_label, 120);
        lv_obj_set_y(final_label, 300);
        lv_obj_set_width(final_label, 490);
        lv_obj_set_height(final_label, 210);
    }

    if (menu_button != NULL) {
        lv_obj_set_x(menu_button, 300);
        lv_obj_set_y(menu_button, 520);
        lv_obj_add_event_cb(menu_button, app_final_menu_clicked_cb,
                            LV_EVENT_CLICKED, NULL);
    }
}
