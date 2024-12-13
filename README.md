# Track-Mower
A conceptual grass mower equipped with tracks for enhanced mobility.

## Overview
The Track-Mower is built around the ESP D1 Mini microcontroller, which provides WiFi, Bluetooth, and BLE capabilities. Communication between the driver and the mower is established via Bluetooth. Commands are sent as single characters, with each character corresponding to a specific action the mower will execute for a predefined duration.

## Features
- **Microcontroller**: ESP D1 Mini with WiFi, Bluetooth, and BLE.
- **Command-based Control**: Simple single-character commands for predefined actions.
- **Bluetooth Communication**: Reliable connection between the mower and a smartphone.

## How to Use
To operate the Track-Mower:
1. Install the [Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) app on your Android device.
2. Pair your smartphone with the Track-Mower via Bluetooth.
3. Use the app to send commands to the mower.

## Command List
The following commands can be used to control the Track-Mower:

| Command | Action   | Duration  | Description                          |
|---------|----------|-----------|--------------------------------------|
| **F**   | Forward  | 1 second  | Moves the mower forward.             |
| **B**   | Backward | 1 second  | Moves the mower backward.            |
| **R**   | Right    | 0.5 second| Turns the mower to the right using both tracks. |
| **L**   | Left     | 0.5 second| Turns the mower to the left using both tracks.  |
| **M**   | Mower    | Gradual   | Spins up the blades gradually.       |

### Example Usage
To drive the mower forward for 2 seconds, turn left, and then start the blades:
```
F
F
L
M
```

## Future Improvements
Here are some ideas for future enhancements:
1. **Advanced Controller**: Develop a controller for precise real-time control of the Track-Mower.
2. **PCB Redesign**: Improve the PCB design to provide more stable current sensing.
3. **Code Optimization**: Refactor the codebase and port it to an RTOS for better performance and scalability.


