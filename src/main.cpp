#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

#define LEDPIN 13  // Pin 13 : Arduino has an LED connected on pin 13

#define SENSORPIN_1 2  // Pin 2
#define SENSORPIN_2 3  // Pin 3
#define SENSORPIN_3 5  // Pin 5
#define SENSORPIN_4 6  // Pin 6
#define SENSORPIN_5 7  // Pin 7
#define SENSORPIN_6 8  // Pin 8
#define SENSORPIN_7 9  // Pin 9

// variables will change:
int sensorState_1 = 0, sensorState_2 = 0, sensorState_3 = 0, sensorState_4 = 0,
    sensorState_5 = 0, sensorState_6 = 0, sensorState_7 = 0, lastState_1 = 0,
    lastState_2 = 0, lastState_3 = 0, lastState_4 = 0, lastState_5 = 0,
    lastState_6 = 0, lastState_7 = 0;
// Time tracking Values
unsigned long sensorMillis_1 = 0, sensorMillis_2 = 0, sensorMillis_3 = 0,
              sensorMillis_4 = 0, sensorMillis_5 = 0, sensorMillis_6 = 0,
              sensorMillis_7 = 0;
// Time we wait before we set up another trigger
unsigned long debounceTime = 15000;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {0xA0, 0x61, 0x0A, 0xAE, 0xA9, 0x84};  // Testing_board MAC
// address
// byte mac[] = {0xA0, 0x61, 0x0A, 0xAE, 0xA9, 0x78};  // Center_Putt MAC
// address byte mac[] = {0xA0, 0x61, 0x0A, 0xAE, 0xA9, 0x7F}; // Ski_Putt_1 MAC
// address byte mac[] = {0xA0, 0x61, 0x0A, 0xAE, 0xA9, 0x76}; // Ski_Putt_2 MAC
// address
IPAddress ip(192, 168, 0, 175);  // The ip of the arduino's ethernet shield

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
IPAddress fpp(192, 168, 0, 101);        // numeric IP for our local FPP
unsigned int httpDestinationPort = 80;  // destination of our HTTP requests

EthernetClient client;

// converts a type of IPAddress into a string
String IpAddress2String(const IPAddress &ipAddress) {
  return String(ipAddress[0]) + String(".") + String(ipAddress[1]) +
         String(".") + String(ipAddress[2]) + String(".") +
         String(ipAddress[3]);
}

// assigns the local IP to a var for our HOST parameter
String ipStr = IpAddress2String(ip);

void runRainbow() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/rainbow/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole1() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole1/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole2() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole2/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole3() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole3/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole4() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole4/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole6() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole6/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void hole7() {
  // if you get a connection, report back via serial:
  if (client.connect(fpp, httpDestinationPort)) {
    Serial.print("Http rainbow connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /api/playlist/hole7/start HTTP/1.1");
    client.print("Host: ");
    client.println(ipStr);
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
void setup() {
  // ------------------------> IR Beam Break Setup here <----------------------
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN_1, INPUT);
  digitalWrite(SENSORPIN_1, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_2, INPUT);
  digitalWrite(SENSORPIN_2, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_3, INPUT);
  digitalWrite(SENSORPIN_3, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_4, INPUT);
  digitalWrite(SENSORPIN_4, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_5, INPUT);
  digitalWrite(SENSORPIN_5, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_6, INPUT);
  digitalWrite(SENSORPIN_6, HIGH);  // turn on the pullup
  pinMode(SENSORPIN_7, INPUT);
  digitalWrite(SENSORPIN_7, HIGH);  // turn on the pullup

  // ------------------------>  Ethernet Setup <----------------------
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(
        "Ethernet shield was not found.  Sorry, can't run without hardware. "
        ":(");
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  //------------------------>  HTTP Client Setup <-----------------------
}

void loop() {
  // read the state of the pushbutton value:
  sensorState_1 = digitalRead(SENSORPIN_1);
  sensorState_2 = digitalRead(SENSORPIN_2);
  sensorState_3 = digitalRead(SENSORPIN_3);
  sensorState_4 = digitalRead(SENSORPIN_4);
  sensorState_5 = digitalRead(SENSORPIN_5);
  sensorState_6 = digitalRead(SENSORPIN_6);
  sensorState_7 = digitalRead(SENSORPIN_7);
  //

  //
  // Sensor 1
  if (sensorState_1 && !lastState_1) {
    Serial.println("Unbroken_1");
  }
  if (!sensorState_1 && lastState_1) {
    if (millis() - sensorMillis_1 > debounceTime) {
      Serial.println("Broken_1");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_1 = millis();
    }
  }
  lastState_1 = sensorState_1;
  //
  // Sensor 2
  if (sensorState_2 && !lastState_2) {
    Serial.println("Unbroken_2");
  }
  if (!sensorState_2 && lastState_2) {
    if (millis() - sensorMillis_2 > debounceTime) {
      Serial.println("Broken_2");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_2 = millis();
    }
  }
  lastState_2 = sensorState_2;
  //
  // Sensor 3
  if (sensorState_3 && !lastState_3) {
    Serial.println("Unbroken_3");
  }
  if (!sensorState_3 && lastState_3) {
    if (millis() - sensorMillis_3 > debounceTime) {
      Serial.println("Broken_3");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_3 = millis();
    }
  }
  lastState_3 = sensorState_3;
  //
  // Sensor 4
  if (sensorState_4 && !lastState_4) {
    Serial.println("Unbroken_4");
  }
  if (!sensorState_4 && lastState_4) {
    if (millis() - sensorMillis_4 > debounceTime) {
      Serial.println("Broken_4");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_4 = millis();
    }
  }
  lastState_4 = sensorState_4;
  //
  // Sensor 5
  if (sensorState_5 && !lastState_5) {
    Serial.println("Unbroken_5");
  }
  if (!sensorState_5 && lastState_5) {
    if (millis() - sensorMillis_5 > debounceTime) {
      Serial.println("Broken_5");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_5 = millis();
    }
  }
  lastState_5 = sensorState_5;
  //
  // Sensor 6
  if (sensorState_6 && !lastState_6) {
    if (millis() - sensorMillis_6 > debounceTime) {
      Serial.println("Unbroken_6");
    }
  }
  if (!sensorState_6 && lastState_6) {
    Serial.println("Broken_6");
    // Http Message Send
    runRainbow();
    // millis tracking for debounce
    sensorMillis_6 = millis();
  }
  lastState_6 = sensorState_6;
  //
  // Sensor 7
  if (sensorState_7 && !lastState_7) {
    Serial.println("Unbroken_7");
  }
  if (!sensorState_7 && lastState_7) {
    if (millis() - sensorMillis_7 > debounceTime) {
      Serial.println("Broken_7");
      // Http Message Send
      runRainbow();
      // millis tracking for debounce
      sensorMillis_7 = millis();
    }
  }
  lastState_7 = sensorState_7;

  // Delay to slow down processing
  delay(10);
}