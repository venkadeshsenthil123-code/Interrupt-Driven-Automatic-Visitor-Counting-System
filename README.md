# Interrupt-Driven Automatic Visitor Counting System

An Interrupt-Driven Automatic Visitor Counting System developed using the **LPC2129 (ARM7) Microcontroller**. The system utilizes **External Interrupts (EINT0 & EINT1)** to detect people entering and exiting a room through IR sensors. The **Visitors Count** is updated in real time, enabling automatic room light control and live occupancy monitoring on a **20×4 LCD Display**.

---

# Project Overview

This project demonstrates the implementation of an interrupt-driven embedded system for monitoring room occupancy.

Two IR sensors are placed at the entry and exit points of the room.

- **IR Sensor 1** is connected to **External Interrupt 0 (EINT0)** and detects people entering the room.
- **IR Sensor 2** is connected to **External Interrupt 1 (EINT1)** and detects people exiting the room.

Whenever either sensor detects a person, the corresponding external interrupt is triggered immediately. This eliminates the need for continuous polling and allows the system to respond quickly while reducing CPU utilization.

The **Visitors Count** is continuously displayed on a **20×4 LCD**.

An **Indication LED** blinks whenever an entry or exit is detected.

A **Room Light LED** is automatically controlled based on the Visitors Count:

- **Visitors Count > 0 → Room Light ON**
- **Visitors Count = 0 → Room Light OFF**

The switch is pressed at a time both total entered and exited person count is shown in the LCD  and it will return back to the normal
person count.

---

# Features

- Interrupt-driven visitor counting
- Real-time Visitors Count display
- Automatic Room Light control
- Entry and Exit detection using IR Sensors
- Indication LED for entry/exit events
- Displays People Entered and People Exited using a Switch
- Automatically returns to Visitors 
- Efficient implementation with reduced CPU utilization

---

# Hardware Components

- LPC2129 Microcontroller
- 20×4 LCD Display
- 2 × IR Sensors
- Power Supply
- Room Light LED
- Connecting Wires
- Switch
- Indication LED


---

# Software Used

- Embedded C
- Keil uVision
- Flash Magic

---

# Working Principle

## Entry Detection

- IR Sensor 1 is connected to **External Interrupt 0 (EINT0)**.
- When a person enters the room, **EINT0** is triggered.
- The **Visitors Count** is incremented.
- The **People Entered** count is incremented.
- The Indication LED blinks like a (BUZZER).
- The LCD updates the Visitors Count.
- Whenever the count will atleast one the another led is ON.

---

## Exit Detection

- IR Sensor 2 is connected to **External Interrupt 1 (EINT1)**.
- When a person exits the room, **EINT1** is triggered.
- The **Visitors Count** is decremented.
- The **People Exited** count is incremented.
- The Indication LED blinks like a (BUZZER).
- The LCD updates the Visitors Count.
- Whenever the count will zero  the another led is OFF.

---

## Automatic Room Light Control

The Room Light LED operates automatically according to the Visitors Count.

| Visitors Count | Room Light |
|----------------|------------|
| Greater than 0 | ON |
| Equal to 0 | OFF |

---

## LCD Display

The **20×4 LCD** continuously displays the **Visitors Count**, representing the number of people currently present inside the room.

Example:

```text
visitor count  :1
Visitors Count :5
```

When the **Switch** is pressed, the LCD displays:

```text
People Entered : 18
People Exited  : 13
```
---

# Interrupt Configuration

| Interrupt | Connected Device | Function |
|-----------|------------------|----------|
| EINT0 | IR Sensor 1 | Detect Entry |
| EINT1 | IR Sensor 2 | Detect Exit |


#  Applications

- Offices
- Libraries
- Classrooms
- Laboratories
- Conference Rooms
- Shopping Malls
- Meeting Halls

---

#  Advantages

- Fast response using hardware interrupts
- Accurate room occupancy monitoring
- Automatic Room Light control
- Low CPU utilization
- Energy-efficient operation
- Reliable and real-time performance

---
