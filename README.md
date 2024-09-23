# CalcOS v1.0 - The First Release of CalcOS

**CalcOS v1.0** is the first release of the operating system for ESP32-based scientific calculators. This version introduces the core functionality, offering both a traditional scientific calculator mode and an app-based interface that allows users to access additional tools such as **ChatGPT**, unit converters, prime checkers, and more.

## Features in CalcOS v1.0

### 1. Advanced Scientific Calculator
CalcOS v1.0 includes a fully functional scientific calculator with support for:
- **Basic arithmetic operations**: addition, subtraction, multiplication, and division.
- **Advanced operations**: trigonometric functions (sin, cos, tan), logarithms, exponentials, square roots, and factorials.
- **Memory functions**: store and recall values.
- **Parentheses**: for handling order of operations.

### 2. App Mode
In addition to the calculator, CalcOS v1.0 provides an app interface where users can access a range of utilities:

- **ChatGPT**: Ask questions and receive intelligent answers via OpenAI's GPT model. Ideal for educational support and complex explanations.
- **Unit Converter**: Convert between various units of length, weight, volume, and temperature.
- **Prime Checker**: Input a number and check if it is prime.
  
More apps will be added in future updates, including matrix calculators, currency converters, and advanced math tools.

### 3. Simple User Interface
The OS has a clean, menu-based interface accessible through a 128x64 OLED display. The keypad is used to navigate between the calculator mode and different apps.

### 4. Power-Saving Standby Mode
To conserve battery power, CalcOS v1.0 automatically enters standby mode after 5 minutes of inactivity. Users can wake the device by pressing any key.

## Getting Started with CalcOS v1.0

### Requirements
To run CalcOS v1.0, you'll need the following hardware:
- **ESP32 Dev Kit**: The main microcontroller unit with Wi-Fi capabilities.
- **128x64 OLED Display (SSD1306)**: Used for the interface.
- **4x4 or 5x4 Matrix Keypad**: For input and menu navigation.
- **Li-Po Battery (3.7V)**: For powering the device.
- **TP4056 Charging Module**: For recharging the battery.
  
### Installation Guide

1. **Clone the Repository**
   Clone the CalcOS repository to your local machine using the following command:
   ```bash
   git clone https://github.com/GOLUPO/CalcOS.git
   cd CalcOS
