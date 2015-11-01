#include <OneWire.h>
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.google.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;


// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)

void setup(void) {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }

  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  Serial.println();

  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
    Serial.println("  Chip = DS18S20");  // or old DS1820
    type_s = 1;
    break;
    case 0x28:
    Serial.println("  Chip = DS18B20");
    type_s = 0;
    break;
    case 0x22:
    Serial.println("  Chip = DS1822");
    type_s = 0;
    break;
    default:
    Serial.println("Device is not a DS18x20 family device.");
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;



  /*
  AT+CIPSTART=id,"type","addr",port
  id = 0
  type = "TCP"
  addr = "www.example.com"
  port = 80
  */
  String TARGET_ID="0";
  String TARGET_TYPE="TCP";
  String TARGET_ADDR="184.106.153.149";  //ThingSpeak IP Address
  String TARGET_PORT="80";

  String cmd="AT+CIPSTART=" + TARGET_ID;
  cmd += ",\"" + TARGET_TYPE + "\",\"" + TARGET_ADDR + "\"";
  cmd += ","+ TARGET_PORT;

  //Serial.println(cmd);
  // ESP8266.println(cmd);
  //delay(1000);
  //Assume OK
  //display and clear buffer
  //clearESP8266SerialBuffer();

  /*
  POST /update?key=<API KEY>&field1=xx.xx&field2=xx.xx HTTP/1.1\r\n
  Host: api.thingspeak.com\r\n\r\n
  */

  String ThingSpeakMethod = "POST";  //GET should also work
  String ThingSpeakHost = "/update";
  String ThingSpeakApiKey = "LBBXXKVUARTYIKL4";
  String ThingSpeakField1 = "field1";
  String ThingSpeakHttp = "HTTP/1.1";

  String ThingSpeak_2ndLine = "Host: api.thingspeak.com\r\n\r\n";

  String HTTP_RQS = ThingSpeakMethod;
  HTTP_RQS += " " + ThingSpeakHost;
  HTTP_RQS += "?key=" + ThingSpeakApiKey;
  HTTP_RQS += "&" + ThingSpeakField1 + "=" + celsius;
  HTTP_RQS += " " + ThingSpeakHttp + "\r\n";
  HTTP_RQS += ThingSpeak_2ndLine;

  String cmdSEND_length = "AT+CIPSEND=";
  cmdSEND_length += TARGET_ID + "," + HTTP_RQS.length() +"\r\n";
}
