/**
 * @file topping_screen_controller.c
 */

#include "app_ui_internal.h"

#define TOPPING_BREW_BUTTON_WIDTH 296
#define TOPPING_BREW_BUTTON_HEIGHT 48
#define TOPPING_SLIDER_TOUCH_PAD 56
#define TOPPING_PERCENT_LABEL_WIDTH 72
#define TOPPING_PERCENT_LABEL_HEIGHT 32
#define TOPPING_PERCENT_LABEL_X_GAP 24
#define TOPPING_PERCENT_LABEL_Y_OFFSET -10

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
static lv_obj_t * coffee_percent_label;
static lv_obj_t * sugar_percent_label;
static lv_obj_t * ice_percent_label;

static const enum app_drink_size app_size_small = APP_DRINK_SIZE_SMALL;
static const enum app_drink_size app_size_medium = APP_DRINK_SIZE_MEDIUM;
static const enum app_drink_size app_size_large = APP_DRINK_SIZE_LARGE;

static void app_topping_update_image(void)
{
    if (topping_ctx == NULL || topping_image == NULL) {
        return;
    }

    lv_image_set_src(topping_image, app_drink_image(topping_ctx->selected_drink));
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

static void app_topping_update_percent_labels(void)
{
    if (topping_ctx == NULL) {
        return;
    }

    if (coffee_percent_label != NULL) {
        lv_label_set_text_fmt(coffee_percent_label, "%d%%",
                              (int)topping_ctx->toppings.coffee);
    }

    if (sugar_percent_label != NULL) {
        lv_label_set_text_fmt(sugar_percent_label, "%d%%",
                              (int)topping_ctx->toppings.sugar);
    }

    if (ice_percent_label != NULL) {
        lv_label_set_text_fmt(ice_percent_label, "%d%%",
                              (int)topping_ctx->toppings.ice);
    }
}

static void app_topping_slider_changed_cb(lv_event_t * event)
{
    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t * slider = lv_event_get_target(event);

    if (code == LV_EVENT_VALUE_CHANGED) {
        app_topping_read_controls();
        app_topping_update_percent_labels();
        return;
    }

    if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST ||
        code == LV_EVENT_LEAVE || code == LV_EVENT_DEFOCUSED) {
        app_topping_read_controls();
        app_topping_update_percent_labels();
        lv_obj_remove_state(slider, LV_STATE_PRESSED | LV_STATE_FOCUSED |
                            LV_STATE_EDITED | LV_STATE_FOCUS_KEY);
    }
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
    app_topping_update_percent_labels();
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

static lv_obj_t * app_topping_create_percent_label(lv_obj_t * slider)
{
    lv_obj_t * label;

    if (topping_ctx == NULL || slider == NULL) {
        return NULL;
    }

    label = lv_label_create(topping_ctx->screens.topping);
    lv_obj_set_width(label, TOPPING_PERCENT_LABEL_WIDTH);
    lv_obj_set_height(label, TOPPING_PERCENT_LABEL_HEIGHT);
    lv_obj_set_x(label, lv_obj_get_x(slider) + lv_obj_get_width(slider) +
                 TOPPING_PERCENT_LABEL_X_GAP);
    lv_obj_set_y(label, lv_obj_get_y(slider) + TOPPING_PERCENT_LABEL_Y_OFFSET);
    lv_obj_set_style_text_color(label, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(label, font_status, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);

    return label;
}

static void app_topping_configure_slider(lv_obj_t * slider)
{
    if (slider == NULL) {
        return;
    }

    lv_obj_set_ext_click_area(slider, TOPPING_SLIDER_TOUCH_PAD);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_PRESS_LOCK);
    lv_obj_remove_flag(slider, LV_OBJ_FLAG_CLICK_FOCUSABLE |
                       LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_remove_state(slider, LV_STATE_PRESSED | LV_STATE_FOCUSED |
                        LV_STATE_EDITED | LV_STATE_FOCUS_KEY);
    lv_obj_add_event_cb(slider, app_topping_slider_changed_cb, LV_EVENT_ALL,
                        NULL);
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

    coffee_percent_label = app_topping_create_percent_label(coffee_slider);
    sugar_percent_label = app_topping_create_percent_label(sugar_slider);
    ice_percent_label = app_topping_create_percent_label(ice_slider);

    app_topping_configure_slider(coffee_slider);
    app_topping_configure_slider(sugar_slider);
    app_topping_configure_slider(ice_slider);

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
