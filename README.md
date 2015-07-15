# Draken
Firmware, profiles and documentation for the Draken 3D Printer.  Official Draken product info, docs and forums are at http://3dfacture.com/

## `firmware/`
This directory contains the source code for the Draken controller.  It is intended to be uploaded as an Arduino sketch, using the 1.5.8 version of the Arduino IDE, with support added for the STM32F103XX cortex-m3 arm cpu.  See https://github.com/MakerLabMe/STM32_Arduino_Cores for the files and instructions on how to add this support to an existing Arduino IDE install.

## `CWH/configs/`
The Draken has 8 projector mounting positions, each coorelating to a different X,Y resolution setting.  So this essentially results in 8 different "printers" in the CWH configuration system.

Below are the 8 different resolutions currently configured, mapped to the projector mounting slot, where 1 == top most, and 8 == bottom most.

|Postion|XY Resolution|
|:-----:|:-----------:|
|1|37µm|
|2|43µm|
|3|50µm|
|4|61µm|
|5|70µm|
|6|75µm|
|7|82µm|
|8|90µm|

Currently, all the `*.slicing` files are identical, as there is a bug in CWH that will only open a `*.slicing` file that matches the `*.machine` name specified in the `*.printer` file.

When this bug is fixed (CWH issue #46: https://goo.gl/CNhZd4), then we should be able to revert to using a single `*.slicing` file.
