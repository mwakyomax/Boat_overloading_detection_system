🚤 Boat Load Monitoring System

This project demonstrates two versions of a boat load monitoring system using Arduino:

Offboat Version – Basic weight monitoring using HX711 load cell and LCD, placed on the ground before boarding.

Onboat Version – Advanced system with buzzer alarm and GSM SMS alert, embedded on the door of the boat for final safety verification.

📂 Project Structure
final project/
│
├── offboat/       # Basic weight monitoring before boarding
│   ├── offboat.ino
│   └── README.md (optional)
│
├── onboat/        # Advanced version with buzzer and GSM SMS alert on boat door
│   ├── onboat.ino
│   └── README.md (optional)
📝 Prototype Workflow

Passenger arrives at the reception

Receptionist directs the passenger to the offboat system

Offboat system (on the ground)

Measures passenger’s weight

Displays weight and Status: SAFE or !! OVERLOAD !!

Passenger boards the boat

Passes through the onboat system (embedded on the door of the boat)

Onboat system (at the boat door)

Measures total boat load in real-time

If total weight exceeds safe limit:

LCD shows !! OVERLOAD !!

Buzzer alarm sounds

SMS alert is sent to the responsible personnel

This ensures double safety checks: before boarding and on the boat door.

1️⃣ Offboat Version

Arduino + HX711 + 16x2 LCD

Description

Measures passenger/boat load weight on the ground before boarding

Displays current weight on a 16x2 LCD

Shows Status: SAFE or !! OVERLOAD !! if weight exceeds 100kg

Features

Real-time weight monitoring

Overload detection display

Automatic scale taring

Simple start button

Hardware Components

Arduino Uno/Nano

HX711 Load Cell Module

Load Cell Sensor

16x2 LCD Display

Push Button

2️⃣ Onboat Version

Arduino + HX711 + 16x2 LCD + Buzzer + GSM Module

Description

Installed on the door of the boat for final safety check

Measures total boat weight in real-time

Buzzer alarm and SMS alert notify of overload

Features

Real-time total load monitoring

Overload detection system

Audible buzzer alarm

SMS alert notification

Automatic scale taring

Simple start button

Hardware Components

Arduino Uno/Nano

HX711 Load Cell Module

Load Cell Sensor

16x2 LCD Display

Push Button

Piezo Buzzer

GSM Module (SIM800L)

📌 Pin Configuration

Shared Components (LCD & HX711)

Component	Arduino Pin
LCD RS	7
LCD EN	6
LCD D4	5
LCD D5	4
LCD D6	3
LCD D7	2
HX711 DT	A0
HX711 SCK	A1
Button	8 (INPUT_PULLUP)

Onboat Only

Component	Arduino Pin
Buzzer	11
GSM TX	10
GSM RX	9
📂 How to Use the Prototype

Passenger meets the receptionist

Passenger goes to the offboat system for initial weight check

Receptionist verifies the Status: SAFE

Passenger boards the boat

Passenger passes through onboat system at the boat door

Onboat system ensures total load safety: triggers alarm and SMS if overloaded

This workflow ensures passenger and cargo safety before and during boarding.

👨‍💻 Author

Elieza Mwakyoma
Embedded Systems & IoT Enthusiast
Founder – Mwakyoma Online Market
