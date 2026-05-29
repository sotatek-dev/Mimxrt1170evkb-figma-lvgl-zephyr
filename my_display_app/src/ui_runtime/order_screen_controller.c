/**
 * @file order_screen_controller.c
 */

#include "app_ui_internal.h"

#define BREW_STEP_PERIOD_MS 100U
#define BREW_STEP_VALUE 2U
#define BREW_STEP_COUNT 3U

static struct app_ui_context * order_ctx;
static lv_obj_t * order_progress_bar;
static lv_obj_t * order_status_label;
static lv_obj_t * order_drink_image;
static lv_timer_t * brew_timer;
static uint8_t brew_progress;

struct app_brew_step {
    const char * name;
    int32_t percentage;
};

static uint8_t app_order_get_brew_steps(struct app_brew_step * steps,
                                        uint8_t max_steps)
{
    uint8_t count = 0U;

    if (order_ctx == NULL || steps == NULL || max_steps == 0U) {
        return 0U;
    }

    if (order_ctx->toppings.coffee > 0 && count < max_steps) {
        steps[count++] = (struct app_brew_step) {
            .name = "Coffee",
            .percentage = order_ctx->toppings.coffee,
        };
    }

    if (order_ctx->toppings.sugar > 0 && count < max_steps) {
        steps[count++] = (struct app_brew_step) {
            .name = "Milk",
            .percentage = order_ctx->toppings.sugar,
        };
    }

    if (order_ctx->toppings.ice > 0 && count < max_steps) {
        steps[count++] = (struct app_brew_step) {
            .name = "Ice",
            .percentage = order_ctx->toppings.ice,
        };
    }

    return count;
}

static void app_order_update_status_label(void)
{
    struct app_brew_step steps[BREW_STEP_COUNT];
    uint8_t step_count;
    uint8_t segment_count;
    uint8_t segment;

    if (order_status_label == NULL) {
        return;
    }

    step_count = app_order_get_brew_steps(steps, BREW_STEP_COUNT);
    segment_count = step_count + 1U;
    segment = (uint8_t)(((uint32_t)brew_progress * segment_count) / 100U);

    if (segment >= segment_count) {
        segment = segment_count - 1U;
    }

    if (segment < step_count) {
        lv_label_set_text_fmt(order_status_label, "Add %d%% %s",
                              (int)steps[segment].percentage,
                              steps[segment].name);
        return;
    }

    lv_label_set_text(order_status_label, "Packing...");
}

static void app_order_update_progress(lv_anim_enable_t anim)
{
    if (order_progress_bar != NULL) {
        lv_bar_set_value(order_progress_bar, brew_progress, anim);
    }

    if (order_status_label != NULL) {
        app_order_update_status_label();
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
    if (ctx == NULL || ctx->screens.order == NULL) {
        return;
    }

    order_ctx = ctx;
    app_prepare_screen(ctx->screens.order);

    order_progress_bar = lv_obj_find_by_name(ctx->screens.order,
                                             "brew_progress_bar");
    order_status_label = lv_obj_find_by_name(ctx->screens.order,
                                             "brew_progress_status");
    order_drink_image = lv_obj_find_by_name(ctx->screens.order,
                                            "selected_drink_image");

    if (order_progress_bar != NULL) {
        lv_bar_set_range(order_progress_bar, 0, 100);
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
