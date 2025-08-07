# RTOS-Based Embedded UART Control System 

## Overview
An embedded application built with FreeRTOS that demonstrates task scheduling, UART command handling, in-application firmware update, and temperature monitoring using internal peripherals. The system runs entirely on a microcontroller, communicating with a PC via UART, without requiring a full hardware prototype.

## Features
- **RTOS-based task management** using FreeRTOS
- **UART CLI**: Control LED via serial commands
- **Temperature monitoring**: Periodic on-chip temperature reading using ADC
- **Firmware update**: Receive and write new firmware via UART (with DMA)

## Core Concepts
- Real-Time Scheduling with FreeRTOS
- Task separation: CLI handling, sensor monitoring, firmware receiving
- UART RX via DMA + IDLE interrupt detection
- Internal temperature sensor reading via ADC
- Context switching, delay-based scheduling
- Flash memory erase and program routines
- Minimal overhead design (no HAL, no external dependencies)

## How It Works
1. **Startup**: Tasks are initialized via FreeRTOS.
2. **CLI over UART**:
   - `led on` / `led off`: Toggle onboard LED
   - `update`: Enter firmware update mode
3. **Temperature Task**:
   - Runs every 1s
   - Uses ADC to read internal temperature sensor
   - Sends value via UART
4. **Firmware update**:
   - DMA receives firmware data via UART
   - MCU erases flash and writes new firmware
   - MCU resets after update
