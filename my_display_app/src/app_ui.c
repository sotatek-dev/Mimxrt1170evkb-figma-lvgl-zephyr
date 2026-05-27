/**
 * @file app_ui.c
 */

#include "app_ui.h"
#include "ui_runtime/app_ui_internal.h"

static struct app_ui_context app_ctx;

void app_ui_load_home_screen(void)
{
    app_order_screen_stop();

    if (app_ctx.screens.home != NULL) {
        lv_screen_load(app_ctx.screens.home);
    }
}

void app_ui_load_drink_screen(void)
{
    app_order_screen_stop();

    if (app_ctx.screens.drink != NULL) {
        lv_screen_load(app_ctx.screens.drink);
    }
}

void app_ui_select_drink(const struct app_drink * drink)
{
    app_ctx.selected_drink = drink != NULL ? drink : &app_drinks[0];
    app_order_screen_stop();

#if APP_HAS_TOPPING_SCREEN
    if (app_ctx.screens.topping != NULL) {
        app_topping_screen_show(&app_ctx);
        return;
    }

    LOG_WRN("toppingscreen was generated but could not be created");
#else
    LOG_WRN("toppingscreen is not generated; loading brewing screen directly");
#endif

    app_ui_start_order_screen();
}

void app_ui_start_order_screen(void)
{
    app_order_screen_start(&app_ctx);

    if (app_ctx.screens.order != NULL) {
        lv_screen_load(app_ctx.screens.order);
    }
}

void app_ui_load_final_screen(void)
{
    if (app_ctx.screens.final != NULL) {
        lv_screen_load(app_ctx.screens.final);
    }
}

void app_ui_start(void)
{
    app_ui_context_init(&app_ctx);
    real_xml_project_init(NULL);

    app_ctx.screens.home = homescreen_create();
    app_ctx.screens.drink = drinkscreen_create();
#if APP_HAS_TOPPING_SCREEN
    app_ctx.screens.topping = toppingscreen_create();
#endif
    app_ctx.screens.order = orderscreen_create();
    app_ctx.screens.final = finalscreen_create();

    app_order_screen_bind(&app_ctx);
    app_home_screen_bind(&app_ctx);
    app_drink_screen_bind(&app_ctx);
    app_topping_screen_bind(&app_ctx);
    app_final_screen_bind(&app_ctx);

    if (app_ctx.screens.home != NULL) {
        lv_screen_load(app_ctx.screens.home);
    }
}
