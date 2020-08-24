﻿[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Harmony 3 Driver and System Service application examples for PIC32MZ W1 family

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices.  Refer to the following links for more information.

- [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)
- [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the MPLAB® Harmony 3 Driver and System Service application examples for PIC32MZ W1 family

- [Release Notes](release_notes.md)
- [MPLAB® Harmony License](mplab_harmony_license.md)

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

## Contents Summary

| Folder     | Description                                    |
| ---        | ---                                            |
| apps       | Driver and System Service example applications |
| docs       | Applications help documentation                |

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more driver and system services.

| Name | Description|
|:---------|:-----------|
|[I2C driver asynchronous - I2C EEPROM](apps/driver/i2c/async/i2c_eeprom/readme.md) | This example application shows how to use the I2C driver in asynchronous mode to perform operations on the EEPROM |
|[I2C driver synchronous - I2C EEPROM](apps/driver/i2c/sync/i2c_eeprom/readme.md) | This example application shows how to use the I2C driver in synchronous mode to perform operations on the EEPROM |
|[SPI Driver asynchronous - Self loopback multi client](apps/driver/spi/async/spi_self_loopback_multi_client/readme.md) | This example demonstrates how to use the SPI driver in asynchronous mode to achieve self-loop back between multiple clients |
|[SPI Driver synchronous - Self loopback multi client](apps/driver/spi/sync/spi_self_loopback_multi_client/readme.md) | This example demonstrates how to use the SPI driver in synchronous mode to achieve self-loop back between multiple clients in RTOS environment |
|[USART driver asynchronous - USART echo](apps/driver/usart/async/usart_echo/readme.md) | This example echoes the received characters over the console using the USART driver in asynchronous mode |
|[USART driver synchronous - USART echo](apps/driver/usart/sync/usart_echo/readme.md) | This example echoes the received characters over the console using the USART driver in synchronous mode |
|[FAT filesystem using NVM Media](apps/fs/nvm_fat/readme.md) | This application shows an example of implementing a FAT disk in the device internal Flash memory |
|[FAT filesystem using SDSPI Media](apps/fs/sdspi_fat/readme.md) | This application shows an example of using the MPLAB Harmony File System to access and modify the contents of a SD card using the SDSPI driver and the SPI PLIB |
|[FAT filesystem using SST26 Media](apps/fs/spi_flash_fat/readme.md) | This application shows an example of using the FAT File System to access SST26 flash media using SPI protocol |
|[FreeRTOS basic](apps/rtos/freertos/basic_freertos/readme.md) | This example application blinks an LED to show the FreeRTOS threads that are running and to indicate status |
|[Console Debug System Service using UART](apps/system/console_debug/sys_console_debug_uart_read_write/readme.md) | This example application demonstrates the UART based console and debug system service |
|[Console Debug System Service using USB](apps/system/console_debug/sys_console_debug_usb_read_write/readme.md) | This example application demonstrates the USB based console and debug system service |
|[Time System Service multi-client](apps/system/time/sys_time_multiclient/readme.md) | This example application demonstrates the multi-client system timer functionality |
|||

____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1/blob/master/mplab_harmony_license.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg)](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg)]()

____

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1.svg?style=social)]()
