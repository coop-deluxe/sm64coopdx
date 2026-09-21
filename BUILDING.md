# Building

## Download the source code

You can either download the source code for this project as a ZIP, or obtain it using `git clone`:

```sh
git clone https://github.com/coop-deluxe/sm64coopdx.git
cd sm64coopdx
```

You can also clone the `dev` branch by appending `-b dev` to the clone command:

```sh
git clone https://github.com/coop-deluxe/sm64coopdx.git -b dev
cd sm64coopdx
```

This sets the target branch to `dev`. You can switch `dev` out for any branch you may want to compile.

## Installing Dependencies

### Windows

#### Setup MSYS2 UCRT64

Download the newest version of the MSYS2 installer from [here](https://github.com/msys2/msys2-installer/releases) and install it.

Run UCRT64 (`ucrt64.exe`)

Enter `pacman -Syuu` in the prompt and hit Enter. Press `Y` when it asks if you want to update packages. If it asks you to close the prompt, do so, then restart it and run the same command again. This updates the packages to their latest versions.

#### Install Dependencies

```sh
pacman -S unzip make git mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-glew mingw-w64-ucrt-x86_64-SDL2 mingw-w64-ucrt-x86_64-python
```

### Linux

#### Debian/Ubuntu

```sh
sudo apt install build-essential git python3 libglew-dev libsdl2-dev libz-dev libcurl4-openssl-dev
```

#### Fedora

```sh
sudo dnf install make gcc gcc-c++ python3 glew-devel SDL2-devel zlib-devel libcurl-devel
```

#### Arch Linux/Steam OS

```sh
sudo pacman -S base-devel glibc linux-api-headers python sdl2 glew zlib libglvnd curl libcurl-compat
```

### macOS

```sh
brew install make gcc pkg-config sdl2 glew coreutils
```

## Compilation

In the terminal, navigate to the folder in which you cloned or downloaded sm64coopdx if you haven't already.

### Windows and Linux

```sh
make -j$(nproc)
```

### macOS

```sh
gmake -j$(nproc)
```

---

The final build will be found in `build/us_pc/sm64coopdx`. The extension is dependant on your platform.

You can append [build flags](#build-flags) after your `make` or `gmake` command for any needed changes.

# Build Flags

- `-j`: Jobs amount, may speed up compilation. Recommended to use the number of cores, or the result of `nproc`.
- `DISCORD_SDK [0|1]`: Enable or disable Discord Game SDK
- `COOPNET [0|1]`: Enable or disable the CoopNet networking system
- `UPDATER [0|1]` Enable or disable the auto updater
- `WINDOWS_BUILD [0|1]` If `1`, build for Windows. This should automatically be set
- `OSX_BUILD [0|1]` If `1`, build for macOS. This should automatically be set
- `USE_APP [0|1]` Whether or not to pack the files into a `.app` on macOS
- `MIN_MACOS_VERSION` The version of macOS to target
- `DEVELOPMENT [0|1]` Enables or disable development mode, which includes useful development features
- `LUA_UNSAFE [0|1]` Allows unsafe lua calls to be ran. Useful for development purposes, such as profiling. Requires `DEVELOPMENT` to be `1`
- `HANDHELD [0|1]` Makes some small adjustments for handheld devices

For an exhaustive list, please see the `Makefile`!
