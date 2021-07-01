---
parent: Harmony 3 driver and system service application examples for PIC32MZ W1 family
title: LittleFS filesystem using NVM Media 
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# LittleFS filesystem using NVM Media

This application shows an example of implementing a LittleFS  disk in the device internal Flash memory.

## Description

### File System Operations on NVM:

- Application places a LittleFS disk image in the internal Flash memory (NVM)

- During execution, the application first opens an existing file named **FILE.TXT** and performs following file system related operations:
    - **SYS_FS_FileStat**
    - **SYS_FS_FileSize**
    - **SYS_FS_FileSeek**
    - **SYS_FS_FileEOF**

- It tries to read the file and checks if string **"Data"** is present. If present it continues to next step or it fails the application

- Finally, the string **"Hello World"** is written to this file. The string is then read and compared with the string that was written to the file. If the string compare is successful, An LED indication is provided

### File system layer uses:

- Memory driver to communicate with underlying NVM media

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/core_apps_pic32mz_w1) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/fs/nvm_littlefs/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| pic32mz_w1_curiosity.X | MPLABX project for PIC32MZ W1 Curiosity Board |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| pic32mz_w1_curiosity.X | PIC32MZ W1 Curiosity Board |
|||

### Setting up PIC32MZ W1 Curiosity Board

- Connect micro USB cable to the 'USB Debug' connector(J302) on the board to the computer

## Running the Application

1. Build and program the application using its IDE
2. Press Switch to start the file operations 
3. The LED is turned ON when the File **FILE.TXT** has the app data **"Hello World"** written in it 

Refer to the following table for switch and LED name:

| Board | Switch name | LED Name |
| ----- | -------- | --------- |
|  PIC32MZ W1 Curiosity Board | SW200 | RED LED |
||||

## Generate LittleFS image and convert to C file to store in NVM
If you want to generate a LittleFS image to store in NVM, you can follow below steps:
1. Download the [prebuild](https://github.com/MicrochipTech/mklittlefs/tree/master/prebuild) mklittlefs tool
2. On Windows PC, unzip **i686-w64-mingw32-mklittlefs-1ee4877.zip** (If you are using other OS PC, you can unzip other prebuild tool)
3. Go to directory *i686-w64-mingw32-mklittlefs-1ee4877/mklittlefs/*
4. create directory *src_folder*
5. Copy the files or directory of the generated image  to the path *i686-w64-mingw32-mklittlefs-1ee4877/mklittlefs/src_folder*
6. Run command **mklittlefs.exe -c src_folder -d 5 -a -b 512 -p 16 -s 65536 lfs_image.img** (The image size is 64KB for this command)
7. lfs_imag.img is generated
8. Use [bin2c](https://www.segger.com/free-utilities/bin2c/) to convert lfs_image.img to C file
9. Replace the generated array variable to array **LFS_IMAGE** in \firmware\src\nvm_disk_images.c  


