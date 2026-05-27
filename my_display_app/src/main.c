/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#ifdef APP_HAS_FRAME_UI
#include "ui_frame_1.h"
#endif

#ifdef APP_HAS_SQUARELINE_UI
#include "ui.h"
#endif

#ifdef APP_HAS_LV_EDITOR_UI
#include "testtool.h"
#endif

#ifdef APP_HAS_REAL_XML_UI
#include "app_ui.h"
#endif

#ifdef APP_HAS_GENERATED_UI
#include "gui_guider.h"
#include "events_init.h"
#if __has_include("custom.h")
#include "custom.h"
#define APP_HAS_CUSTOM_UI 1
#endif
#endif

LOG_MODULE_REGISTER(app, CONFIG_LOG_DEFAULT_LEVEL);

#define LVGL_MAX_SLEEP_MS 5U
#define APP_DISPLAY_ROTATION LV_DISPLAY_ROTATION_90

BUILD_ASSERT(IS_ENABLED(CONFIG_MCUX_ELCDIF_PXP) &&
	     IS_ENABLED(CONFIG_MCUX_ELCDIF_PXP_ROTATE_270),
	     "Landscape LVGL rotation requires eLCDIF PXP rotate 270");

#ifdef APP_HAS_GENERATED_UI
lv_ui guider_ui;
#endif

static void app_display_configure_landscape(void)
{
	lv_display_t *display = lv_display_get_default();

	if (display == NULL) {
		LOG_ERR("LVGL display is not ready");
		return;
	}

	lv_display_set_rotation(display, APP_DISPLAY_ROTATION);
	LOG_INF("LVGL logical display: %dx%d",
		(int)lv_display_get_horizontal_resolution(display),
		(int)lv_display_get_vertical_resolution(display));
}

#ifdef APP_HAS_SQUARELINE_UI
struct app_home_slider_binding {
	const char *name;
	int32_t *value;
};

static lv_obj_t *home_status_label;
static int32_t home_strength;
static int32_t home_length;

static struct app_home_slider_binding home_strength_binding = {
	.name = "strength",
	.value = &home_strength,
};

static struct app_home_slider_binding home_length_binding = {
	.name = "length",
	.value = &home_length,
};

static void app_home_status_update(void)
{
	if (home_status_label != NULL) {
		lv_label_set_text_fmt(home_status_label, "Strength %d | %d ml",
				      (int)home_strength, (int)(home_length * 100));
	}
}

static void app_home_slider_event_cb(lv_event_t *event)
{
	struct app_home_slider_binding *binding = lv_event_get_user_data(event);
	lv_obj_t *slider = lv_event_get_target(event);

	*binding->value = lv_slider_get_value(slider);
	app_home_status_update();
	LOG_INF("Home %s slider: %d", binding->name, (int)*binding->value);
}

static void app_ui_click_event_cb(lv_event_t *event)
{
	LOG_INF("UI touch: %s", (char *)lv_event_get_user_data(event));
}

static void app_squareline_bind_home_test(void)
{
	lv_obj_t *strength_slider;
	lv_obj_t *length_slider;
	lv_obj_t *start_button;
	lv_obj_t *extract_button;

	if (ui_Home_header_header4 == NULL ||
	    ui_Home_home_sliders_home_slider == NULL ||
	    ui_Home_home_sliders_home_slider1 == NULL ||
	    ui_Splash_screen_CTA_container_CTA_container9 == NULL ||
	    ui_Home_CTA_container_CTA_container == NULL) {
		LOG_WRN("SquareLine home test objects are not ready");
		return;
	}

	home_status_label = ui_comp_get_child(
		ui_Home_header_header4,
		UI_COMP_CONTAINER_HEADER_CONTAINER_HEADER_PANEL_LABEL_TITLE);
	strength_slider = ui_comp_get_child(
		ui_Home_home_sliders_home_slider,
		UI_COMP_CONTAINER_HOME_SLIDERS_CONTAINER_STRENGTH_CONTAINER_SLIDER_SLIDER_STRENGTH);
	length_slider = ui_comp_get_child(
		ui_Home_home_sliders_home_slider1,
		UI_COMP_CONTAINER_HOME_SLIDERS_CONTAINER_LENGTH_CONTAINER_SLIDER_SLIDER_LENGTH);
	start_button = ui_comp_get_child(
		ui_Splash_screen_CTA_container_CTA_container9,
		UI_COMP_CONTAINER_CTA_CONTAINER_PANEL_CIRCLE_PANEL);
	extract_button = ui_comp_get_child(
		ui_Home_CTA_container_CTA_container,
		UI_COMP_CONTAINER_CTA_CONTAINER_PANEL_CIRCLE_PANEL);

	if (home_status_label == NULL || strength_slider == NULL ||
	    length_slider == NULL || start_button == NULL ||
	    extract_button == NULL) {
		LOG_WRN("SquareLine home test binding is incomplete");
		return;
	}

	home_strength = lv_slider_get_value(strength_slider);
	home_length = lv_slider_get_value(length_slider);
	app_home_status_update();

	lv_obj_add_event_cb(strength_slider, app_home_slider_event_cb,
			    LV_EVENT_VALUE_CHANGED, &home_strength_binding);
	lv_obj_add_event_cb(length_slider, app_home_slider_event_cb,
			    LV_EVENT_VALUE_CHANGED, &home_length_binding);
	lv_obj_add_event_cb(start_button, app_ui_click_event_cb,
			    LV_EVENT_CLICKED, "splash start");
	lv_obj_add_event_cb(extract_button, app_ui_click_event_cb,
			    LV_EVENT_CLICKED, "home extract");
}
#endif

