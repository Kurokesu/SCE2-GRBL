set(bootloader_name sce2-grbl-boot)
set(mcu_target stm32f103xb)

# Add a custom target to build the sboot-stm32 using its Makefile
add_custom_target(sce2-grbl-boot ALL
    COMMAND make
        FWNAME=${bootloader_name}
        CMSIS=${CMAKE_CURRENT_LIST_DIR}/cmsis_5
        CMSISDEV=${CMAKE_CURRENT_LIST_DIR}/stm32h
        DFU_USER_CONFIG=${CMAKE_CURRENT_LIST_DIR}/bootloader_config.h
        ${mcu_target}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
    COMMENT "Building ${bootloader_name}"
)
