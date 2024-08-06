## Overview

This code implements a basic Snake game on a PIC microcontroller, utilizing an 8x8 LED matrix for display and push buttons for directional control. 

## Hardware Requirements

1. **PIC Microcontroller**: The code is designed for a PIC microcontroller. The specific model should be compatible with the MPLAB XC8 compiler and support the necessary I/O ports.
2. **8x8 LED Matrix**: For displaying the snake and food.
3. **Push Buttons (4)**: For controlling the snake's direction (UP, DOWN, LEFT, RIGHT).
4. **Resistors**: For current limiting on the LED matrix.
5. **Power Supply**: As required by the PIC microcontroller.
6. **Crystal Oscillator**: 20 MHz crystal oscillator for the PIC microcontroller.
7. **Breadboard and Jumper Wires**: For prototyping and connecting the components.

## Software Requirements

1. **MPLAB X IDE**: For writing and compiling the code.
2. **MPLAB XC8 Compiler**: For compiling the C code for the PIC microcontroller.
3. **PICkit**: For programming the microcontroller.

## Circuit Diagram

The following connections are required:

1. **LED Matrix Connections**:
   - Connect the rows of the LED matrix to PORTB (RB0 to RB7).
   - Connect the columns of the LED matrix to PORTD (RD0 to RD7).

2. **Push Buttons Connections**:
   - Connect four push buttons to PORTC (RC0 to RC3).
   - Configure the buttons to pull-up or pull-down as per your design.

3. **Power Supply**:
   - Connect the power supply to the VDD and VSS pins of the PIC microcontroller.
   - Connect the crystal oscillator to the appropriate pins of the PIC microcontroller.

## Code Description

### Configuration Bits

The configuration bits are set to:
- Use a High-Speed (HS) oscillator.
- Disable the Watchdog Timer (WDT).
- Disable the Power-up Timer (PWRT).
- Enable Brown-out Reset (BOR).
- Disable Low-Voltage Programming (LVP).
- Disable Data EEPROM Memory Code Protection.
- Disable Flash Program Memory Write Protection.
- Disable Flash Program Memory Code Protection.

### Definitions

- `_XTAL_FREQ`: Sets the crystal frequency to 20 MHz.
- `ROWS` and `COLS`: Define the dimensions of the LED matrix (8x8).
- `UP`, `DOWN`, `LEFT`, `RIGHT`: Define direction constants.

### Function Prototypes

Declarations for initialization, display refresh, snake movement, food generation, delay, collision checking, game over handling, and button checking functions.

### Global Variables

- `snake[ROWS][COLS]`: A matrix representing the snake's position.
- `direction`: The current direction of the snake.
- `food_x`, `food_y`: Coordinates of the food.
- `snake_length`: The length of the snake.

### `main` Function

1. **Initialization**: Calls `init()` to set up the microcontroller and initialize the snake.
2. **Generate Initial Food**: Calls `generate_food()` to place the first piece of food.
3. **Main Game Loop**:
   - Checks button states to update the snake's direction.
   - Moves the snake based on the current direction.
   - Checks for collisions.
   - Refreshes the display.
   - Delays to control the snake's speed.

### `init` Function

Configures the microcontroller ports, initializes the snake's position, and clears the snake matrix.

### `refresh_display` Function

Refreshes the LED matrix by activating the appropriate rows and columns to display the current state of the snake and food.

### `move_snake` Function

Updates the snake's position according to the current direction, handles snake growth when food is eaten, and checks for collisions with itself.

### `generate_food` Function

Randomly places a new piece of food on the LED grid in a position not occupied by the snake.

### `check_collision` Function

Checks if the snake has collided with itself by counting the number of head segments (should be exactly one).

### `game_over` Function

Resets the game when a collision occurs, resets the snake's length and position, and indicates game over by lighting all LEDs.

### `check_buttons` Function

Reads the states of the input buttons to update the snake's direction, ensuring the snake cannot reverse direction directly.

### `delay_ms` Function

Provides a millisecond delay using the microcontroller's delay functions.

## Compilation and Programming

1. Open MPLAB X IDE and create a new project for the PIC microcontroller.
2. Copy the provided code into the main C file of the project.
3. Configure the project to use the MPLAB XC8 compiler.
4. Compile the project to generate the hex file.
5. Use a PICkit or another programmer to upload the hex file to the PIC microcontroller.

## Usage

1. Connect the hardware components as per the circuit diagram.
2. Power on the system.
3. The snake game will start automatically.
4. Use the push buttons to control the snake's direction.
5. The game will handle snake movement, food generation, and collisions.
6. When a collision occurs, the game will reset and start over.

## Troubleshooting

- Ensure all connections are secure and correct.
- Verify the power supply voltage is appropriate for the PIC microcontroller.
- Check the button connections and ensure they are functioning correctly.
- If the LED matrix does not display correctly, verify the connections to PORTB and PORTD.

## Conclusion

This project demonstrates a simple implementation of a Snake game using a PIC microcontroller, an 8x8 LED matrix, and push buttons. It covers fundamental concepts such as I/O port configuration, matrix display control, and basic game logic.
