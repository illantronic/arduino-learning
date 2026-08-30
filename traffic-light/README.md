# Arduino Traffic Light

Traffic light project built with Arduino to practice LED control, serial communication, program states, and non-blocking timing using `millis()`.

## Features

The traffic light includes several operating modes:

- **Normal mode:** standard red, green, and yellow traffic light sequence.
- **Blinking yellow mode:** yellow LED flashes continuously.
- **Simple manual mode:** manually select which LED is active.
- **Advanced manual mode:** independently control each LED.
  - Turn LEDs on and off.
  - Make individual LEDs blink.
  - Combine different LED states.
  - Switch between fixed and blinking states.

## What I Learned

This project helped me practice:

- Digital outputs with `digitalWrite()`.
- Serial communication with `Serial`.
- Functions.
- Boolean variables and program states.
- ASCII character handling.
- Using `millis()` instead of `delay()`.
- Running multiple blinking LEDs without blocking the program.

## Hardware

- Arduino
- Red LED
- Yellow LED
- Green LED
- Resistors
- Breadboard
- Jumper wires

## Demo Videos

See the different operating modes of the project in action:

### 🚦 Normal Mode

The traffic light automatically follows the standard red, green, and yellow sequence.

▶️ [Watch Normal Mode on YouTube](https://youtube.com/shorts/CWuzXLMFZGA)



### 🎛️ Simple Manual Mode

Manually select which LED is active.

▶️ [Watch Simple Manual Mode on YouTube](https://youtube.com/shorts/1j9U4bRwd88)

### ⚙️ Advanced Manual Mode

Independently control each LED, including fixed and blinking states.

▶️ [Watch Advanced Manual Mode on YouTube](https://youtube.com/shorts/W3grj5daBjs)
