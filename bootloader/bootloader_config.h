#ifndef BOOTLOADER_CONFIG
#define BOOTLOADER_CONFIG

/* Skip unwanted dfuDNLOAD_SYNC phase. Slightly improve speed, but doesn't meet DFU1.1 state diagram */
#define DFU_DNLOAD_NOSYNC   _DISABLE

/** Add extra DFU interface for EEPROM */
#define DFU_INTF_EEPROM     _DISABLE

/** Firmware can be uploaded from device */
#ifndef DFU_CAN_UPLOAD
#define DFU_CAN_UPLOAD      _ENABLE
#endif
/** Handle DFU_DETACH request in DFU mode. System reset will be issued. */
#ifndef DFU_DETACH
#define DFU_DETACH          _ENABLE
#endif
/** Whether application image is verified by a checksum algorithm */
#ifndef DFU_VERIFY_CHECKSUM
#define DFU_VERIFY_CHECKSUM _DISABLE
#endif
/** Memory Readout Protection level **/
#ifndef DFU_SEAL_LEVEL
#define DFU_SEAL_LEVEL      0
#endif
/* USB VID */
#ifndef DFU_VENDOR_ID
#define DFU_VENDOR_ID       0x0483
#endif
/* USB PID */
#ifndef DFU_DEVICE_ID
#define DFU_DEVICE_ID       0xDF11
#endif
/* USB manufacturer string */
#ifndef DFU_STR_MANUF
#define DFU_STR_MANUF       "Your company name"
#endif
/* USB product sting */
#ifndef DFU_STR_PRODUCT
#define DFU_STR_PRODUCT     "Secure bootloader"
#endif
/* USB string for DFU configureation string descriptor. */
#ifndef DFU_DSC_CONFIG
#define DFU_DSC_CONFIG      _ENABLE
#endif
#ifndef DFU_STR_CONFIG
#define DFU_STR_CONFIG      "DFU"
#endif
/* USB string for DFU flash interface string descriptor. */
#ifndef DFU_DSC_FLASH
#define DFU_DSC_FLASH       _ENABLE
#endif
#ifndef DFU_STR_FLASH
#define DFU_STR_FLASH       "Internal flash"
#endif
/* USB string for DFU EEPROM interface sreing descriptor */
#ifndef DFU_DSC_EEPROM
#define DFU_DSC_EEPROM      _ENABLE
#endif
#ifndef DFU_STR_EEPROM
#define DFU_STR_EEPROM       "Internal EEPROM"
#endif
/* USB EP0 size. Must be 8 for USB FS */
#define DFU_EP0_SIZE        8
/* DFU properties */
#ifndef DFU_POLL_TIMEOUT
#define DFU_POLL_TIMEOUT    20
#endif
#ifndef DFU_DETACH_TIMEOUT
#define DFU_DETACH_TIMEOUT  200
#endif
#ifndef DFU_BLOCKSZ
#define DFU_BLOCKSZ         0x80
#endif
/* 32 bit DFU bootkey value */
#ifndef DFU_BOOTKEY
#define DFU_BOOTKEY         0x157F32D4
#endif
/* DFU bootkey address. Top of the ram by default. _AUTO, _DISABLE or set address.
 * May be enabled internally. */
#ifndef DFU_BOOTKEY_ADDR
#define DFU_BOOTKEY_ADDR    _AUTO
#endif
/* DFU bootstrap port/pin settings. Set GPIOx or _DISABLE */
#ifndef DFU_BOOTSTRAP_GPIO
#define DFU_BOOTSTRAP_GPIO  GPIOA
#endif
#ifndef DFU_BOOTSTRAP_PIN
#define DFU_BOOTSTRAP_PIN   1
#endif
/* Active bootstrap pin logic level. _HIGH, _LOW */
#ifndef DFU_BOOTSTRAP_LEVEL
#define DFU_BOOTSTRAP_LEVEL _LOW
#endif
/* Pullup or pulldown settings for the bootstrap pin _AUTO, _DISABLE, _HIGH, _LOW */
#ifndef DFU_BOOTSTRAP_PULL
#define DFU_BOOTSTRAP_PULL  _AUTO
#endif
/* Double reset waiting time in mS. _DISABLE or time in mS */
#ifndef DFU_DBLRESET_MS
#define DFU_DBLRESET_MS     300
#endif
/* User application address. _AUTO or page aligned address.
 * for _AUTO check __app_start address in output linker map file*/
#ifndef DFU_APP_START
#define DFU_APP_START       _AUTO
#endif
/* User application size. _AUTO or required size in bytes. */
#ifndef DFU_APP_SIZE
#define DFU_APP_SIZE        _AUTO
#endif
/* Microsoft WCID allows automatic driver (WinUSB) installation on device
 * connection. Use _ENABLE to make your device likeable by Windows. */
#ifndef DFU_WCID
#define DFU_WCID _DISABLE
#endif
/* Cipher to use. set _DISABLE or choose from implemented ciphers */
#define DFU_CIPHER          _DISABLE

#endif //BOOTLOADER_CONFIG
