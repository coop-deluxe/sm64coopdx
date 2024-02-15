# sm64coopdx
Online multiplayer mod for the Super Mario 64 PC port that synchronizes all entities and every level for multiple players. Fork of [sm64ex-coop](https://github.com/djoslin0/sm64ex-coop). 

Feel free to report bugs and contribute, but remember, there must be **no upload of any copyrighted asset**. 
Run `./extract_assets.py --clean && make clean` or `make distclean` to clear ROM assets, however this is unnecessary for contributing because the .gitignore file already excludes ROM assets.

## How to Play

The easiest way to play is by using [coopdx-patcher](https://github.com/coop-deluxe/coopdx-patcher/releases/latest/download/coopdx-patcher.zip). Simply drag and drop your ROM into the program or run `coopdx-patcher "your_rom_name.z64"`.

## How to Compile

### Windows:

Download the newest version of the MSYS2 installer from [here](https://github.com/msys2/msys2-installer/releases) and install it.

#### Set up MSYS2.

Run the MINGW64 (`mingw64.exe`) prompt if you wish to build a 64-bit version of the executable, or the MINGW32 (`mingw32.exe`) prompt otherwise.

Enter `pacman -Syuu` in the prompt and hit Enter. Press `Y` when it asks if you want to update packages. If it asks you to close the prompt, do so, then restart it and run the same command again. This updates the packages to their latest versions.

#### Install dependencies.
Enter this command to install packages necessary to build sm64coopdx:

```
pacman -S unzip make git mingw-w64-i686-gcc mingw-w64-x86_64-gcc mingw-w64-i686-glew mingw-w64-x86_64-glew mingw-w64-i686-SDL2 mingw-w64-i686-SDL mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL python3
```

### Linux:

#### Install build dependencies
The build system has the following package requirements:

* python3 >= 3.6
* libsdl2-dev
* libglew-dev
* git

#### Debian / Ubuntu - targeting 32 bits
```
sudo apt install build-essential git python3 libglew-dev:i386 libsdl2-dev:i386 libz-dev:i386
```
#### Debian / Ubuntu - targeting 64 bits
```
sudo apt install build-essential git python3 libglew-dev libsdl2-dev libz-dev
```
#### Fedora - targeting 64 bits
```
sudo dnf install make gcc python3 glew-devel SDL2-devel zlib-devel
```
#### Fedora - targeting 32 bits
```
sudo dnf install python3.i686 glew-devel.i686 SDL2-devel.i686 zlib-devel.i686
```
#### Arch Linux
There is an AUR package (courtesy of @narukeh) avaliable under the name sm64pc-git. Install it using your AUR helper of choice.

If you want to build it yourself:

```
sudo pacman -S base-devel python sdl2 glew zlib-devel
```

#### Void Linux - targeting 64 bits
```
sudo xbps-install -S base-devel python3 SDL2-devel glew-devel libz-dev
```
#### Void Linux - targeting 32 bits
```
sudo xbps-install -S base-devel python3 SDL2-devel-32bit glew-devel-32bit libz-dev-32bit
```
#### Nix OS
It is recommended you create a nix-shell enviroment for compiling it. Create a file called whatever you want.nix and insert

```
{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.gcc pkgs.python310 pkgs.SDL2 pkgs.glew pkgs.zlib pkgs.git];
}
```
then run `nix-shell name.nix`

#### Obtain the source code.
You can either download the ZIP file from github, or clone it with git:
```
git clone https://github.com/coop-deluxe/sm64coopdx.git
cd sm64coopdx
```

### macOS (Intel)
#### Set up Homebrew.
Follow the Homebrew installation instructions [here](https://brew.sh), pasting the given line in Terminal.

#### Install dependencies.
After installing homebrew, enter this command in the terminal to install packages necessary to build sm64coopdx:
```
brew install make mingw-w64 gcc gcc@9 sdl2 pkg-config glew glfw3 libusb audiofile coreutils
```

#### Obtain the source code.
```
git clone https://github.com/djoslin0/sm64ex-coop.git
cd sm64ex-coop
```
#### Assembling libjuice (optional for 10.15 and above).
Run the following script to compile the libjuice library:

`sh tools/mac-intel-essential.sh`

### macOS (ARM)

#### Set up the environment
Start a terminal through Rosetta by running `arch -x86_64 zsh`. All commands in this tutorial must be run within this terminal.

Follow the Homebrew installation instructions [here](https://brew.sh), pasting the given line in Rosetta Terminal.

**TIP:** To make your life easier, add the following aliases to your .zshrc
```
alias ibrew="arch -x86_64 /usr/local/bin/brew"
alias iarch="arch -x86_64"
```

#### Install dependencies.
After installing homebrew, enter this command in the Rosetta terminal to install packages necessary to build sm64coopdx:

```
/usr/local/bin/brew install make mingw-w64 gcc gcc@9 sdl2 pkg-config glew glfw3 libusb audiofile coreutils
```

#### Disable ARM dependencies
You will need to disable `glew` and `SDL2` if you have installed them using native brew. You can do this either by uninstalling them through native brew, or by temporarily renaming the symlinks in `/opt/homebrew/Cellar/[dependency]`. The build system will choke on ARM dependenices without even looking for compatible x86_64 dependencies.


#### Copy baserom(s) for asset extraction.
For each version (jp/us/eu) that you want to build an executable for, put an existing ROM at `./baserom.<version>.z64` for asset extraction.

For example, if you want to build the US version, there should be a ROM file called baserom.us.z64 in the sm64coopdx directory (meaning next to the Makefile). The US version is highly recommended.

If during the build process you get messages saying that the ROM has an incorrect hash, there is a possibility that it's a V64 ROM that needs to be byteswapped. To do that, use this [web tool](https://hack64.net/tools/swapper.php).

#### Run `make`. To turn certain features on and off, append any needed build flags to your `make` invocation like so:

#### Useful Flag information:
`-j[2|4|8|16]`: Jobs amount, may speed up compilation.

`TARGET_BITS [32|64]`: Compile 32-bit or 64-bit.

`DISCORD_SDK [0|1]`: Enable or disable Discord Game SDK.

`COOPNET [0|1]`: Enable or disable the CoopNet networking system.

`HEADLESS [0|1]`: Enable or disable headless mode (meant for servers.)

`RENDER_API [GL|GL_LEGACY|D3D11|D3D12|DUMMY]`: Sets the rendering API.

`WINDOW_API [SDL1|SDL2|DXGI|DUMMY]` Sets the window API.

#### Windows / Linux:
```
make
```
#### macOS (Intel):
```
gmake OSX_BUILD=1
```
#### macOS (ARM):
```
gmake OSX_BUILD=1 TARGET_ARCH=x86_64-apple-darwin TARGET_BITS=64
```

## Goal (accomplished)
Create a mod for the PC port where multiple people can play together online.

Unlike previous multiplayer projects, this one synchronizes enemies and events. This allows players interact with the same world at the same time.

## Lua
sm64coopdx is moddable via Lua, similar to Roblox and Garry's Mod's Lua APIs. To get started, click [here](docs/lua/lua.md) to see the Lua documentation.
