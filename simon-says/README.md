# Simon Says

A Simon Says memory game built with Arduino using LEDs, push buttons, and a buzzer.

The game generates an increasingly long random sequence of colors. The player must reproduce the sequence correctly using the corresponding buttons.

## Features

- Four colored LEDs: yellow, green, red, and blue
- Four push buttons for player input
- Different buzzer tone for each color
- Randomly generated sequences
- Increasing difficulty after each successful round
- Maximum time between button presses
- Detection of incorrect or extra button presses
- Visual and sound feedback when pressing a button
- Defeat light and sound effect
- High score tracking
- Victory melody when a new high score is achieved

## Components

- Arduino Uno
- 4 LEDs
- 4 push buttons
- 4 LED resistors
- 1 buzzer
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

At the beginning of each round, the game adds a new random color to the sequence.

The complete sequence is then shown to the player using the LEDs and their corresponding buzzer tones.

The player must reproduce the sequence using the four buttons. Each button press activates its corresponding LED and sound.

If the player enters the complete sequence correctly, the game advances to the next round and adds another color.

The game ends if the player:

- Presses an incorrect button
- Presses an extra button
- Takes too long between button presses

After a defeat, the game displays the round reached and the current high score through the Serial Monitor.

If a new high score is achieved, a victory melody is played.

## Demo

A demonstration video of the project is included in this folder.

## Code

The Arduino source code is available in:

`Simon_Says.ino`
