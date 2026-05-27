/**
 * @file topping_screen_controller.c
 */

#include "app_ui_internal.h"

#define TOPPING_BREW_BUTTON_WIDTH 296
#define TOPPING_BREW_BUTTON_HEIGHT 48

#if APP_HAS_TOPPING_SCREEN
static struct app_ui_context * topping_ctx;
static lv_obj_t * topping_image;
static lv_obj_t * coffee_slider;
static lv_obj_t * sugar_slider;
static lv_obj_t * ice_slider;
static lv_obj_t * size_small_button;
static lv_obj_t * size_medium_button;
static lv_obj_t * size_large_button;
static lv_obj_t * topping_brew_button;

static const enum app_drink_size app_size_small = APP_DRINK_SIZE_SMALL;
static const enum app_drink_size app_size_medium = APP_DRINK_SIZE_MEDIUM;
static const enum app_drink_size app_size_large = APP_DRINK_SIZE_LARGE;

static void app_topping_update_image(void)
{
    if (topping_ctx == NULL || topping_image == NULL) {
        return;
    }

    lv_image_set_src(topping_image, app_drink_image(topping_ctx->selected_drink));
    lv_obj_set_x(topping_image, 640);
    lv_obj_set_y(topping_image, 0);
    lv_obj_set_width(topping_image, 640);
    lv_obj_set_height(topping_image, 720);
    lv_image_set_inner_align(topping_image, LV_IMAGE_ALIGN_CONTAIN);
}

static void app_topping_set_size(enum app_drink_size size)
{
    if (topping_ctx == NULL) {
        return;
    }

    topping_ctx->toppings.size = size;

    if (size_small_button != NULL) {
        lv_obj_set_state(size_small_button, LV_STATE_CHECKED,
                         size == APP_DRINK_SIZE_SMALL);
    }

    if (size_medium_button != NULL) {
        lv_obj_set_state(size_medium_button, LV_STATE_CHECKED,
                         size == APP_DRINK_SIZE_MEDIUM);
    }

    if (size_large_button != NULL) {
        lv_obj_set_state(size_large_button, LV_STATE_CHECKED,
                         size == APP_DRINK_SIZE_LARGE);
    }
}

static void app_topping_read_controls(void)
{
    if (topping_ctx == NULL) {
        return;
    }

    if (coffee_slider != NULL) {
        topping_ctx->toppings.coffee = lv_slider_get_value(coffee_slider);
    }

    if (sugar_slider != NULL) {
        topping_ctx->toppings.sugar = lv_slider_get_value(sugar_slider);
    }

    if (ice_slider != NULL) {
        topping_ctx->toppings.ice = lv_slider_get_value(ice_slider);
    }
}

static void app_topping_slider_changed_cb(lv_event_t * event)
{
    (void)event;

    app_topping_read_controls();
}

static void app_topping_size_clicked_cb(lv_event_t * event)
{
    const enum app_drink_size * size = lv_event_get_user_data(event);

    if (size != NULL) {
        app_topping_set_size(*size);
    }
}

static void app_topping_reset_controls(void)
{
    if (topping_ctx == NULL) {
        return;
    }

    topping_ctx->toppings.coffee = APP_TOPPING_DEFAULT_AMOUNT;
    topping_ctx->toppings.sugar = APP_TOPPING_DEFAULT_AMOUNT;
    topping_ctx->toppings.ice = APP_TOPPING_DEFAULT_AMOUNT;

    if (coffee_slider != NULL) {
        lv_slider_set_value(coffee_slider, topping_ctx->toppings.coffee,
                            LV_ANIM_OFF);
    }

    if (sugar_slider != NULL) {
        lv_slider_set_value(sugar_slider, topping_ctx->toppings.sugar,
                            LV_ANIM_OFF);
    }

    if (ice_slider != NULL) {
        lv_slider_set_value(ice_slider, topping_ctx->toppings.ice, LV_ANIM_OFF);
    }

    app_topping_set_size(APP_DRINK_SIZE_SMALL);
    app_topping_update_image();
}

