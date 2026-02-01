
<img src="https://media.giphy.com/media/U3qYN8S0j3bpK/giphy.gif" width="100%" height="40px" style="object-fit: cover;" />


# 🌱 Soil Monitoring System for Improved Crop Yield
A modern **ESP32-powered Smart Irrigation System** with an interactive web dashboard.  

---

## 📌 Problem Statement

Traditional irrigation systems rely heavily on manual monitoring and fixed watering schedules.  
This often results in **water wastage, poor crop health, and lack of real-time soil condition awareness**.

Additionally, for students and beginners, **sensor cost, availability, and maintenance** become a challenge during project development and demonstrations.

---

## 💡 Proposed Solution

This project introduces a **web-based Smart Irrigation System using ESP32**, which:
- Hosts a **real-time web dashboard** directly on the ESP32
- Displays soil moisture data in a **visual and user-friendly UI**
- Shows water motor (pump) status
- Supports a **Demo Mode using fake data** for easy testing and presentations
- Can be upgraded to **real sensor-based automation**

No external server or cloud is required.

---

## 🎯 Features

- 🌐 ESP32 inbuilt web server  
- 🎨 Attractive, mobile-friendly UI (glassmorphism design)  
- 📊 Animated soil moisture visualization  
- 🔄 Auto-updating data every few seconds  
- 💧 Motor ON/OFF status display  
- 🚫 No cloud or app dependency  
- 🎓 Ideal for mini-projects, demos, and viva  

---

## 🧠 System Architecture

**Main Components**
- ESP32 Microcontroller  
- Wi-Fi Network  
- Web Browser (Mobile / Laptop)

**Operating Modes**
1. **Demo Mode (Fake Data)** – No hardware required  
2. **Live Mode (Upgradeable)** – Real sensor + relay control  

---

## 🖼️ Project Images

Upload your images in the repository and update the paths below.

### 🔹 Web Dashboard UI

<img width="475" height="388" alt="Screenshot 2026-02-01 110424" src="https://github.com/user-attachments/assets/caf18d40-a636-47cb-bcad-864d40892a67" /> / <img width="475" height="388" alt="Screenshot 2026-02-01 110950" src="https://github.com/user-attachments/assets/1ac2f506-555b-49c8-893f-990992ca194c" />




### 🔹 ESP32 Hardware Setup

```md
![ESP32 Setup](images/esp32-setup.jpg)
```

### 🔹 Circuit Diagram

```md
![Circuit Diagram](images/circuit-diagram.png)
```

---

## 🔌 Circuit Diagram (Live Mode – Optional)

| Component              | ESP32 Pin |
| ---------------------- | --------- |
| Soil Moisture (Analog) | GPIO 34   |
| DHT11 Data             | GPIO 27   |
| Relay / Motor          | GPIO 26   |
| VCC                    | 3.3V / 5V |
| GND                    | GND       |


⚠️ **Note:** Demo mode works without any hardware connections.

---

## 🛠️ Software Requirements

* Arduino IDE
* ESP32 Board Package
* USB Cable
* Wi-Fi Network

---

## ⚙️ Installation Steps

### Step 1: Install Arduino IDE

Download from:

```
https://www.arduino.cc/en/software
```

---

### Step 2: Install ESP32 Board Package

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add this URL in *Additional Boards Manager URLs*:

   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to **Tools → Board → Boards Manager**
5. Search **ESP32**
6. Install **ESP32 by Espressif Systems**

---

### Step 3: Download the Project

```bash
git clone https://github.com/your-username/smart-irrigation-esp32.git
```

Or download ZIP and extract.

---

### Step 4: Configure Wi-Fi Credentials

Open the `.ino` file and update:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

### Step 5: Select Board and Port

* Board: **ESP32 Dev Module**
* Port: ESP32 COM Port

---

### Step 6: Upload the Code

Click **Upload** in Arduino IDE.

---

### Step 7: Access the Web Dashboard

1. Open **Serial Monitor** (115200 baud)
2. Copy the ESP32 IP address
3. Paste it into a web browser

🎉 Dashboard will load instantly!

---

## 🧪 Demo Mode (Fake Data)

In Demo Mode:

* Soil moisture values are randomly generated
* Motor state changes automatically
* UI updates every 3 seconds
* No sensor or relay required

Best suited for:

* Project demonstrations
* UI testing
* Academic presentations

---

## 🔄 Future Enhancements

* 🌡 Real soil moisture sensor integration
* 💧 Automatic motor control using thresholds
* 📊 Live charts and data logging
* ☁️ Cloud integration (Firebase / ThingSpeak)
* 📱 Android mobile application
* 🤖 AI-based irrigation scheduling

---

## 📚 Applications

* Smart agriculture
* Home gardening systems
* IoT academic projects
* Embedded systems learning

---

## 👨‍💻 Author

**Ashu**
Electronics & Communication Engineering
ESP32 | IoT | Embedded Systems

 [my portfolio ] (https://yerukondaashritha2-boop.github.io/my_portfolio/)
---

## 📜 License

This project is open-source and intended for educational and research purposes.

---

⭐ If you like this project, don’t forget to star the repository!


---
## ❤️ ©️ Ashu & team's 
---


![Footer](https://capsule-render.vercel.app/api?type=waving&color=0099ff&height=100&section=footer)
