# 4 axis GRBL firmware for Kurokesu SCE-2 module

SCE2-M is a fully integrated stepper motor controller module for digital control for limited space applications. Designed for small 3D printers, laser cutters/engravers, CNC mills, pick and place machines, robots, test fixtures, and other motorized devices. SCE2-M module is the smallest motor controller that requires no external components and runs industry-standard g-code processor with linear interpolation control open-source firmware. 

![](doc/Kurokesu_SCE2-M.jpg)

# Ordering
Order [SCE2-M controller](https://www.kurokesu.com/shop/SCE2-M)

# Documentation
More detailed documentation is on [Kurokesu knowledge base pages](https://wiki.kurokesu.com/shelves/motion-controllers)

# GRBL notice
This repository is based on [usbcnc grbl](https://github.com/usbcnc/grbl) which in turn is based on [native grbl 1.1f](https://github.com/gnea/grbl)<br>

# Dimensions
![](doc/SCE2-M_2.png)

# Getting started
## Toolchain setup
- Install [cmake](https://cmake.org/download)
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to your `Path`
- Install [arm-none-eabi-gcc](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) toolchain, make sure to add it to `Path`

### Bootloader dependancies
The bootloader project uses a `Makefile` for its build process, so your system must be able to run the `make` command.

- [Install chocolatey](https://chocolatey.org/install)
- `choco install make` and add to `Path`

## Recommended vscode extensions (optional)
- [cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

## Build the project

- `cmake --build .\build\release --`