static lv_obj_t * app_topping_create_brew_button(void)
{
    lv_obj_t * button = lv_button_create(topping_ctx->screens.topping);
    lv_obj_t * label;

    lv_obj_set_name(button, "brew_button");
    lv_obj_set_x(button, 168);
    lv_obj_set_y(button, 650);
    lv_obj_set_width(button, TOPPING_BREW_BUTTON_WIDTH);
    lv_obj_set_height(button, TOPPING_BREW_BUTTON_HEIGHT);
    lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(button, lv_color_hex(0x2f1a14), 0);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(button, 8, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_set_style_shadow_width(button, 0, 0);

    label = lv_label_create(button);
    lv_label_set_text(label, "Start Brewing");
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(label, font_status, 0);

    return button;
}

static void app_topping_brew_clicked_cb(lv_event_t * event)
{
    (void)event;

    if (topping_ctx == NULL) {
        return;
    }

    app_topping_read_controls();
    LOG_INF("Brewing %s: coffee=%d sugar=%d ice=%d size=%s",
            app_drink_name(topping_ctx->selected_drink),
            (int)topping_ctx->toppings.coffee,
            (int)topping_ctx->toppings.sugar,
            (int)topping_ctx->toppings.ice,
            app_drink_size_name(topping_ctx->toppings.size));

    app_ui_start_order_screen();
}
#endif

void app_topping_screen_bind(struct app_ui_context * ctx)
{
#if APP_HAS_TOPPING_SCREEN
    if (ctx == NULL || ctx->screens.topping == NULL) {
        LOG_WRN("toppingscreen_create returned NULL");
        return;
    }

    topping_ctx = ctx;
    app_prepare_screen(ctx->screens.topping);

    topping_image = lv_obj_find_by_name(ctx->screens.topping, "topping_image");
    coffee_slider = lv_obj_find_by_name(ctx->screens.topping, "coffee_slider");
    sugar_slider = lv_obj_find_by_name(ctx->screens.topping, "sugar_slider");
    ice_slider = lv_obj_find_by_name(ctx->screens.topping, "ice_slider");
    size_small_button = lv_obj_find_by_name(ctx->screens.topping,
                                            "size_small_button");
    size_medium_button = lv_obj_find_by_name(ctx->screens.topping,
                                             "size_medium_button");
    size_large_button = lv_obj_find_by_name(ctx->screens.topping,
                                            "size_large_button");
    topping_brew_button = lv_obj_find_by_name(ctx->screens.topping,
                                              "brew_button");

    if (coffee_slider != NULL) {
        lv_obj_add_event_cb(coffee_slider, app_topping_slider_changed_cb,
                            LV_EVENT_VALUE_CHANGED, NULL);
    }

    if (sugar_slider != NULL) {
        lv_obj_add_event_cb(sugar_slider, app_topping_slider_changed_cb,
                            LV_EVENT_VALUE_CHANGED, NULL);
    }

    if (ice_slider != NULL) {
        lv_obj_add_event_cb(ice_slider, app_topping_slider_changed_cb,
                            LV_EVENT_VALUE_CHANGED, NULL);
    }

    if (size_small_button != NULL) {
        lv_obj_add_event_cb(size_small_button, app_topping_size_clicked_cb,
                            LV_EVENT_CLICKED, (void *)&app_size_small);
    }

    if (size_medium_button != NULL) {
        lv_obj_add_event_cb(size_medium_button, app_topping_size_clicked_cb,
                            LV_EVENT_CLICKED, (void *)&app_size_medium);
    }

    if (size_large_button != NULL) {
        lv_obj_add_event_cb(size_large_button, app_topping_size_clicked_cb,
                            LV_EVENT_CLICKED, (void *)&app_size_large);
    }

    if (topping_brew_button == NULL) {
        LOG_WRN("toppingscreen object 'brew_button' was not found; creating runtime button");
        topping_brew_button = app_topping_create_brew_button();
    }

    lv_obj_add_event_cb(topping_brew_button, app_topping_brew_clicked_cb,
                        LV_EVENT_CLICKED, NULL);
    app_topping_reset_controls();
#else
    ARG_UNUSED(ctx);
    LOG_WRN("toppingscreen_gen.h not found; drink selection will load brewing directly");
#endif
}

void app_topping_screen_show(struct app_ui_context * ctx)
{
#if APP_HAS_TOPPING_SCREEN
    topping_ctx = ctx;
    app_topping_reset_controls();

    if (ctx != NULL && ctx->screens.topping != NULL) {
        lv_screen_load(ctx->screens.topping);
    }
#else
    ARG_UNUSED(ctx);
#endif
}
