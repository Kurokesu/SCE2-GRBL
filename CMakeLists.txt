cmake_minimum_required(VERSION 3.22)

#
# User is free to modify the file as much as necessary
#

list(APPEND CMAKE_MODULE_PATH "{{sr:cmake_path}}")
message(STATUS "Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
include("cmake/gcc-arm-none-eabi.cmake")
message(STATUS "Build CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

# Define the target MCU
if(NOT DEFINED TARGET_MCU)
    set(TARGET_MCU "STM32F103C8" CACHE STRING "Target STM32 MCU")
endif()

message(STATUS "Target MCU: ${TARGET_MCU}")

# Core project settings
project(sce2-grbl)
enable_language(C CXX ASM)
message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

# Check if we're in a git repository
find_package(Git REQUIRED)

# Update git submodules
message(STATUS "Updating Git submodules...")
execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE result
)

if(result)
    message(FATAL_ERROR "Failed to update submodules (error code: ${result})")
endif()

find_package(Python REQUIRED COMPONENTS Interpreter)

# Path to requirements.txt
set(REQUIREMENTS_FILE "${CMAKE_SOURCE_DIR}/requirements.txt")

set(VIRTUAL_ENV_DIR ${CMAKE_SOURCE_DIR}/build/venv)

# Create and activate virtual environment
execute_process(
    COMMAND ${Python_EXECUTABLE} -m venv ${VIRTUAL_ENV_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

if(CMAKE_HOST_WIN32)
    message(STATUS "Host OS: Windows")
    set(PYTHON_VENV_DIR ${VIRTUAL_ENV_DIR}/Scripts)
else()
    message(STATUS "Host OS: Linux")
    set(PYTHON_VENV_DIR ${VIRTUAL_ENV_DIR}/bin)
endif()

set(PYTHON_COMMAND ${PYTHON_VENV_DIR}/python)
message(STATUS "Python command: ${PYTHON_COMMAND}")

# Install Python packages in virtual environment
execute_process(
    COMMAND ${PYTHON_COMMAND} -m pip install -r ${REQUIREMENTS_FILE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(PYTHON_HEXMERGE "${PYTHON_VENV_DIR}/hexmerge.py")

# Path to the STM32CubeProgrammer CLI tool
set(STM32CUBE_PROG_COMMAND "STM32_Programmer_CLI")

# Path to dfu-util
set(DFU_UTIL_COMMAND "dfu-util")
set(DFU_SUFFIX_COMMAND "dfu-suffix")

set(BOOTLOADER_NAME_PREFIX sce2-grbl-boot)
set(BOOTLOADER_NAME ${BOOTLOADER_NAME_PREFIX}-${TARGET_MCU})

set(APP_BIN_FILE ${CMAKE_PROJECT_NAME}.bin)
set(APP_HEX_FILE ${CMAKE_PROJECT_NAME}.hex)
set(FULL_HEX_FILE ${CMAKE_PROJECT_NAME}_full.hex)
set(DFU_FILE ${CMAKE_PROJECT_NAME}.dfu)
set(BOOT_HEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/bootloader/sboot-stm32/build/${BOOTLOADER_NAME}.hex)

set(BOOT_USB_VENDOR_ID 0x16D0)
set(BOOT_USB_PRODUCT_ID 0x10A2)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Core MCU flags, CPU type, instruction set and FPU setup
set(cpu_PARAMS 
    -mthumb

    -mcpu=cortex-m3
    -mfloat-abi=soft
)

# Sources
set(sources_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/startup_stm32f10x_md.s
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system_stm32f10x.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coolant_control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/eeprom.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gcode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/jog.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/limits.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/motion_control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/nuts_bolts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/planner.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/print.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/probe.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/report.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serial.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/spindle_control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stepper.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/syscall.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tmc2300.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_int.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_mem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_regs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/src/usb_sil.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/hw_config.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb_desc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb_endp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb_istr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb_prop.c
    ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/util/stm32f10x_it.c
)

# Include directories for all compilers
set(include_DIRS)

# Include directories for each compiler
set(include_c_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/CMSIS/Device/ST/STM32F10x/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/STM32F10x_StdPeriph_Driver/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/stm_usb_fs_lib/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/usb
    ${CMAKE_CURRENT_SOURCE_DIR}/util
)

set(include_cxx_DIRS)
set(include_asm_DIRS)

# Symbols definition for all compilers
set(symbols_SYMB
    "STM32F10X_MD"
    "USE_STDPERIPH_DRIVER"
    "LEDBLINK"
    "USEUSB"
    "STM32F103C8"
    "STM32F103C8T6"
    "_GRBL_"
    "__ASSEMBLY__"
    "USE_TMC2300"
)

# Symbols definition for each compiler
set(symbols_c_SYMB)
set(symbols_cxx_SYMB)
set(symbols_asm_SYMB)

# Link directories and names of libraries
set(link_DIRS)
set(link_LIBS)

# Linker script
set(linker_script_SRC ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_MCU}_flash.ld)

# Compiler options
set(compiler_OPTS)

# Linker options
set(linker_OPTS)

# Add bootloader subdirectory for managing dependancies
add_subdirectory(bootloader)

# Link directories setup
# Must be before executable is added
link_directories(${CMAKE_PROJECT_NAME} ${link_DIRS})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${sources_SRCS})

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${include_DIRS}
    $<$<COMPILE_LANGUAGE:C>: ${include_c_DIRS}>
    $<$<COMPILE_LANGUAGE:CXX>: ${include_cxx_DIRS}>
    $<$<COMPILE_LANGUAGE:ASM>: ${include_asm_DIRS}>
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ${symbols_SYMB}
    $<$<COMPILE_LANGUAGE:C>: ${symbols_c_SYMB}>
    $<$<COMPILE_LANGUAGE:CXX>: ${symbols_cxx_SYMB}>
    $<$<COMPILE_LANGUAGE:ASM>: ${symbols_asm_SYMB}>

    # Configuration specific
    $<$<CONFIG:Debug>: >
    $<$<CONFIG:Release>: >
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${link_LIBS})

# Compiler options
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    ${cpu_PARAMS}
    ${compiler_OPTS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:C>: >
    $<$<COMPILE_LANGUAGE:CXX>:

    # -Wno-volatile
    # -Wold-style-cast
    # -Wuseless-cast
    # -Wsuggest-override
    >
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Ofast>
)

# Linker options
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${linker_script_SRC}
    ${cpu_PARAMS}
    ${linker_OPTS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -u _printf_float # STDIO float formatting support (remove if not used)
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,-z,max-page-size=8 # Allow good software remapping across address space (with proper GCC section making)
    -Wl,--print-memory-usage
)

# Execute post-build to print size, generate hex and bin
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${APP_HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${APP_BIN_FILE}
    BYPRODUCTS ${APP_HEX_FILE} ${APP_BIN_FILE}
)

add_custom_command(
    OUTPUT ${DFU_FILE}
    COMMENT "Generating DFU file ${DFU_FILE} with vendor id ${BOOT_USB_VENDOR_ID} and product id ${BOOT_USB_PRODUCT_ID}"
    COMMAND ${CMAKE_COMMAND} -E copy ${APP_BIN_FILE} ${DFU_FILE}
    COMMAND ${DFU_SUFFIX_COMMAND} -v ${BOOT_USB_VENDOR_ID} -p ${BOOT_USB_PRODUCT_ID} --add ${DFU_FILE}
    MAIN_DEPENDENCY ${APP_BIN_FILE}
)

add_custom_command(
    OUTPUT ${FULL_HEX_FILE}
    COMMENT "Generating full hex file containing bootloader + application ${FULL_HEX_FILE}"
    COMMAND ${PYTHON_COMMAND} ${PYTHON_HEXMERGE} --output=${FULL_HEX_FILE} --overlap=replace ${BOOT_HEX_FILE} ${APP_HEX_FILE}
    DEPENDS ${BOOT_HEX_FILE} ${APP_HEX_FILE}
)

add_custom_target(build_app_dfu
    DEPENDS ${DFU_FILE}
)

add_custom_target(build_full_hex
    DEPENDS ${FULL_HEX_FILE}
)

add_custom_target(flash_app
    COMMAND ${STM32CUBE_PROG_COMMAND} -c port=SWD -w ${APP_HEX_FILE}
    COMMENT "Flashing application using STM32CubeProgrammer"
    DEPENDS ${APP_HEX_FILE}
)

add_custom_target(flash_app_dfu
    COMMAND ${DFU_UTIL_COMMAND} -D ${DFU_FILE} -R
    COMMENT "Flashing app using bootloader"
    DEPENDS ${DFU_FILE}
)

add_custom_target(flash_boot
    COMMAND ${STM32CUBE_PROG_COMMAND} -c port=SWD -w ${BOOT_HEX_FILE}
    COMMENT "Flashing bootloader using STM32CubeProgrammer"
    DEPENDS ${BOOT_HEX_FILE}
)

add_custom_target(flash_full_hex
    COMMAND ${STM32CUBE_PROG_COMMAND} -c port=SWD -w ${FULL_HEX_FILE}
    COMMENT "Flashing application and bootloader using STM32CubeProgrammer"
    DEPENDS ${FULL_HEX_FILE}
)
