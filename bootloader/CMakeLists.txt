set(bootloader_name sce2-grbl-boot)
set(mcu_target stm32f103xb)

# Add a custom target to build the submodule using its Makefile
add_custom_target(sce2-grbl-boot ALL
    COMMAND make FWNAME=${bootloader_name} DFU_USER_CONFIG=../bootloader_config.h ${mcu_target} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
    COMMENT "Building ${bootloader_name}"
)

# Include the submodule's headers (if any)
include_directories(${CMAKE_CURRENT_LIST_DIR}/submodule/include)
