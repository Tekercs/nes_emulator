# Project scope and outline plan

## Overview

NES (Nintendo Entertainment System) is a gaming console released back in 1983. The NES was the successor of the old arcade gaming systems which had been widely used since the '80s. Nintendo's goal with their system was to bring the gaming experience into homes. The new console was different compared to its predecessors: it was connected to a TV for display purposes; instead of having predeployed games, the console developed a new cartridge-based storage for software; and included two separate easy to use innovative controllers.

This console was single-handedly resurrected the dying gaming market due to its cheap console and its supervised gaming library.

The aim of this project is to develop a software which makes the users able to run games on their PC which was developed for the NES home gaming console. The software's goal to emulate the system and its components. These components are the following:

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

Possible advanced features for future development beyond the previously mentioned.
These features implementation will be done when the key milestones completed and also well tested and documented.

* Pixel perfect and properly synced CPU PPU emulation
* Online multiplayer support
* Additional mapper implementation
* Raspberry Pi & USB controller support

### Development plan

The project feature development will be delivered with the Incremental Development Model and Behavior driven testing.
The documentation phase of the project will be tightly coupled with development and carried out simultaneously.

## Evaluation

The result software evaluation will be executed in multiple steps. With the Incremental development, the aim is to reach and satisfy given evaluation stages. With each satisfied evaluation stage, all the previously completed stage must not be changed.

* Running 6502 assembly code and programs written with it.
* Running programs loaded in form the NES virtual cartridge format.
* Displaying sample text and minimal static images on the screen with the Help of the PPU
* Displaying minimal dynamic content
* Run and display minimal not complex NES games. (e.g. Donkey Kong)
* Run and display graphically more Complex games, involves at least one way of scrolling.
* Running most of the titles with pixel perfection and high cycle accuracy.

## Marking scheme

The project would follow the Software Development Based marking scheme as the project focus is on the actual implementation of the NES emulator and to provide an accurate software-based reproduction of the original hardware. 


## Supervisor's comments

This is an ambitious and fun looking project. I am very jealous and wish I had time to do this! From speaking with Bence, I think that he has a solid grasp of what is involved in this project, and has identified sources of documentation and help should he get stuck or need more details of how the NES works.

The "Software Development Based" marking scheme is appropriate for this project.

The only problem with this plan is the lack of a detailed time breakdown including time for writing the report. Documentation of the system is included in the plan, but remember that a report also needs to be written! Based on the quality of the written English in this outline plan, I think some time should be put aside for drafting and getting feedback on the report as it is written would be beneficial. (I have edited the first paragraph of this plan to improve the English.)
