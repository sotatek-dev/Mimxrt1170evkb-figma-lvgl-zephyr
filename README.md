# Mimxrt1170evkb-figma-lvgl-zephyr
A Zephyr RTOS GUI bring-up project for MIMXRT1170-EVKB, targeting a Figma-to-LVGL workflow using LVGL and board display integration.

How to pull this repo using west : 
```
west init -m https://github.com/Sotatek-NamNguyen19/Mimxrt1170evkb-figma-lvgl-zephyr.git IMXRT1170EVKB
cd IMXRT1170EVKB
west update --fetch-opt=--depth=1
```