/**
 * @file app_ui.c
 */

#include "app_ui.h"
#include "real_xml_project.h"

#include <stdint.h>

#define APP_UI_SCREEN_WIDTH 720
#define APP_UI_SCREEN_HEIGHT 1280

#define BREW_STEP_PERIOD_MS 100U
#define BREW_STEP_VALUE 2U
#define DRINK_COUNT 4U

#define DRINK_BUTTON_WIDTH 199
#define DRINK_BUTTON_HEIGHT 228

enum app_drink_id {
    APP_DRINK_CARAMEL_FRAPPE,
    APP_DRINK_LATTE,
    APP_DRINK_MOCHA_CREAM,
    APP_DRINK_CARAMEL_MACCHIATO,
};

struct app_drink {
    enum app_drink_id id;
    const char * name;
};

static const struct app_drink app_drinks[DRINK_COUNT] = {
    { APP_DRINK_CARAMEL_FRAPPE, "Caramel Frappe" },
    { APP_DRINK_LATTE, "Latte" },
    { APP_DRINK_MOCHA_CREAM, "Mocha Cream" },
    { APP_DRINK_CARAMEL_MACCHIATO, "Caramel Macchiato" },
};

static lv_obj_t * home_screen;
static lv_obj_t * drink_screen;
static lv_obj_t * order_screen;
static lv_obj_t * final_screen;
static lv_obj_t * order_drink_name_label;
static lv_obj_t * order_progress_bar;
static lv_obj_t * order_status_label;
static lv_obj_t * order_drink_image;

static const struct app_drink * selected_drink = &app_drinks[0];
static lv_timer_t * brew_timer;
static uint8_t brew_progress;

static void app_prepare_screen(lv_obj_t * screen)
{
    if (screen == NULL) {
        return;
    }

    lv_obj_set_size(screen, APP_UI_SCREEN_WIDTH, APP_UI_SCREEN_HEIGHT);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
}

static void app_configure_background(lv_obj_t * screen, const void * src)
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

