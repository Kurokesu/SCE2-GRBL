message(STATUS "Updating bootloader dependencies...")
execute_process(
    COMMAND make prerequisites
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
)

add_custom_target(build_boot
    COMMAND make
        FWNAME=${BOOTLOADER_NAME}
        DFU_USER_CONFIG=${CMAKE_CURRENT_LIST_DIR}/bootloader_config.h
        DFU_VENDOR_ID=${BOOT_USB_VENDOR_ID}
        DFU_DEVICE_ID=${BOOT_USB_PRODUCT_ID}
        ${TARGET_MCU}
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32
    COMMENT "Building ${BOOTLOADER_NAME}"
    BYPRODUCTS
        ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${BOOTLOADER_NAME}.hex
        ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${BOOTLOADER_NAME}.bin
        ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${BOOTLOADER_NAME}.elf
        ${CMAKE_CURRENT_LIST_DIR}/sboot-stm32/build/${BOOTLOADER_NAME}.map
)