#ifdef APP_HAS_LV_EDITOR_UI
static lv_obj_t *editor_button_status_label;
static uint32_t editor_button_click_count;

static lv_obj_t *app_find_child_by_type(lv_obj_t *parent,
					const lv_obj_class_t *class_p)
{
	uint32_t child_count = lv_obj_get_child_count(parent);

	for (uint32_t index = 0U; index < child_count; index++) {
		lv_obj_t *child = lv_obj_get_child(parent, index);

		if (lv_obj_check_type(child, class_p)) {
			return child;
		}
	}

	return NULL;
}

static void app_editor_button_status_update(void)
{
	if (editor_button_status_label != NULL) {
		lv_label_set_text_fmt(editor_button_status_label, "Button clicks: %u",
				      (unsigned int)editor_button_click_count);
	}
}

static void app_editor_button_event_cb(lv_event_t *event)
{
	lv_obj_t *button = lv_event_get_target(event);

	editor_button_click_count++;
	lv_obj_set_style_bg_color(button,
				  lv_color_hex((editor_button_click_count % 2U) != 0U ?
					       0x0b7a53 : 0x2c2c2c),
				  0);
	app_editor_button_status_update();
	LOG_INF("LVGL Editor button clicks: %u",
		(unsigned int)editor_button_click_count);
}

static void app_editor_bind_hello_test(lv_obj_t *hello_screen)
{
	lv_obj_t *button;

	if (hello_screen == NULL) {
		LOG_WRN("LVGL Editor hello screen is not ready");
		return;
	}

	button = app_find_child_by_type(hello_screen, &lv_button_class);
	if (button == NULL) {
		LOG_WRN("LVGL Editor hello button was not found");
		return;
	}

	editor_button_status_label = lv_label_create(hello_screen);
	lv_obj_set_align(editor_button_status_label, LV_ALIGN_TOP_MID);
	lv_obj_set_y(editor_button_status_label, 36);
	lv_obj_set_style_text_color(editor_button_status_label,
				    lv_color_hex(0xffffff), 0);

	app_editor_button_status_update();
	lv_obj_add_event_cb(button, app_editor_button_event_cb,
			    LV_EVENT_CLICKED, NULL);
}
#endif

int main(void)
{
	const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

	if (!device_is_ready(display_dev)) {
		LOG_ERR("Display device is not ready");
		return 0;
	}

	app_display_configure_landscape();

#ifdef APP_HAS_FRAME_UI
	ui_frame_1_init();
	ui_frame_1_button_display();
	ui_frame_1_load();
#elif defined(APP_HAS_SQUARELINE_UI)
	ui_init();
	app_squareline_bind_home_test();
#elif defined(APP_HAS_LV_EDITOR_UI)
	lv_obj_t *hello_screen;

	testtool_init(NULL);
	hello_screen = hello_create();
	if (hello_screen != NULL) {
		lv_screen_load(hello_screen);
	}
	app_editor_bind_hello_test(hello_screen);
#elif defined(APP_HAS_REAL_XML_UI)
	app_ui_start();
#elif defined(APP_HAS_GENERATED_UI)
	setup_ui(&guider_ui);
	events_init(&guider_ui);
#ifdef APP_HAS_CUSTOM_UI
	custom_init(&guider_ui);
#endif
#else
	LOG_WRN("No UI source found under src/ui");
#endif

	(void)lv_timer_handler();
	(void)display_blanking_off(display_dev);

#if defined(APP_HAS_FRAME_UI) || defined(APP_HAS_SQUARELINE_UI) || \
	defined(APP_HAS_LV_EDITOR_UI) || defined(APP_HAS_REAL_XML_UI) || \
	defined(APP_HAS_GENERATED_UI)
	LOG_INF("LVGL UI started");
#else
	LOG_INF("LVGL shell started");
#endif

	while (1) {
		uint32_t sleep_ms = lv_timer_handler();

		k_msleep(MIN(sleep_ms, LVGL_MAX_SLEEP_MS));
	}

	return 0;
}
