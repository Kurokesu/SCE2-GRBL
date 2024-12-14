set(bootloader_name sce2-grbl-boot)

set(bootloader_targets
    stm32f103x8
    stm32f103xb
)

message(STATUS "Updating bootloader dependencies...")
execute_process(
    COMMAND make prerequisites
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
)

function(create_bootloader_target target_mcu)
    set(fw_name ${bootloader_name}-${target_mcu})

    add_custom_target(bootloader-${target_mcu} ALL
        COMMAND make
            FWNAME=${fw_name}
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

foreach(target ${bootloader_targets})
    create_bootloader_target(${target})
endforeach()
