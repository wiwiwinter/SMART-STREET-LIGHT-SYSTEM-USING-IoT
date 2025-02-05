# Smart Street Light System using IoT

## Overview
This project implements a Smart Street Light System (SSLS) utilizing the Internet of Things (IoT) to optimize energy consumption, improve lighting efficiency, and enhance public safety. The system integrates advanced sensors, Arduino microcontrollers, RGB LED lighting, and wireless communication to enable dynamic lighting control and real-time monitoring.

## Features
- **Energy Efficiency**: Uses motion detection to adjust brightness based on vehicular and pedestrian movement.
- **Dynamic Color Adjustment**: RGB LED lights change color based on ambient temperature for better visibility and aesthetic appeal.
- **IoT Integration**: Real-time data monitoring and control through ThingSpeak.
- **Physical and Software Security**:
  - Hardware secured with a padlock.
  - Source code protected with encrypted zip file access.

## Components
### Hardware:
- **Arduino UNO**: Central microcontroller for processing sensor data.
- **RGB LED Light**: Adjustable intensity and color lighting.
- **ESP8266 Wi-Fi Module**: Enables IoT connectivity for remote monitoring.
- **Ultrasonic Sensor (HR-SR04)**: Detects vehicle presence for adaptive brightness control.
- **Infrared Temperature Sensor**: Measures ambient temperature to determine LED color.
- **LCD Screen**: Displays real-time system status and sensor readings.
- **Power Supply (5V)**: Provides necessary operational voltage.
- **Padlock**: Protects the physical components of the system.

### Software:
- **Arduino IDE**: Used for programming the microcontroller.
- **ThingSpeak**: Online platform for real-time monitoring and data visualization.
- **Embedded Algorithm**:
  - Continuously collects temperature and motion sensor data.
  - Adjusts lighting intensity and color based on sensor readings.
  - Displays real-time data on the LCD.
  - Sends sensor data to ThingSpeak for remote monitoring.

## System Block Diagram
```
[Battery] → [Microcontroller (Arduino UNO)] → [Sensors (Infrared & Ultrasonic)]
  → [RGB LED Light] → [Wi-Fi Module (ESP8266)] → [ThingSpeak Cloud]
```

## Implementation & Results
The prototype successfully demonstrates:
- Reduced energy consumption by adaptive lighting control.
- Effective color adjustment based on temperature conditions.
- Real-time monitoring through ThingSpeak.
- Secure hardware and software implementation.

## Future Enhancements
- Further reduction in response time and system latency.
- Enhanced security mechanisms for software protection.
- Extended IoT functionalities for smart city integration.

## Authors
- **Edgar Jr. B. Villas**
- **Mohammad Naim Mariga**

## License
This project is open-source. Feel free to modify and improve!

## References
For further reading, see the included project report and related studies in the `docs/` folder.
