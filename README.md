# IoT-Based Multi-Sensor Gas Leakage Monitoring & Automatic Ventilation System

**University:** Daffodil International University  
**Department:** Computer Science and Engineering  
**Course:** Embedded Systems and IoT Project

## 📝 Abstract
This project is an IoT-enabled safety system designed to detect gas leakage (LPG, Methane, Smoke) in residential and industrial environments using the **ESP32 DevKit V1**. The system utilizes **three MQ2 gas sensors** placed at different heights (ceiling, stove level, ventilation outlet) to ensure accurate detection. Upon detecting gas levels above calibrated thresholds, the system triggers a local alarm (Buzzer + Red LED), automatically activates an **exhaust fan** via a relay, and sends real-time alerts (Push Notifications + Email) to a smartphone via the **Blynk IoT Platform**.

## ✨ Key Features
* **Multi-Point Detection:** Uses 3 calibrated MQ2 sensors for different zones (Source, Ceiling, Vent).
* **Automatic Ventilation:** Active mitigation system that turns on an exhaust fan immediately when a leak is detected.
* **IoT Connectivity:** Real-time monitoring dashboard and remote alerts using the Blynk Mobile App.
* **Dual Alert System:** * **Local:** LCD Display (16x2 I2C), Buzzer, and Status LEDs.
    * **Remote:** Push notifications and automated emails.

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP32 DevKit V1
* **Sensors:** 3x MQ2 Gas Sensors
* **Actuators:**
    * Relay Module (SPD-05VDC-SLC)
    * DC Ventilation Fan (12V)
    * Piezo Buzzer
* **Display:** 16x2 LCD with I2C Interface
* **Indicators:** Red & Green LEDs

## 🔌 Pin Configuration
| Component       | ESP32 GPIO Pin | Description |
|----------------|----------------|-------------|
| **MQ2 Sensor 1**| GPIO 39 (VN)   | Ceiling Level (Threshold: 1400) |
| **MQ2 Sensor 2**| GPIO 36 (VP)   | Stove Height (Threshold: 350)   |
| **MQ2 Sensor 3**| GPIO 34        | Vent Outlet (Threshold: 1600)   |
| **Relay (Fan)** | GPIO 18        | Active LOW trigger |
| **Buzzer** | GPIO 4         | Alarm Output |
| **Green LED** | GPIO 15        | Safe Status Indicator |
| **Red LED** | GPIO 2         | Danger Status Indicator |
| **I2C LCD** | GPIO 21 (SDA), GPIO 22 (SCL) | System Display |

## ⚙️ Working Principle
1. **Monitoring:** The ESP32 continuously reads analog values from all three sensors.
2. **Analysis:** The system compares readings against custom thresholds calibrated for each sensor's location:
   * Sensor 1 (Ceiling): > 1400
   * Sensor 2 (Source/Stove): > 350
   * Sensor 3 (Vent): > 1600
3. **Trigger:** If *any* sensor exceeds its threshold:
   * **Visual/Audio:** Red LED and Buzzer turn ON.
   * **Action:** Relay switches LOW to activate the Exhaust Fan.
   * **IoT:** Blynk sends a "Gas Leak Detected" notification and Email.
   * **Display:** LCD updates to show "Warning: Gas Detected".
4. **Safety:** Once levels return to normal, the system resets to Green LED and "All Normal" status.

## 📊 Results & Screenshots
*(Place your images in an `img` folder and reference them here)*

![System Prototype](img/prototype_photo.jpg)
*Figure: Real implementation of the monitoring unit.*

![Blynk Dashboard](img/blynk_dashboard.jpg)
*Figure: Mobile dashboard showing real-time PPM levels and fan status.*

## 👥 Project Team
* **Showrav Das** (ID: 221-15-5425)
* **Adnan Rahman Sayeem** (ID: 221-15-5505)
* **Niloy Biswas** (ID: 221-15-5894)
* **Shahnewaz Saeem** (ID: 221-15-5442)
* **Pronob Chandra Sarkar** (ID: 221-15-4840)

**Supervised By:** Indrojit Sarkar  
Lecturer, Department of CSE  
Daffodil International University

---
*Created: August 2025*