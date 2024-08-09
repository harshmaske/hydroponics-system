#include <ESP8266WiFi.h>

String apiKey1 = ""; // Enter your ThingSpeak Write API key for MQ-135
String apiKey2 = ""; // Enter your ThingSpeak Write API key for LDR
String apiKey3 = ""; // Enter your ThingSpeak Write API key for Water Level

const char *ssid = "rushi@7"; // Replace with your WiFi SSID
const char *pass = "123456789"; // Replace with your WiFi password
const char *server = "api.thingspeak.com";

const int MQ135_D0_PIN = D0; // Digital input pin for MQ-135
const int LDR_PIN = D1; // Analog pin for LDR
const int WATER_SENSOR_PIN = A0; // Analog pin for Water Level Sensor

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial.println("Connecting to Wi-Fi:");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

void loop()
{
  // MQ-135 Sensor
  int mq135DigitalValue = digitalRead(MQ135_D0_PIN);

  if (client.connect(server, 80))
  {
    String postStr = apiKey1;
    postStr += "&field1=";
    postStr += String(mq135DigitalValue);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey1 + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Data sent to ThingSpeak for MQ-135.");
  }
  client.stop();

  // LDR Sensor
  int ldrValue = analogRead(LDR_PIN);

  if (client.connect(server, 80))
  {
    String postStr = apiKey2;
    postStr += "&field1=";
    postStr += String(ldrValue);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey2 + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Data sent to ThingSpeak for LDR.");
  }
  client.stop();

  // Water Level Sensor
  int waterLevel = analogRead(WATER_SENSOR_PIN);

  if (client.connect(server, 80))
  {
    String postStr = apiKey3;
    postStr += "&field1=";
    postStr += String(waterLevel);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey3 + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Data sent to ThingSpeak for Water Level.");
  }
  client.stop();

  Serial.println("Waiting for next update...");

  // ThingSpeak requires a minimum 15-second delay between updates
  delay(15000);
}
