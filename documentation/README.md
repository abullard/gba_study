# Settting up a Gameboy Advanced development environment
NOTE: *Following this* [*tutorial*](https://www.gamedev.net/blogs/entry/2268899-gameboy-advance-dev-workflow-in-2020/) *from James Grimwood published March 01, 2020*

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
    * TBD
    * You'll run into others, install them as you need them

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

4. Navigate to your codes directory, run `code .` to install/launch VS Code Server.

5. Here's a basic `.bashrc` file to save @ `$HOME` in WSL:
    ```
    export DEVKITPRO=/opt/devkitpro
    export DEVKITARM=${DEVKITPRO}/devkitARM
    export DEVKITPPC=${DEVKITPRO}/devkitPPC

    export PATH=${DEVKITPRO}/tools/bin:$PATH

    # aliases
    alias reload="clear; source $HOME/.bash_profile"
    alias ll="ls -lha"
    alias editsh="vim $HOME/.bash_profile"
    alias folder="explorer.exe ."
    alias gba="cd $HOME/dev/gba; code ."
    ```
    * alias `gba` will open VS Code to a project folder called `gba`

6. Open VS Code from WSL, this will be your native development environment
    * Install extension [Remote Development extension pack](https://code.visualstudio.com/docs/remote/wsl)
    * Install extension [Native Debug](https://marketplace.visualstudio.com/items?itemName=webfreak.debug)
    * Install extension C/C++ and C/C++ Extension Pack
        * You'll setup your includes and compiler path inside this extenion for Intellisense on header files
    * Set these up according to their docs

7. In WSL navigate to `/opt/devkitpro/examples/gba/template`, and run `cp -r * $HOME/dev/gba/src` to get an example project with a makefile

8. Install [mGBA](https://mgba.io/downloads.html) on your Windows install, we'll create a `tasks.json` file that points to the mounted `/mnt/c` WSL location to run the `mGBA.exe` tool with your ROM.

9. Create the `tasks.json` file, here's James Grimwood's example:
    * NOTE: make sure `template.gba` to whatever name you gave your ROM
    ```
    {
        // See https://go.microsoft.com/fwlink/?LinkId=733558
        // for the documentation about the tasks.json format
        "version": "2.0.0",
        "tasks": [
            {
                "label": "Make",
                "type": "shell",
                "command": "make",
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "options": {
                    "cwd": "${workspaceFolder}/src/template"
                }
            },
            {
                "label": "Make Clean",
                "type": "shell",
                "command": "make clean",
                "options": {
                    "cwd": "${workspaceFolder}/src/template"
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
                    "cwd": "${workspaceFolder}/src/template"
                },
                "command": "make && /mnt/d/Games/Emulators/Gba/mGBA-0.9.3-win64/mGBA.exe template.gba"
            }
        ]
    }
    ```
10. This is bound to change, so I'm simply noting that you'll need to figure it out. There are some files `.vscode/c_cpp_properties.json` & `.vscode/settings.json` that spell out intellisense properties for C and devkitARM. Properties to be aware of:
    * `"compilerPath": "/opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc"` helps intellisense stop complaining about C header files
    * the `includePath` tells VS Code where to look for devkitARM GBA headerfiles:
    ```
    "includePath": [
        "${workspaceFolder}/**",
        "/opt/devkitpro/libgba/**",
        "/opt/devkitpro/libtonc/**"
    ],
    ```
  NOTE: If you change your `compilerPath`, it may wipe out your `includePath`. I saw this happen, and had my go-to-definition break

##### Austin Bullard (summarized steps from James Grimwood) on 07/21/2023
*This document is subject to change, and will probably need refined the next time we install stuff, change it then*
