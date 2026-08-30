# Simon Says

A Simon Says memory game built with Arduino using LEDs, push buttons, and a buzzer.

The game generates a random sequence of colors that becomes longer after each successful round. The player must reproduce it correctly using the corresponding buttons.

## Features

- Four LEDs and push buttons
- Different buzzer tone for each color
- Random and progressively longer sequences
- Time limit between button presses
- Detection of incorrect or extra inputs
- Visual and sound feedback
- High score tracking
- Victory and defeat effects

## What I Learned

This project helped me practice:

- Working with arrays to store and compare sequences.
- Generating random values with `random()`.
- Using `tone()` and `noTone()` with a buzzer.
- Working with musical notes and frequencies.
- Reading and validating button inputs.
- Managing time limits.
- Organizing larger programs using functions.

## Components

- Arduino Uno
- 4 LEDs
- 4 push buttons
- 4 resistors
- Buzzer
- Breadboard
- Jumper wires

## Pin Configuration

| Component | Arduino Pin |
|---|---:|
| Yellow LED | 4 |
| Green LED | 5 |
| Red LED | 6 |
| Blue LED | 7 |
| Yellow Button | 8 |
| Green Button | 9 |
| Red Button | 10 |
| Blue Button | 11 |
| Buzzer | 12 |

## How It Works

Each round adds a new random color to the sequence.

The Arduino shows the complete sequence using the LEDs and buzzer. The player must then reproduce it using the buttons.

The game ends if the player presses the wrong button, adds an extra input, or takes too long.

A new high score triggers a victory melody.

## Demo Video

▶️ [Watch Simon Says on YouTube](https://youtube.com/shorts/HR4_xqF4TI4)

## Code

`Simon_Says.ino`
