A GPS tracking system leveraging MQTT communication, designed for seamless integration with Adafruit IO. This project utilizes the NEO-6M GPS module and ESP8266 for precise location tracking and real-time data publishing.

Features:
- NEO-6M GPS module for accurate positioning
- ESP8266 for MQTT communication with Adafruit IO
- Real-time tracking of latitude, longitude, altitude, and speed
- Integration with Adafruit IO feeds for centralized data management

This open-source project provides a robust foundation for building GPS tracking applications with MQTT connectivity. Enhance your IoT projects with reliable location-based monitoring and management.

Getting Started:
1. Connect NEO-6M GPS module and ESP8266 to your hardware. (connect GPS RX > D1, GPS TX >D2, GPS GND > ESP GND,  GPS VCC > ESP 3V3. Please refer the arduino.jpg figure to setup the arduino uno configurations)
2. Configure Wi-Fi credentials and Adafruit IO settings.
3. Configure Adafruit account, dashboards and Feeds. ((Please refer this https://www.youtube.com/watch?v=CSH1NB8RdKQ&t=175s for configure Adafruit IO settings))
4. Upload the provided Arduino sketch to your ESP8266.
5. Monitor GPS data and receive alarms via Adafruit IO dashboard.

Explore the endless possibilities of MQTT-based GPS tracking with Adafruit IO through this user-friendly and customizable project.

Contributions and feedback are welcome! Happy coding!
