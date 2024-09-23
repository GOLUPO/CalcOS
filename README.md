# CalcOS - An Advanced Operating System for Scientific Calculators

**CalcOS** is a lightweight and advanced operating system designed for ESP32-based scientific calculators. It combines the functionalities of a traditional scientific calculator with an expandable ecosystem of apps, supporting advanced calculations, internet connectivity, and interactive modes like **ChatGPT**. This project aims to provide a powerful tool for students, teachers, and electronics enthusiasts to enhance productivity and learning.

## Key Features

- **Advanced Scientific Calculator**: Supports basic and advanced operations like trigonometry, logarithms, exponentials, etc.
- **Customizable Apps**: An internal "App Store" allows downloading new apps, system updates, and even creating custom apps.
- **ChatGPT Integration**: Uses OpenAI to answer questions, explain calculations, and provide suggestions.
- **Standby Mode**: Saves power when not in use.
- **Modern Interface**: OLED display to show menus, apps, and calculation results.
- **Wi-Fi Support**: Internet connectivity for apps like currency converter and system updates.

## Required Hardware

1. **ESP32 Dev Kit**: Microcontroller with built-in Wi-Fi and Bluetooth.
2. **128x64 OLED Display (SSD1306)**: To display the operating system interface.
3. **4x4 or 5x4 Matrix Keypad**: For input and navigation.
4. **Buzzer and LED Indicators**: For sound and visual feedback.
5. **3.7V Li-Po Battery** and **TP4056 Module**: For portable power and safe charging.

## Operating System Features

- **Calculator Mode**: Performs standard scientific calculations.
- **App Mode**: Access to a range of apps such as:
  - **Unit Converter**: Convert between various units of measurement.
  - **Currency Converter**: Up-to-date exchange rates via the internet.
  - **Prime Checker**: Check if a number is prime.
  - **Matrix Calculator**: Perform matrix operations.
  - **ChatGPT**: Intelligent responses via OpenAI API.
- **Internal App Store**: Allows downloading apps and system updates.
- **Standby Mode**: Reduces power consumption when inactive.

## Installation Guide

1. **Clone the Repository**
   ```bash
   git clone https://github.com/GOLUPO/CalcOS.git
   cd CalcOS
