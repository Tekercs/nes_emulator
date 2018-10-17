# Project scope and outline plan

## Overview
NES (Nintendo Entertainmnet System) is a gaming console released back in 1983. This innovation was the successor of the old arcade gameing systems which was widely used Since the '80. Nintendo with their system the goal was to bring the gaming experience to the homes. The new console was different compared to its predecessors, it was meant to connect to a TV for display purposes, instead of having predeployed games the console developed with a new cartridge based storage for the softwares, and two seperate easy to use innovative controllers.
This console was single handedly ressurected the dying gameing market due to it's cheap console and its supervised gaming library.
The aim of this project is to develop a software which makes the users able to run games on their PC which was developed for the NES home gameing console. The software's goal to emulate the system and it's components. These components are the following:

* CPU (MOS 6502)
* PPU (Picture Processing Unit)
* Cartridge mapping
* Memory

## Objectives

### Milestones

Key milestones of the project in order:

1. Implement the memory map of the system ( ~>1week)
2. CPU implementation (capability to execute all official 6502 opcodes) (~3week)
3. Basic cartridge mapper implementation (~1week)
4. PPU implementation and GUI for I/O purposes (~3-4 week)

Possible advanced features for future development beyond the previoulsy mentioned.
These features implementation will be done when the key milestones completed and also well tested and documented.

* Pixel perfect and properly synced CPU PPU emulation
* Online multiplayer support
* Additional mapper implementation
* Rapsbery Pi & Usb controller support

### Development plan

The project feature development will be deliverd with Incremental Development Model and Behavior driven testing.
The documentation phase of the project will be tightly coupled with development and carryed out simultaniously.

## Evaluation

The result software evaluation will be executed in multiple steps. With the Incremental development the aim is to reach and satisfy given evaluation stages. With each satisfied evaluation stage all the previoulsy completed stage must not be changed.

* Running 6502 assembly code and programs written with it.
* Running programs loaded in form the NES virtual cartdige format.
* Displaying sample text and minimal static images on the screen with the Help of the PPU
* Displaying minimal dynamic content
* Run and display minimal not complex NES games. (e.g. Donkey Kong)
* Run and display graphically more Complex games, involves at least one way of scrolling.
* Running most of the titles with pixel perfection and high cycle accuracy.

## Marking scheme

The project would follow the Software Development Based marking scheme as the project focus is on the actuall implementation of the NES emulator.


