# MIMXRT1170-EVKB Figma LVGL Zephyr

This project runs an LVGL UI on the NXP MIMXRT1170-EVKB with the
`rk055hdmipi4ma0` display shield.

For full environment setup, install steps, Zephyr SDK setup, and sample build
commands, see [SETUP_ENVIRONMENT.md](SETUP_ENVIRONMENT.md).

## Target

- Board: `mimxrt1170_evk@B/mimxrt1176/cm7`
- Shield: `rk055hdmipi4ma0`
- App: `my_display_app`

## Build And Flash

From the workspace root:

```powershell
.\.venv\Scripts\Activate.ps1
west build -p always -b mimxrt1170_evk@B/mimxrt1176/cm7 --shield rk055hdmipi4ma0 my_display_app
west flash -r linkserver
```

If the app is inside a west `app/` folder, build `app/my_display_app` instead of
`my_display_app`.

After flashing, the board resets and starts the UI. The display should show the
coffee UI. Serial console is `115200 8N1`.

## Why `my_display_app/src/ui` Exists

`my_display_app/src/ui` is the generated LVGL Editor project. It contains the UI
screens, image assets, fonts, and generated C files that are compiled into the
firmware.

Main things inside:

- `screens/*.xml`: editable screen layouts.
- `screens/*_gen.c`: generated screen code.
- `images/` and `fonts/`: UI assets and generated embedded data.
- `file_list_gen.cmake`: tells CMake which generated UI files to compile.

Treat this folder as generated output. It is okay to replace it with a fresh
LVGL Editor export, but do not put app logic here.

## Regenerating The UI

When exporting from LVGL Editor, copy the contents of the exported
`real_xml_project` folder into:

```text
my_display_app/src/ui/
```

Copy the generated project files and folders such as:

```text
components/
fonts/
images/
screens/
widgets/
component_lib_list_gen.cmake
file_list_gen.cmake
globals.xml
project.xml
project_local.xml
real_xml_project.c
real_xml_project.h
real_xml_project_gen.c
real_xml_project_gen.h
user_config.cmake
```

Do not copy editor build folders:

```text
preview-bin/
preview-build/
```

Do not overwrite app runtime files outside `src/ui`:

```text
my_display_app/src/app_ui.c
my_display_app/src/app_ui.h
my_display_app/src/ui_runtime/
my_display_app/src/main.c
my_display_app/prj.conf
my_display_app/CMakeLists.txt
```

After replacing generated UI output, check these generated files:

- `src/ui/file_list_gen.cmake` includes every new `screens/*_gen.c` file.
- `src/ui/real_xml_project_gen.h` includes every new `screens/*_gen.h` file.
- New screens have predictable create functions, for example
  `toppingscreen_create()`.

If an incremental build behaves strangely after replacing generated files, run a
pristine build:

```powershell
west build -p always -b mimxrt1170_evk@B/mimxrt1176/cm7 --shield rk055hdmipi4ma0 my_display_app
```

## Where App Logic Goes

Generated layout is the source of truth for object positions, sizes, colors, and
assets. Runtime code should bind events and update data, not move generated UI
objects around.

App runtime is split like this:

- `src/app_ui.c`: creates generated screens and controls navigation.
- `src/ui_runtime/app_ui_internal.h`: shared app state, screen pointers, and
  controller APIs.
- `src/ui_runtime/app_ui_helpers.c`: shared drink metadata and helper functions.
- `src/ui_runtime/home_screen_controller.c`: home screen start button.
- `src/ui_runtime/drink_screen_controller.c`: drink selection behavior.
- `src/ui_runtime/topping_screen_controller.c`: topping sliders, milk/coffee/ice
  percentages, size buttons, and brew button behavior.
- `src/ui_runtime/order_screen_controller.c`: brewing progress and status text.
- `src/ui_runtime/final_screen_controller.c`: final screen menu button.

Do not add persistent custom logic to:

```text
src/ui/screens/*_gen.c
src/ui/real_xml_project*.c
src/ui/user_config.cmake
```

Those files may be replaced by code generation.

## Adding A New Screen

1. Create the screen in LVGL Editor with a stable name, for example
   `paymentscreen`.
2. Give interactive objects stable names in LVGL Editor, for example
   `pay_button` or `back_button`.
3. Regenerate and replace `my_display_app/src/ui/`.
4. Confirm the generated output contains:

```text
src/ui/screens/paymentscreen_gen.c
src/ui/screens/paymentscreen_gen.h
paymentscreen_create()
```

5. Add a screen pointer to `struct app_ui_screens` in
   `src/ui_runtime/app_ui_internal.h`.
6. Create the screen in `src/app_ui.c` by calling the generated create function.
7. Add a new controller file under `src/ui_runtime/`, for example
   `payment_screen_controller.c`.
8. Add that controller to `APP_UI_RUNTIME_SOURCES` in `my_display_app/CMakeLists.txt`.
9. Bind generated objects by name with `lv_obj_find_by_name()`.
10. Keep layout in LVGL Editor. Do not set generated object `x`, `y`, `width`, or
    `height` in runtime unless it is a deliberate runtime-created object.

For optional generated objects, use a fallback pattern. The topping screen does
this for `brew_button`: if LVGL Editor generates an object named `brew_button`,
runtime binds it; otherwise runtime creates a simple fallback button.

## Display Rotation

Landscape rotation is app-level configuration, not generated UI logic:

- `src/main.c` calls `lv_display_set_rotation(..., LV_DISPLAY_ROTATION_90)`.
- `prj.conf` enables eLCDIF/PXP rotation with
  `CONFIG_MCUX_ELCDIF_PXP_ROTATE_270=y`.

Do not move rotation setup into generated files. If the physical screen is
upside down after flashing, swap the pair to `LV_DISPLAY_ROTATION_270` and
`CONFIG_MCUX_ELCDIF_PXP_ROTATE_90`.

## Editing The UI

Edit visual layout in LVGL Editor and regenerate the files under `src/ui`.
Implement app behavior in `src/ui_runtime`.
