#include <OneWire.h>
OneWire  ds(10);
#include <SPI.h>
#include <Ethernet.h>

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Must be unique on local network
// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "LBBXXKVUARTYIKL4";
const int updateThingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup()
{
  // Start Serial for debugging on the Serial Monitor
  Serial.begin(9600);
  // Start Ethernet on Arduino
  startEthernet();
}

void loop()
{
  int celsius;
  // Read value from Analog Input Pin 0
  String analogValue0 = String(celsius, DEC);
  // Update ThingSpeak
  if(client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
  {
    updateThingSpeak(analogValue0);
  }
}

void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {
    String postStr = writeAPIKey;
           postStr +="&amp;field1=";
           postStr += String(tsData);
           postStr += "\r\n\r\n";


    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");

    client.print(postStr);

    lastConnectionTime = millis();
    client.stop();
  }

  void startEthernet()
  {
    Serial.println("Connecting Arduino to network...");
    Serial.println();

    delay(1000);

    // Connect to network amd obtain an IP address using DHCP
    if (Ethernet.begin(mac) == 0)
    {
      Serial.println("DHCP Failed, reset Arduino to try again");
      Serial.println();
    }
    else
    {
      Serial.println("Arduino connected to network using DHCP");
      Serial.println();
    }
    delay(1000);
  }
test branch
test branch
test
