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
- `app_ui.c`: app glue code that starts the generated UI.

Do not delete this folder unless you are replacing the UI.

## Editing The UI

Edit the UI in LVGL Editor or update the XML files under `src/ui/screens`.
Generated files may be overwritten by the editor, so keep manual app logic in
`src/main.c` or `src/ui/app_ui.c`.
