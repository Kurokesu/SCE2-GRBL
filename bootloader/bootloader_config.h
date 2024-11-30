#ifndef BOOTLOADER_CONFIG
#define BOOTLOADER_CONFIG

/* Skip unwanted dfuDNLOAD_SYNC phase. Slightly improve speed, but doesn't meet DFU1.1 state diagram */
#define DFU_DNLOAD_NOSYNC   _DISABLE

/** Add extra DFU interface for EEPROM */
#define DFU_INTF_EEPROM     _DISABLE

/** Firmware can be uploaded from device */
#define DFU_CAN_UPLOAD      _ENABLE

/** Handle DFU_DETACH request in DFU mode. System reset will be issued. */
#define DFU_DETACH          _ENABLE

/** Whether application image is verified by a checksum algorithm */
#define DFU_VERIFY_CHECKSUM _DISABLE

/** Memory Readout Protection level **/
#define DFU_SEAL_LEVEL      0

/* USB VID */
#define DFU_VENDOR_ID       0x0483

/* USB PID */
#define DFU_DEVICE_ID       0xDF11

/* USB manufacturer string */
#define DFU_STR_MANUF       "Kurokesu"

/* USB product sting */
#define DFU_STR_PRODUCT     "SCE2-GRBL bootloader"

/* USB string for DFU configuration string descriptor. */
#define DFU_DSC_CONFIG      _ENABLE
#define DFU_STR_CONFIG      "SCE2-GRBL DFU"

/* USB string for DFU flash interface string descriptor. */
#define DFU_DSC_FLASH       _ENABLE
#define DFU_STR_FLASH       "Internal flash"

/* USB string for DFU EEPROM interface sreing descriptor */
#define DFU_DSC_EEPROM      _DISABLE

/* DFU properties */
#define DFU_POLL_TIMEOUT    20
#define DFU_DETACH_TIMEOUT  200
#define DFU_BLOCKSZ         0x80

/* 32 bit DFU bootkey value */
#define DFU_BOOTKEY         0x157F32D4

/* DFU bootkey address. Top of the ram by default. _AUTO, _DISABLE or set address.
 * May be enabled internally. */
#define DFU_BOOTKEY_ADDR    _AUTO

/* DFU bootstrap port/pin settings. Set GPIOx or _DISABLE */
#define DFU_BOOTSTRAP_GPIO  _DISABLE
#define DFU_BOOTSTRAP_PIN   1

/* Active bootstrap pin logic level. _HIGH, _LOW */
#define DFU_BOOTSTRAP_LEVEL _LOW

/* Pullup or pulldown settings for the bootstrap pin _AUTO, _DISABLE, _HIGH, _LOW */
#define DFU_BOOTSTRAP_PULL  _AUTO

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
