# MSP430 LaunchPad Games

> University project developed in C for the **MSP-EXP430FR6989 LaunchPad**, demonstrating low-level peripheral control and interrupt handling.

## Overview
This project explores Computer Architecture concepts by implementing a dual-game system directly on an embedded microcontroller. Using **Code Composer Studio (CCS)**, the software interacts directly with the board's hardware to manage input/output without an operating system. It features a main menu selection system that allows the user to switch between a classic **Hangman** game and a competitive **Blind Timer** challenge.

## Key Features
* **Dual Game Modes:**
    * **Hangman:** Players guess words using an external keypad. The LCD updates to show the word progress and the stick figure upon failure.
    * **Blind Timer:** A precision game where two players must stop a hidden timer as close to 10 seconds as possible. The system calculates the time difference and awards points based on accuracy.
* **Hardware Interrupts:** Utilizes ISRs (Interrupt Service Routines) to handle button presses and keypad inputs efficiently without blocking the CPU.
* **LCD Control:** Custom driver implementation to manage the on-board segment LCD, displaying text, scores, and scrolling messages.
* **Peripheral Management:** Direct manipulation of General Purpose I/O (GPIO) for buttons/LEDs and Timer_A for precise time counting.

## Tech Stack
* **Language:** Embedded C
* **Hardware:** Texas Instruments MSP-EXP430FR6989 LaunchPad
* **IDE:** Code Composer Studio (CCS)
* **Libraries:** TI DriverLib (Board Support Package)

## System Requirements
**Note:** This project is designed to run on specific embedded hardware. Therefore, standard execution instructions are not provided, as the code cannot be run on a general-purpose PC without the microcontroller.

To build and deploy this software, the following components are required:

* **Hardware:** Texas Instruments **MSP-EXP430FR6989 LaunchPad** Development Kit.
* **Software:** Code Composer Studio (CCS) or a compatible MSP430 toolchain.
* **Input:** Connection to a PC for keyboard input (via UART/Console).

## Authors and Collaboration
This project was developed as a team effort for the **ESTRUCTURA DE COMPUTADORES** course.

* **Cameron Sánchez** - https://github.com/cameronsanchezb
* **Carlos Doval** - https://github.com/cakedov3-svg

---
Licensed under the [MIT License](LICENSE).