static const void * app_drink_image(const struct app_drink * drink)
{
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

static const char * app_drink_name(const struct app_drink * drink)
{
    if (drink == NULL) {
        return app_drinks[0].name;
    }

    return drink->name;
}

static void app_stop_brew_timer(void)
{
    if (brew_timer != NULL) {
        lv_timer_delete(brew_timer);
        brew_timer = NULL;
    }
}

static void app_configure_order_screen(void)
{
    lv_obj_t * title_label;

    if (order_screen == NULL) {
        return;
    }

    app_prepare_screen(order_screen);

    title_label = lv_obj_get_child_by_type(order_screen, 0, &lv_label_class);
    order_progress_bar = lv_obj_find_by_name(order_screen, "brew_progress_bar");
    order_status_label = lv_obj_find_by_name(order_screen, "brew_progress_status");
    order_drink_image = lv_obj_find_by_name(order_screen, "selected_drink_image");

    if (title_label != NULL) {
        lv_label_set_text(title_label, "BREWING");
        lv_obj_set_x(title_label, 40);
        lv_obj_set_y(title_label, 350);
        lv_obj_set_width(title_label, 320);
        lv_obj_set_height(title_label, 120);
    }

    order_drink_name_label = lv_label_create(order_screen);
    lv_label_set_text(order_drink_name_label, app_drink_name(selected_drink));
    lv_obj_set_x(order_drink_name_label, 40);
    lv_obj_set_y(order_drink_name_label, 455);
    lv_obj_set_width(order_drink_name_label, 300);
    lv_obj_set_height(order_drink_name_label, 54);
    lv_obj_set_style_text_color(order_drink_name_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_font(order_drink_name_label, font_status, 0);
    lv_obj_set_style_text_align(order_drink_name_label, LV_TEXT_ALIGN_LEFT, 0);

    if (order_progress_bar != NULL) {
        lv_obj_set_x(order_progress_bar, 40);
        lv_obj_set_y(order_progress_bar, 520);
        lv_obj_set_width(order_progress_bar, 300);
        lv_obj_set_height(order_progress_bar, 16);
        lv_bar_set_range(order_progress_bar, 0, 100);
    }

    if (order_status_label != NULL) {
        lv_obj_set_x(order_status_label, 40);
        lv_obj_set_y(order_status_label, 580);
        lv_obj_set_width(order_status_label, 300);
        lv_obj_set_height(order_status_label, 80);
    }

    if (order_drink_image != NULL) {
        lv_obj_set_x(order_drink_image, 360);
        lv_obj_set_y(order_drink_image, 0);
        lv_obj_set_width(order_drink_image, 360);
        lv_obj_set_height(order_drink_image, 1280);
        lv_image_set_inner_align(order_drink_image, LV_IMAGE_ALIGN_CONTAIN);
    }
}

static void app_update_brew_progress(lv_anim_enable_t anim)
{
    if (order_progress_bar != NULL) {
        lv_bar_set_value(order_progress_bar, brew_progress, anim);
    }

    if (order_status_label != NULL) {
        lv_label_set_text(order_status_label, app_brew_status_text(brew_progress));
    }
}

static void app_update_selected_drink_image(void)
{
    if (order_drink_image != NULL) {
        lv_image_set_src(order_drink_image, app_drink_image(selected_drink));
    }
}

static void app_update_selected_drink_name(void)
{
    if (order_drink_name_label != NULL) {
        lv_label_set_text(order_drink_name_label, app_drink_name(selected_drink));
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

        app_update_brew_progress(LV_ANIM_ON);
    }

    if (brew_progress >= 100U) {
        app_stop_brew_timer();
        if (final_screen != NULL) {
            lv_screen_load(final_screen);
        }
    }
}

static void app_start_brewing(void)
{
    app_stop_brew_timer();
    brew_progress = 0U;
    app_update_selected_drink_image();
    app_update_selected_drink_name();
    app_update_brew_progress(LV_ANIM_OFF);

    brew_timer = lv_timer_create(app_brew_timer_cb, BREW_STEP_PERIOD_MS, NULL);
}

static void app_load_drink_screen_cb(lv_event_t * event)
{
    (void)event;

    app_stop_brew_timer();
    lv_screen_load(drink_screen);
}

static void app_drink_selected_cb(lv_event_t * event)
{
    selected_drink = lv_event_get_user_data(event);
    if (selected_drink == NULL) {
        selected_drink = &app_drinks[0];
    }

    app_start_brewing();
    lv_screen_load(order_screen);
}

static void app_load_home_screen_cb(lv_event_t * event)
{
    (void)event;

    app_stop_brew_timer();
    lv_screen_load(home_screen);
}

static void app_bind_home_screen(void)
{
    lv_obj_t * start_button = lv_obj_get_child_by_type(home_screen, 0, &lv_button_class);

    app_prepare_screen(home_screen);
    app_configure_background(home_screen, coffee_maker_hero);

    if (start_button != NULL) {
        lv_obj_set_x(start_button, 49);
        lv_obj_set_y(start_button, 1040);
        lv_obj_add_event_cb(start_button, app_load_drink_screen_cb, LV_EVENT_CLICKED, NULL);
    }
}

static void app_bind_drink_screen(void)
{
    lv_obj_t * title_label;

    app_prepare_screen(drink_screen);

    title_label = lv_obj_get_child_by_type(drink_screen, 0, &lv_label_class);
    if (title_label != NULL) {
        lv_obj_set_x(title_label, 38);
        lv_obj_set_y(title_label, 90);
        lv_obj_set_width(title_label, 644);
        lv_obj_set_height(title_label, 95);
    }

    for (uint32_t index = 0U; index < DRINK_COUNT; index++) {
        lv_obj_t * drink_button = lv_obj_get_child_by_type(drink_screen, (int32_t)index,
                                                           &lv_button_class);

        if (drink_button != NULL) {
            switch (index) {
            case 0U:
                app_configure_drink_button(drink_button, 106, 260);
                break;
            case 1U:
                app_configure_drink_button(drink_button, 415, 260);
                break;
            case 2U:
                app_configure_drink_button(drink_button, 106, 610);
                break;
            default:
                app_configure_drink_button(drink_button, 415, 610);
                break;
            }

            lv_obj_add_event_cb(drink_button, app_drink_selected_cb, LV_EVENT_CLICKED,
                                (void *)&app_drinks[index]);
        }
    }
}

static void app_bind_final_screen(void)
{
    lv_obj_t * final_label = lv_obj_get_child_by_type(final_screen, 0, &lv_label_class);
    lv_obj_t * menu_button = lv_obj_get_child_by_type(final_screen, 0, &lv_button_class);

    app_prepare_screen(final_screen);
    app_configure_background(final_screen, frame_3);

    if (final_label != NULL) {
        lv_obj_set_x(final_label, 115);
        lv_obj_set_y(final_label, 460);
        lv_obj_set_width(final_label, 490);
        lv_obj_set_height(final_label, 210);
    }

    if (menu_button != NULL) {
        lv_obj_set_x(menu_button, 300);
        lv_obj_set_y(menu_button, 760);
        lv_obj_add_event_cb(menu_button, app_load_home_screen_cb, LV_EVENT_CLICKED, NULL);
    }
}

void app_ui_start(void)
{
    real_xml_project_init(NULL);

    home_screen = homescreen_create();
    drink_screen = drinkscreen_create();
    order_screen = orderscreen_create();
    final_screen = finalscreen_create();

    app_configure_order_screen();
    app_update_brew_progress(LV_ANIM_OFF);
    app_bind_home_screen();
    app_bind_drink_screen();
    app_bind_final_screen();

    lv_screen_load(home_screen);
}
