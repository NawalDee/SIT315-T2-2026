# Smart Security Alert System

## Overview
This project demonstrates an interrupt-driven embedded system using Pin Change Interrupts and Timer1 Interrupt.

## Hardware
- Arduino Uno
- 3 Push Buttons
- Red LED
- Green LED
- Buzzer

## Features
- Pin Change Interrupts for buttons
- Timer1 Interrupt every second
- State Machine
- Sense-Think-Act logic

## States
- READY
- MONITORING
- WARNING
- EMERGENCY

## How to Use
1. Press Button 1 to start monitoring.
2. Wait 5 seconds to enter WARNING.
3. Press Button 3 to activate EMERGENCY.
4. Press Button 2 to reset the system.
