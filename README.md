# 🤖 Smorphi QR Maze Solver

An autonomous navigation system for the **Smorphi modular robot** that combines **AI-based QR code detection** with **maze-solving using bottom IR sensors**. This hybrid logic system uses the HuskyLens AI camera to interpret QR codes and simple `if-else` logic to follow and recover from line-based paths.

---


---



###  Maze Solving Logic

| Left IR | Right IR | Action              |
|---------|----------|---------------------|
| 1       | 1        | Move Forward        |
| 1       | 0        | Turn Slightly Left  |
| 0       | 1        | Turn Slightly Right |
| 0       | 0        | Lost — Recover      |

###  QR Code Detection

The robot uses HuskyLens to scan QR codes placed in the maze. It reacts as follows:

| QR Label | Action               |
|----------|----------------------|
| `Start`  | Begin solving maze   |
| `Left`   | Make left turn       |
| `Right`  | Make right turn      |
| `Goal`   | Stop & finish        |

---

##  Code Structure

- `main_code.ino` – Core logic for scanning and solving
- `recoverLine()` – Searches for the line when lost
- `sensor_test.ino` – (Optional) Check IR values in Serial Monitor

---

##  Hardware Requirements

| Component      | Description                          |
|----------------|--------------------------------------|
| Smorphi Robot  | Modular robot with motor control     |
| HuskyLens      | AI Vision Sensor in QR mode          |
| IR Sensors     | Bottom-facing, module1 pins 0 and 4  |
| Arduino Board  | Compatible microcontroller            |
| Power Supply   | Rechargeable Li-ion battery pack 
| ESP32 DEV MODULE | Arduino Board for Smorphi

---

##  Setup Instructions

1. Mount 2 IR sensors facing downward.
2. Connect HuskyLens to pins **TX=16**, **RX=14** using SoftwareSerial.
3. In HuskyLens, switch to **QR Code Mode**.
4. Train and name QR codes as:
   - `Start`
   - `Left`
   - `Right`
   - `Goal`
5. Upload `main_code.ino` to your Smorphi board.
6. Place the robot at the start of the maze — it’s autonomous from here!

---




