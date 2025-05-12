Car Black Box System using PIC18F Microcontroller
Overview
This project implements a Car Black Box (Vehicle Data Recorder) using a PIC18F microcontroller, which logs critical events such as sudden braking, collisions, or abnormal activity. The system interfaces with hardware components like push buttons (for input triggers), an LCD display (for status updates), and optionally sensors (e.g., vibration or temperature) to record events much like an aircraft black box.

Features
Event Recording: Logs key vehicle events like ignition on/off, brake press, collision alert, etc.

Real-time Display: Shows system status and recent events on a 16x2 LCD display.

Button Interface: Buttons simulate or capture user-triggered events (e.g., brake, ignition, crash alert).

Persistent Storage (optional): Can log data to EEPROM or external memory if required.

Timestamp (optional): Real-time clock can be added to timestamp each event.

Hardware Components
PIC18F Microcontroller (e.g., PIC18F4550 / PIC18F452)

16x2 LCD (connected in 4-bit or 8-bit mode)

Push Buttons (minimum 3–4: ignition, brake, crash alert, reset)

Power Supply (regulated 5V)

Optional: RTC module, EEPROM, sensors (vibration/acceleration)

Working Principle
Startup:

On power-up, the system initializes the LCD and waits for input.

Input Detection:

Pressing buttons triggers specific event types (e.g., brake, ignition, crash).

Each event is recorded with a message displayed on the LCD.

Display:

LCD shows either the latest event or a real-time status log.

Can include scrolling or multi-line updates.

Event Handling:

Each event may trigger a flag or counter (e.g., number of crashes, resets).

Events can be stored in memory for post-analysis.
