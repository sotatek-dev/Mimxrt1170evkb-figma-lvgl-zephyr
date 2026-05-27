/**
 * @file order_screen_controller.c
 */

#include "app_ui_internal.h"

#define BREW_STEP_PERIOD_MS 100U
#define BREW_STEP_VALUE 2U

static struct app_ui_context * order_ctx;
static lv_obj_t * order_drink_name_label;
static lv_obj_t * order_progress_bar;
static lv_obj_t * order_status_label;
static lv_obj_t * order_drink_image;
static lv_timer_t * brew_timer;
static uint8_t brew_progress;

static const char * app_brew_status_text(uint8_t progress)
{
    if (progress < 25U) {
        return "Add coffee...";
    }

    if (progress < 50U) {
        return "Add Milk...";
    }

    if (progress < 75U) {
        return "Some Ice ...";
    }

    return "Packing...";
}

static void app_order_update_progress(lv_anim_enable_t anim)
{
    if (order_progress_bar != NULL) {
        lv_bar_set_value(order_progress_bar, brew_progress, anim);
    }

    if (order_status_label != NULL) {
        lv_label_set_text(order_status_label, app_brew_status_text(brew_progress));
    }
}

static void app_order_update_selected_drink(void)
{
    if (order_ctx == NULL) {
        return;
    }

    if (order_drink_image != NULL) {
        lv_image_set_src(order_drink_image,
                         app_drink_image(order_ctx->selected_drink));
    }

    if (order_drink_name_label != NULL) {
        lv_label_set_text(order_drink_name_label,
                          app_drink_name(order_ctx->selected_drink));
    }
}

static void app_brew_timer_cb(lv_timer_t * timer)
{
    (void)timer;

    if (brew_progress < 100U) {
        brew_progress += BREW_STEP_VALUE;
        if (brew_progress > 100U) {
            brew_progress = 100U;
        }

        app_order_update_progress(LV_ANIM_ON);
    }

    if (brew_progress >= 100U) {
        app_order_screen_stop();
        app_ui_load_final_screen();
    }
}

void app_order_screen_bind(struct app_ui_context * ctx)
{
    lv_obj_t * title_label;

    if (ctx == NULL || ctx->screens.order == NULL) {
        return;
    }

    order_ctx = ctx;
    app_prepare_screen(ctx->screens.order);

    title_label = lv_obj_get_child_by_type(ctx->screens.order, 0,
                                           &lv_label_class);
    order_progress_bar = lv_obj_find_by_name(ctx->screens.order,
                                             "brew_progress_bar");
    order_status_label = lv_obj_find_by_name(ctx->screens.order,
                                             "brew_progress_status");
    order_drink_image = lv_obj_find_by_name(ctx->screens.order,
                                            "selected_drink_image");

    if (title_label != NULL) {
        lv_label_set_text(title_label, "BREWING");
        lv_obj_set_x(title_label, 80);
        lv_obj_set_y(title_label, 210);
        lv_obj_set_width(title_label, 320);
        lv_obj_set_height(title_label, 120);
    }

    order_drink_name_label = lv_label_create(ctx->screens.order);
    lv_label_set_text(order_drink_name_label, app_drink_name(ctx->selected_drink));
    lv_obj_set_x(order_drink_name_label, 80);
    lv_obj_set_y(order_drink_name_label, 315);
    lv_obj_set_width(order_drink_name_label, 300);
    lv_obj_set_height(order_drink_name_label, 54);
    lv_obj_set_style_text_color(order_drink_name_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(order_drink_name_label, font_status, 0);
    lv_obj_set_style_text_align(order_drink_name_label, LV_TEXT_ALIGN_LEFT, 0);

    if (order_progress_bar != NULL) {
        lv_obj_set_x(order_progress_bar, 80);
        lv_obj_set_y(order_progress_bar, 380);
        lv_obj_set_width(order_progress_bar, 300);
        lv_obj_set_height(order_progress_bar, 16);
        lv_bar_set_range(order_progress_bar, 0, 100);
    }

    if (order_status_label != NULL) {
        lv_obj_set_x(order_status_label, 80);
        lv_obj_set_y(order_status_label, 440);
        lv_obj_set_width(order_status_label, 300);
        lv_obj_set_height(order_status_label, 80);
    }

    if (order_drink_image != NULL) {
        lv_obj_set_x(order_drink_image, 760);
        lv_obj_set_y(order_drink_image, 150);
        lv_obj_set_width(order_drink_image, 420);
        lv_obj_set_height(order_drink_image, 420);
        lv_image_set_inner_align(order_drink_image, LV_IMAGE_ALIGN_CONTAIN);
    }

    app_order_update_progress(LV_ANIM_OFF);
}

void app_order_screen_start(struct app_ui_context * ctx)
{
    order_ctx = ctx;
    app_order_screen_stop();

    brew_progress = 0U;
    app_order_update_selected_drink();
    app_order_update_progress(LV_ANIM_OFF);

    brew_timer = lv_timer_create(app_brew_timer_cb, BREW_STEP_PERIOD_MS, NULL);
}

void app_order_screen_stop(void)
{
    if (brew_timer != NULL) {
        lv_timer_delete(brew_timer);
        brew_timer = NULL;
    }
}
