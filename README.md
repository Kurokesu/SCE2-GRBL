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

# Getting Started

## Flashing FW update via bootloader

### Install DFU Utilities

For performing device firmware upgrades via the USB bootloader, `dfu-util` is required.

#### Windows
- **Download dfu-util**: [https://dfu-util.sourceforge.net/releases/](https://dfu-util.sourceforge.net/releases/)
- After downloading ensure the `dfu-util` executable is added to your `Path` environment variable so it can be accessed from the command line.

#### Linux
- **Install dfu-util**:
    ```bash
    sudo apt-get install dfu-util
    ```

#### Test dfu-util Installation:
Open a terminal and run:
```bash
dfu-util --version
```
You should see the version output if the installation was successful.

### Using pre-built release files

If you do not wish to build the firmware from source, you can use the pre-built release files.

1. Download the latest firmware release from the [Releases](https://github.com/Kurokesu/SCE2-GRBL/releases) page.
2. Use `dfu-util` to flash the downloaded `.dfu` file to your device.

```bash
dfu-util -D path/to/downloaded/sce2-grbl.dfu -R
```

### Using built files

If you have built the firmware from source, you can flash the generated `.dfu` file.

```bash
dfu-util -D .\build\stm32f103xb-release\sce2-grbl.dfu -R
```

## Install Build Tools

The following steps are for users who want to build the bootloader and firmware from source. Before you can build the bootloader and firmware, you need to set up your development environment. Below are the steps for installing the necessary tools on **Windows** and **Linux**.

### Windows

#### 1. Ensure `dfu-util` is ready to go
Follow the instructions in the [Install DFU Utilities](#install-dfu-utilities) section to install `dfu-util`.

#### 2. CMake
CMake is a build automation tool that helps manage the build process of the project.

- **Download CMake**: [https://cmake.org/download](https://cmake.org/download)
- Follow the installation instructions and ensure that CMake is added to your system's `Path` environment variable.

#### Test CMake Installation:
Open a terminal and run:
```bash
cmake --version
```
If installed correctly, the CMake version will be displayed.

---

#### 3. Ninja Build System
Ninja is a small, fast build system used by the project.

- **Download Ninja**: [https://github.com/ninja-build/ninja/releases](https://github.com/ninja-build/ninja/releases)
- Add the Ninja executable to your `Path` environment variable so you can run it from the command line.

#### Test Ninja Installation:
Open a terminal and run:
```bash
ninja --version
```
You should see the Ninja version output if installed correctly.

---

#### 4. GNU Arm Toolchain
The STM32 bootloader and firmware project requires the `arm-none-eabi-gcc` toolchain for cross-compiling for ARM-based microcontrollers.

- **Download ARM Toolchain**: [https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- After installing the toolchain, add it to your system’s `Path` environment variable so you can use commands like `arm-none-eabi-gcc` from anywhere.

#### Test GNU Arm Toolchain Installation:
Open a terminal and run:
```bash
arm-none-eabi-gcc --version
```
This should print the version of the ARM compiler.

---

#### 5. Python
Python IntelHex package is used by CMake for merging bootloader and application hex files. 

- **Download Python**: [https://www.python.org/downloads/](https://www.python.org/downloads/)
- During installation, ensure you check the option to add Python to the `Path` environment variable.
- The [intelhex](https://pypi.org/project/intelhex) pip package is used for merging hex files. It is automatically installed by `cmake`. But can also be installed manually:
```bash
pip install -r ./requirements.txt
```

#### Test Python Installation:
Open a terminal and run:
```bash
python --version
```
You should see the Python version. Additionally, test `pip`:
```bash
pip --version
```

---

#### 6. Install Chocolatey
The bootloader project uses a `Makefile` to control its build process. To successfully build the bootloader, you need the `make` utility. We recommend installing the Chocolatey package manager for Windows, which simplifies the installation of `make`.

- **Install Chocolatey**: [Follow the instructions here](https://chocolatey.org/install) or run the following command in `PowerShell`:
    ```pwsh
    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
    ```

#### Test Chocolatey Installation:
Open a terminal and run:
```bash
choco --version
```
You should see the Chocolatey version output.

---

#### 7. Install Make
After installing Chocolatey, use it to install `make`:

- **Command**:
    ```bash
    choco install make
    ```

- Ensure the path to `make` (usually `chocolatey\lib\make\tools\install\bin`) is added to your `Path` environment variable to use the `make` command globally.

#### Test Make Installation:
Open a terminal and run:
```bash
make --version
```
If installed correctly, the Make version will be displayed.

---

#### 8. Install STM32CubeCLI

STM32CubeCLI is a command-line interface for STM32 microcontrollers, which can be used for programming and debugging.

- **Download STM32CubeCLI**: [https://www.st.com/en/development-tools/stm32cubeclt.html](https://www.st.com/en/development-tools/stm32cubeclt.html)
- Follow the installation instructions provided on the website.
- Ensure the STM32CubeCLI executable is added to your `Path` environment variable so it can be accessed from the command line.

#### Test STM32CubeCLI Installation:
Open a terminal and run:
```bash
STM32_Programmer_CLI --version
```
You should see the version output if the installation was successful.

---

### Linux

#### 1. Ensure `dfu-util` is ready to go
Follow the instructions in the [Install DFU Utilities](#install-dfu-utilities) section to install `dfu-util`.

#### 2. CMake
CMake is a build automation tool that helps manage the build process of the project.

- **Install CMake**:
    ```bash
    sudo apt-get install cmake
    ```

#### Test CMake Installation:
Open a terminal and run:
```bash
cmake --version
```
If installed correctly, the CMake version will be displayed.

---

#### 3. Ninja Build System
Ninja is a small, fast build system used by the project.

- **Install Ninja**:
    ```bash
    sudo apt-get install ninja-build
    ```

#### Test Ninja Installation:
Open a terminal and run:
```bash
ninja --version
```
You should see the Ninja version output if installed correctly.

---

#### 4. GNU Arm Toolchain
The STM32 bootloader and firmware project requires the `arm-none-eabi-gcc` toolchain for cross-compiling for ARM-based microcontrollers.

- **Install ARM Toolchain**:
    ```bash
    sudo apt-get install gcc-arm-none-eabi
    ```

#### Test GNU Arm Toolchain Installation:
Open a terminal and run:
```bash
arm-none-eabi-gcc --version
```
This should print the version of the ARM compiler.

---

#### 5. Python
Python IntelHex package is used by CMake for merging bootloader and application hex files. 

- **Install Python**:
    ```bash
    sudo apt-get install python3 python3-pip
    ```

- **Install IntelHex**:
    ```bash
    pip3 install intelhex
    ```

#### Test Python Installation:
Open a terminal and run:
```bash
python3 --version
```
You should see the Python version. Additionally, test `pip`:
```bash
pip3 --version
```

---

#### 6. Install Make
The bootloader project uses a `Makefile` to control its build process. To successfully build the bootloader, you need the `make` utility.

- **Install Make**:
    ```bash
    sudo apt-get install build-essential
    ```

#### Test Make Installation:
Open a terminal and run:
```bash
make --version
```
If installed correctly, the Make version will be displayed.

---

#### 7. Install STM32CubeCLI

STM32CubeCLI is a command-line interface for STM32 microcontrollers, which can be used for programming and debugging.

- **Download STM32CubeCLI**: [https://www.st.com/en/development-tools/stm32cubeclt.html](https://www.st.com/en/development-tools/stm32cubeclt.html)
- Follow the installation instructions provided on the website.
- Extract the downloaded archive and navigate to the extracted directory.
- Copy the `STM32_Programmer_CLI` executable to a directory in your `PATH`, for example:
  ```bash
  sudo cp STM32_Programmer_CLI /usr/local/bin/
  ```

#### Test STM32CubeCLI Installation:
Open a terminal and run:
```bash
STM32_Programmer_CLI --version
```
You should see the version output if the installation was successful.

---

## Build the project

Once all the tools are installed we can finally try to build.

The recommended tool for working with the project is Visual Studio Code (VS Code). VS Code provides tasks that simplify various build aspects and extensions that help with CMake integration. However, building manually is also supported, see [Build manually](#build-manually) section.

### Build using vscode
#### Install recommended extensions

![](doc/vscode_recommended.gif)

#### Select cmake build configuration and build

![](doc/vscode_cmake.gif)

#### Debug builds can be attached to a debugger

![](doc/vscode_debugger.gif)

### Build manually

#### Available target MCUs:
- `stm32f103x8`- target MCU with 64KB flash memory.
- `stm32f103xb`- target MCU with 128KB flash memory.

#### Available build configurations:
- Debug: Builds with debugging information.
  - `./build/stm32f103x8-debug`
  - `./build/stm32f103xb-debug`
- Release: Optimized builds for production.
  - `./build/stm32f103x8-release`
  - `./build/stm32f103xb-release`

#### Available build types:
- `Debug`
- `Release`

#### Available targets
- `sce2-grbl` - build main SCE2-GRBL application.
- `build_app_dfu` - generate application DFU file for firmware updates.
- `build_boot` - build bootloader for MCU.
- `build_full_hex` - generate hex file containing both bootloader and application.
- `flash_app` - flash main application to MCU.
- `flash_app_dfu` - flash application DFU file using bootloader.
- `flash_boot` - flash bootloader to MCU.
- `flash_full_hex` - flash both application and bootloader to MCU.

#### Configure build:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DTARGET_MCU=stm32f103xb -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_TOOLCHAIN_FILE=./cmake/gcc-arm-none-eabi.cmake -S ./ -B ./build/stm32f103xb-release -G Ninja
```

#### Build application:
```bash
cmake --build ./build/stm32f103xb-release
```
