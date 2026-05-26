/**
 * @file real_xml_project_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "real_xml_project_gen.h"

#if LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * font_brewing;
extern lv_font_t font_brewing_data;
lv_font_t * font_status;
extern lv_font_t font_status_data;

/*----------------
 * Images
 *----------------*/

const void * coffee_maker_hero;
extern const void * coffee_maker_hero_data;
const void * caramel_frappe;
extern const void * caramel_frappe_data;
const void * latte;
extern const void * latte_data;
const void * mocha_cream;
extern const void * mocha_cream_data;
const void * caramel_macchiato;
extern const void * caramel_macchiato_data;
const void * frame_3;
extern const void * frame_3_data;

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Subjects
 *----------------*/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void real_xml_project_init_gen(const char * asset_path)
{
    char buf[256];


    /*----------------
     * Fonts
     *----------------*/

    /* get font 'font_brewing' from a C array */
    font_brewing = &font_brewing_data;
    /* get font 'font_status' from a C array */
    font_status = &font_status_data;


    /*----------------
     * Images
     *----------------*/
    coffee_maker_hero = &coffee_maker_hero_data;
    caramel_frappe = &caramel_frappe_data;
    latte = &latte_data;
    mocha_cream = &mocha_cream_data;
    caramel_macchiato = &caramel_macchiato_data;
    frame_3 = &frame_3_data;

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Subjects
     *----------------*/
    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */

    /* Register fonts */
    lv_xml_register_font(NULL, "font_brewing", font_brewing);
    lv_xml_register_font(NULL, "font_status", font_status);

    /* Register subjects */

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "coffee_maker_hero", coffee_maker_hero);
    lv_xml_register_image(NULL, "caramel_frappe", caramel_frappe);
    lv_xml_register_image(NULL, "latte", latte);
    lv_xml_register_image(NULL, "mocha_cream", mocha_cream);
    lv_xml_register_image(NULL, "caramel_macchiato", caramel_macchiato);
    lv_xml_register_image(NULL, "frame_3", frame_3);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/