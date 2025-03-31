# Traffic Lights Simulation using ESP32 and FreeRTOS

## Overview

This embedded project simulates a traffic light system using an ESP32 microcontroller and FreeRTOS. It controls two sets of traffic lights for perpendicular roads and includes a button to influence light timing simulating a cross walk button. The system ensures an alternating flow of traffic with proper transitions between red, yellow, and green signals.

## Features

- Controls two sets of traffic lights (North-South and East-West directions).
- Uses FreeRTOS for handling timing and transitions.
- Implements a button input to modify the timing of the green light.
- Simulates realistic traffic light behavior with transition delays.

## Hardware Requirements

- **ESP32 Development Board**
- **LEDs** (For Red, Yellow, and Green signals for both directions)
- **Resistors** (Appropriate values for LEDs)
- **Push Button** (For pedestrian or traffic influence)
- **Wiring Connections:**
  - **North-South Traffic Light:**
    - Red → GPIO 19
    - Yellow → GPIO 18
    - Green → GPIO 5
  - **East-West Traffic Light:**
    - Red → GPIO 25
    - Yellow → GPIO 26
    - Green → GPIO 27
  - **Button:**
    - Input → GPIO 0

## Software Components

### 1. `main.c`

- Initializes GPIO for traffic lights and button.
- Implements functions to control light transitions.
- Uses FreeRTOS tasks and delays for timing control.
- Manages the state of the lights to ensure proper traffic flow.

### 2. Functions:

- **`setup_button()`**: Configures the button as an input.
- **`setup_traffic_light()`**: Configures LEDs as output and initializes them.
- **`change_to_green()`**: Handles transition from red to green with an optional button influence.
- **`change_to_red()`**: Manages transition from green to red through yellow.

## Expected Behavior

- The North-South direction starts with a green light while East-West is red.
- After the green cycle completes, the light turns yellow, then red.
- The East-West direction then turns green, following the same cycle.
- If the button is pressed, the green light duration is extended (simulating pedestrian crossing influence).

