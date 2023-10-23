# Setting up a Gameboy Advanced (GBA) development environment

| Author | Date Changed | Notes|
|--------------|-----------|------------|
| abullard | 09/13/2023 | initial commit |
| abullard | 10/23/2023 | grit, mgba-qt updates |

### PLEASE READ
* *Following this* [*tutorial*](https://www.gamedev.net/blogs/entry/2268899-gameboy-advance-dev-workflow-in-2020/) *from James Grimwood published March 01, 2020*
* [A Technical Manual for the GBA](https://problemkaputt.de/gbatek.htm)
* [Tonc](https://www.coranac.com/tonc/text/toc.htm) is a human guided approached to learning the GBA
    * Please read this and break/fix the example ROMs provided by *Jasper Vijn*, he really did the most for those of us interested in this stuff
* [GRIT (GBA Raster Image Transmogrifier)](https://www.coranac.com/projects/grit/) a makefile/build-pipeline tool to convert `.bmp/.png/.jpg/etc` files into a linkable C library. This lets you use [Aseprite](https://www.aseprite.org/) for Objects and Backgrounds 0-3.

## IDE Setup
1. Install Windows Subsystem for Linux (WSL)
   * Open PowerShell as an Admin user and type in
`Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`
    * Reboot
    * Open the Windows Store and install your Linux Distro of choice. I chose Debian. (I still haven't figured out how to halt the Ubuntu install)
    * Open WSL by searching Windows for Debian on the Start Menu, and allow it to initialise itself.

2. Install Visual Stuido Code on Windows, select the option during install to add it to your PATH, or add it to your PATH manually. You'll need it in your PATH to launch VS Code from WSL.

3. Launch Debian from start menu and install necessary packages
    * sudo apt install Make
    * sudo apt install wget
    * sudo apt install libncurses5
    * sudo apt install xz-utils
    * sudo apt install Python 3
    * sudo apt install mgba-qt
        * default path for me was `/usr/games/mgba-qt`, see `/alias_funcs/mkrom.sh`
    * To Be Determined, you'll run into others, install them as you need them

4. Install [devkitARM](https://github.com/devkitPro/pacman/releases/), you'll need to investigate the releases of this repo on Github to find instructions for a Debian install, as they may have changed.  
    * Currently, you'll need these instructions (the symlink is probably unnessecary):
    ```
    wget https://apt.devkitpro.org/install-devkitpro-pacman
    chmod +x ./install-devkitpro-pacman
    sudo ./install-devkitpro-pacman
    sudo ln -s /proc/self/mounts /etc/mtab
    sudo dkp-pacman -S gba-dev
    ```
    * Select yes on the last command to install gba-dev from devkitPro with pacman

5. Navigate to your codes directory, run `code .` to install/launch VS Code Server.

6. Here's a basic `.bashrc` file to save @ `$HOME` in WSL:
    ```
    # alias bash script imports
    source $HOME/dev/gba_study/alias_funcs/mkrom.sh

    export DEVKITPRO=/opt/devkitpro
    export DEVKITARM=${DEVKITPRO}/devkitARM
    export DEVKITPPC=${DEVKITPRO}/devkitPPC

    export PATH=${DEVKITPRO}/tools/bin:$PATH

    # aliases
    alias reload="clear; source $HOME/.bash_profile"
    alias ll="ls -lha"
    alias editsh="vim $HOME/.bashrc"
    alias folder="explorer.exe ."
    alias gogba="cd $HOME/dev/gba_study"
    alias mkrom="mkrom"
    alias play="cd $HOME/dev/gba_study/playground; gcc main.c -o main; ./main"
    ```
    * alias `play` builds main.c and runs `./main`, this is great for quick checks of bitwise operations
    * check the `/alias_funcs/mkrom` directory in this repository. This is useful for quickly building Tonc's example ROMs and launching them with mgba-qt

7. Open VS Code from WSL, this will be your native development environment
    * Install extension [Remote Development extension pack](https://code.visualstudio.com/docs/remote/wsl)
    * Install extension [Native Debug](https://marketplace.visualstudio.com/items?itemName=webfreak.debug)
    * Install extension C/C++ and C/C++ Extension Pack
        * You'll setup your includes and compiler path inside this extenion for Intellisense on header files
    * Set these up according to their docs

8. In WSL navigate to `/opt/devkitpro/examples/gba/template`, and run `cp -r * $HOME/dev/gba/src` to get an example project with a makefile

9. Create the `tasks.json` file, or copy mine from this repository. Located at `.vscode/tasks.json`
    * NOTE: make sure you update `template.gba` to whatever name you gave your ROM
    ```
    {
        // See https://go.microsoft.com/fwlink/?LinkId=733558
        // for the documentation about the tasks.json format
        "version": "2.0.0",
        "tasks": [
            {
                "label": "Make",
                "type": "shell",
                "command": "clear; kill -9 $(pidof mgba-qt); make",
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "options": {
                    "cwd": "${workspaceFolder}/filbert"
                }
            },
            {
                "label": "Make Clean",
                "type": "shell",
                "command": "make clean",
                "options": {
                    "cwd": "${workspaceFolder}/filbert"
                },
                "problemMatcher": []
            },
            {
                "label": "Run",
                "type": "shell",
                "group": {
                    "kind": "test",
                    "isDefault": true
                },
                "options": {
                    "cwd": "${workspaceFolder}/filbert"
                },
                "command": "clear; make && /usr/games/mgba-qt filbert.gba"
            }
        ]
    }
    ```

10. This is bound to change, so I'm simply noting that you'll need to figure it out. There are some files `.vscode/c_cpp_properties.json` & `.vscode/settings.json` that spell out Intellisense properties for C, devkitARM, and Tonc. Properties to be aware of:
    * `"compilerPath": "/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc"` helps intellisense stop complaining about C header files
    * the `includePath` tells VS Code's Intellisense where to look for GBA header files:
    ```
    "includePath": [
        "/opt/devkitpro/libgba/include",
        "/opt/devkitpro/libtonc/include",
        "${workspaceFolder}/filbert/libgfx/include"
    ],
    ```
  NOTE: If you change your `compilerPath`, it may wipe out your `includePath`. I saw this happen, and had my go-to-definition break

11. This isn't necessary to build, but it makes pixel art easier. Install [GRIT (GBA Raster Image Transmogrifier)](https://www.coranac.com/projects/grit/), this is another resource from Tonc. 
    * You can create sprite assets in Aseprite and drop the exported `.bmp`'s into a directory that converts them to the `libgfx.a` library to link to your ROM, [Learn how here](https://www.coranac.com/man/grit/html/gritmake.htm)
    * I bundled `grit.exe` with my repository and dropped all the extra stuff. Check `/grit` and any file with a `.grit` extension. This may inform your study.
    * Make sure you read the documentation!!!! [Here it is again because it's so important for GRIT](https://www.coranac.com/man/grit/html/grit.htm)

##### Austin Bullard (summarized steps from James Grimwood) on 07/21/2023
*This document is subject to change, and will probably need refined the next time we install stuff, change it then*
