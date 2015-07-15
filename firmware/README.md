# Firmware

The Draken firmware is a combination of code for Sprinter, grbl and marlin, according to the comments in `Sprinter.ino`:

```
/*
  This firmware is a mashup between Sprinter, grbl and parts from marlin.
  (https://github.com/kliment/Sprinter)

  Changes by Doppler Michael (midopple)

  Planner is from Simen Svale Skogsrud
  https://github.com/simen/grbl

  Parts of Marlin Firmware from ErikZalm
  https://github.com/ErikZalm/Marlin-non-gen6
*/
```

Read more about GCodes:

* [Descriptions of GCodes](http://linuxcnc.org/handbook/gcode/g-code.html)
* [Reprap GCodes](http://objects.reprap.org/wiki/Mendel_User_Manual:_RepRapGCodes)

## How to update the firmware on the Draken

### Windows
*_Copy from Forum post_*
### OS X
1. Get the various files you will need:
   * Draken Arduino 1.5.8 IDE for OS X: https://drive.google.com/file/d/0ByK3W2c482S4RWF2T3ktUF9hRzQ/view?usp=sharing
   * Silicon Labs USB-UART driver for OS X: http://www.silabs.com/Support%20Documents/Software/Mac_OSX_VCP_Driver.zip
   * Firmware sources for the Draken from one of the following places:
      - https://github.com/sbryan/Draken/firmware/
      - https://drive.google.com/file/d/0ByK3W2c482S4cnh4aUJ1Z2ViR1k/view?usp=sharing

   **NOTE**: For the rest of these instructions, we will assume all files have been saved in your `~/Downloads/` directory


2. Install the Silicon Labs USB-UART driver

```bash
$ cd ~/Downloads/
$ unzip Mac_OSX_VCP_Driver.zip
#Archive:  Mac_OSX_VCP_Driver.zip
#  inflating: SiLabsUSBDriverDisk.dmg
$ hdiutil attach ./SiLabsUSBDriverDisk.dmg
#/dev/disk2                /Volumes/Silicon Labs VCP Driver Install Disk
$ open /Volumes/Silicon\ Labs\ VCP\ Driver\ Install\ Disk/Silicon\ Labs\ VCP\ Driver.pkg
# The following screenshot shows the SiLabs USB to UART driver installer
```

|<img src='../misc/SiLabsUSBtoUART-installer.png' width=620 height=438>|
|:--------------------------:
|Click the <button>**Continue**</button> and complete the driver installation|

3. Install the Draken Arduino 1.5.8 IDE
4. Start the Draken Arduino 1.5.8 IDE
5. Check Board and Port settings
6. Open the Draken firmware sketch
7. Verify the firmware
8. Upload the firmware
9. Boot up the Draken and confirm it works

### Linux
*_TODO_*


