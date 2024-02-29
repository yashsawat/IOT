# NodeMcu_ESP8266_program_to_send_safety_message_by_monitoring_dr.ino

This project is designed to monitor the safety of a driver by using an ESP8266 NodeMCU microcontroller and various sensors. It checks for high alcohol levels and high stress levels (as indicated by heart rate) and sends a safety message accordingly.

## Requirements

- ESP8266WiFi library
- ESP8266HTTPClient library
- WiFiClient library
- UrlEncode library
- SparkFun_MAX3010x_Sensor_Library library
- Wire library

## Setup

1. Connect the ESP8266 NodeMCU to your computer via USB.
2. Open the Arduino IDE and install the required libraries.
3. Open the `NodeMcu_ESP8266_program_to_send_safety_message_by_monitoring_dr.ino` file.
4. Replace the placeholders for `ssid`, `password`, `phoneNumber`, and `apiKey` with your own values.
5. Upload the code to the ESP8266 NodeMCU.

## Usage

1. Power on the ESP8266 NodeMCU.
2. The program will connect to the specified WiFi network.
3. It will then monitor the alcohol sensor and heart rate sensor.
4. If a critical situation is detected (high alcohol level and/or high stress), it will send a safety message via WhatsApp using the `sendMessage` function.
5. The program will continue to monitor and send messages as needed.

## Notes

- The alcohol sensor pin is defined as `A0`.
- The heart rate sensor is a MAX30105 sensor.
- The `sendMessage` function sends a message via the `api.callmebot.com` API. You need to provide your own phone number and API key.
- The program will delay for 15 minutes (900,000 milliseconds) after sending a safety message to avoid spamming.

## Acknowledgments

- This project was inspired by the need for a safety monitoring system for drivers.
- The `SparkFun_MAX3010x_Sensor_Library` was used for the heart rate sensor.
- The `UrlEncode` library was used for URL encoding the message for the API call.
- The `ESP8266WiFi` and `ESP8266HTTPClient` libraries were used for WiFi and HTTP communication.

## Using the callmebot.com API

The `sendMessage` function in the code uses the `callmebot.com` API to send WhatsApp messages. To use this API, you need to obtain an API key from `callmebot.com` and replace the `<api_key>` placeholder in the code with your actual API key.

Additionally, you need to provide your own phone number as the recipient's WhatsApp number. Replace the `<phone_number>` placeholder in the code with your actual phone number.

Please note that the message to be sent should be URL-encoded before being passed to the `sendMessage` function.
