set(bootloader_name sce2-grbl-boot)

function(create_bootloader_target target_mcu)
    set(fw_name ${bootloader_name}-${target_mcu})

    add_custom_target(bootloader-${target_mcu} ALL
        COMMAND make
            FWNAME=${fw_name}
            CMSIS=${CMAKE_CURRENT_LIST_DIR}/cmsis_5
            CMSISDEV=${CMAKE_CURRENT_LIST_DIR}/stm32h
            DFU_USER_CONFIG=${CMAKE_CURRENT_LIST_DIR}/bootloader_config.h
            ${target_mcu}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
        COMMENT "Building ${fw_name}"
        BYPRODUCTS
            ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${fw_name}.bin
            ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${fw_name}.hex
            ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${fw_name}.elf
            ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${fw_name}.map
    )
endfunction()

create_bootloader_target(stm32f103x8)
create_bootloader_target(stm32f103xb)
