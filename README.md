# LCD Display Driver for PIC16F877A

A C-based driver and interface library for controlling 16x2 LCD displays using the PIC16F877A microcontroller.

## Overview

This project provides a complete implementation for interfacing a 16x2 character LCD display with the PIC16F877A microcontroller. It includes initialization routines, display control functions, and example programs.

## Features

- 4-bit and 8-bit mode support
- Display initialization and control
- Character and string display functions
- Cursor control
- Clear display functionality
- Custom character support
- Example code and documentation

## Hardware Requirements

- PIC16F877A Microcontroller
- 16x2 LCD Display (HD44780 compatible)
- 4.7kΩ pull-up resistors
- 10kΩ potentiometer (for contrast adjustment)
- Power supply (5V)

## Pin Configuration

| LCD Pin | PIC16F877A Port |
|---------|-----------------|
| RS      | RA0             |
| RW      | RA1             |
| EN      | RA2             |
| D0-D3   | RB0-RB3 (4-bit) |
| D4-D7   | RB4-RB7 (8-bit) |
| VSS     | GND             |
| VCC     | +5V             |
| VEE     | GND (or pot)    |

## Getting Started

1. Connect the LCD display to PIC16F877A as per pin configuration
2. Include the header files in your project
3. Call `lcd_init()` to initialize the display
4. Use `lcd_putchar()` and `lcd_puts()` to display characters and strings

## Files

- `lcd.h` - LCD driver header file
- `lcd.c` - LCD driver implementation
- `main.c` - Example usage
- `configuration.h` - Configuration settings

## Usage Example

```c
#include "lcd.h"

void main(void) {
    lcd_init();           // Initialize LCD
    lcd_puts("Hello");    // Display text
    lcd_putchar('!');     // Display single character
    
    while(1) {
        // Your code here
    }
}
