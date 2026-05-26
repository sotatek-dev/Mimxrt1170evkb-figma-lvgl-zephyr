# MIMXRT1170-EVKB Figma LVGL Zephyr

A Zephyr RTOS GUI bring-up project for MIMXRT1170-EVKB, targeting a Figma-to-LVGL workflow using LVGL and board display integration.

## Environment Setup Guide

This guide prepares a fresh development environment, pulls the Zephyr workspace through `west`, installs Python dependencies, installs the Zephyr SDK toolchain, builds the Zephyr `hello_world` sample for the MIMXRT1170-EVK CM7 core, and flashes it to the board.

## Prerequisites

Install these tools first and make sure they are available in `PATH`:

- Python 3.12 or newer
- Ninja
- CMake
- 7-Zip / `7z`
- Git
- NXP LinkServer

Check the installed versions:

```powershell
python --version
pip --version
cmake --version
ninja --version
git --version
7z
LinkServer --version
```

## Install West

`west` is Zephyr's workspace and build command-line tool.

```powershell
pip3 install -U west
```

Check that it installed correctly:

```powershell
west --version
```

## Initialize The West Workspace

From the parent directory where you want the full workspace to be created, run:

```powershell
west init -m https://github.com/Sotatek-NamNguyen19/Mimxrt1170evkb-figma-lvgl-zephyr.git IMXRT1170EVKB
cd IMXRT1170EVKB
```

This creates a workspace like:

```text
IMXRT1170EVKB/
  app/
    west.yml
  zephyr/
  modules/
  ...
```

The `app/west.yml` manifest controls which Zephyr repositories are pulled.

### If `west init` Fails

If `west init` fails repeatedly, remove the partially initialized workspace files, enable long paths, force Git to use HTTP/1.1, then retry with a shallow clone:

```powershell
git config --global core.longpaths true
git config --global http.version HTTP/1.1
west init -m https://github.com/Sotatek-NamNguyen19/Mimxrt1170evkb-figma-lvgl-zephyr.git IMXRT1170EVKB -o=--depth=1
cd IMXRT1170EVKB
```

On Windows, `core.longpaths true` helps avoid path length failures while cloning Zephyr modules.

## Pull Repositories From `west.yml`

Run this from the workspace root, not from inside `app`:

```powershell
west update --fetch-opt=--depth=1
```

### If `west update` Fails

For unreliable networks or large repository fetches, configure Git and retry the update several times.

PowerShell:

```powershell
git config --global http.version HTTP/1.1
git config --global http.postBuffer 524288000
git config --global core.compression 0

for ($i = 1; $i -le 10; $i++) {
    west update --narrow -o=--depth=1
    if ($LASTEXITCODE -eq 0) {
        break
    }

    Write-Host "Retry $i failed"
    Start-Sleep -Seconds 5
}
```

Git Bash:

```bash
git config --global http.version HTTP/1.1
git config --global http.postBuffer 524288000
git config --global core.compression 0

for i in 1 2 3 4 5 6 7 8 9 10; do
    west update --narrow -o=--depth=1 && break || echo "Retry $i failed"
    sleep 5
done
```

## Export Zephyr To CMake

Run:

```powershell
west zephyr-export
```

This registers Zephyr's CMake package so CMake-based projects can find the Zephyr build system.

## Install Python Packages

Install Python dependencies required by Zephyr and the modules in the workspace:

```powershell
west packages pip --install
```

## Install The Zephyr SDK Toolchain

The Zephyr SDK provides compilers, linkers, and target tools used to build firmware.

```powershell
cd zephyr
west sdk install
cd ..
```

## Build A Sample

`west build` wraps the CMake and Ninja build flow.

Useful options:

- `-p always`: pristine build; clean and reconfigure before building
- `-b <board-target>`: board target to build for
- `samples/hello_world`: source application directory that contains the sample's CMake files

Build Zephyr's `hello_world` sample for the MIMXRT1170-EVK CM7 target:

```powershell
west build -p always -b mimxrt1170_evk/mimxrt1176/cm7 samples/hello_world
```

Build Zephyr's `HDMI sample of rk055hdmipi4ma0` for the MIMXRT1170-EVK CM7 target:

```powershell
west build -p always -b mimxrt1170_evk/mimxrt1176/cm7 --shield rk055hdmipi4ma0 samples/drivers/display
```

The build output is generated under:

```text
build/
```

## Flash The Board

Install NXP LinkServer before flashing and connect the board through its debug USB port.

After a successful build, flash the generated firmware:

```powershell
west flash
```

## Common Command Flow

For a fresh setup, the full flow is:

```powershell
pip3 install -U west

west init -m https://github.com/Sotatek-NamNguyen19/Mimxrt1170evkb-figma-lvgl-zephyr.git IMXRT1170EVKB -o=--depth=1
cd IMXRT1170EVKB

west update --fetch-opt=--depth=1
west zephyr-export
west packages pip --install

cd zephyr
west sdk install
cd ..

west build -p always -b mimxrt1170_evk/mimxrt1176/cm7 samples/hello_world
west flash
```
