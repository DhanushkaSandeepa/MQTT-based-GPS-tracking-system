//Import following header files

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "YOUR_SSID"
#define WLAN_PASS       "YOUR_WIFI_PASSWORD"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883  // Use 8883 for SSL
#define AIO_USERNAME    "YOUR_USERNAME"
#define AIO_KEY         "YOUR_ADAFRUIT_SECRET_KEY"



/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'gpsloc' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish gpsloc = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gpsloc/csv"); //specify your feed name here

/***************************** GPS Configuration ****************************/

// GPS module configuration
static const int RXPin = 4;  // Connect GPS RX to D1 on ESP8266
static const int TXPin = 3;  // Connect GPS TX to D2 on ESP8266
static const uint32_t GPSBaud = 9600;

// Create a software serial connection for the GPS module
SoftwareSerial myGPS(RXPin, TXPin);

// Create a TinyGPS++ object to parse the GPS data
TinyGPSPlus gps;

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi access point.
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the GPS module
  myGPS.begin(GPSBaud);

  Serial.println("Setup completed.");
}

uint32_t x = 0;

void loop() {
  // Ensure the connection to the MQTT server is alive.
  MQTT_connect();

  while (myGPS.available() > 0) {
    gps.encode(myGPS.read());
   
    if (gps.location.isUpdated()) {
      // Read GPS data
      
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      float altitude = gps.altitude.meters();
      float speed_mph = gps.speed.mph();
      float heading = gps.course.deg();

      // Construct CSV data to publish
      char gpsData[100];
      snprintf(gpsData, sizeof(gpsData), "%.2f,%.6f,%.6f,%.2f", speed_mph, latitude, longitude, altitude);
     

      // Publish GPS data to Adafruit IO
      if (gpsloc.publish(gpsData)) {
        Serial.println(F("Published GPS data to Adafruit IO"));
        delay(5000);
      } else {
        Serial.println(F("Failed to publish GPS data"));
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
