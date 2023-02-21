#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define LEDPIN 13
// Pin 13 : Arduino has an LED connected on pin 13
// Pin 11: Teensy 2.0 has the LED on pin 11
// Pin  6: Teensy++ 2.0 has the LED on pin 6
// Pin 13: Teensy 3.0 has the LED on pin 13

#define SENSORPIN_1 2
#define SENSORPIN_2 3
#define SENSORPIN_3 5
#define SENSORPIN_4 6
#define SENSORPIN_5 7
#define SENSORPIN_6 8
#define SENSORPIN_7 9

// variables will change:
int sensorState_1 = 0,
    sensorState_2 = 0,
    sensorState_3 = 0,
    sensorState_4 = 0,
    sensorState_5 = 0,
    sensorState_6 = 0,
    sensorState_7 = 0,
    lastState_1 = 0, // variable for reading the pushbutton status
    lastState_2 = 0, // variable for reading the pushbutton status
    lastState_3 = 0, // variable for reading the pushbutton status
    lastState_4 = 0, // variable for reading the pushbutton status
    lastState_5 = 0, // variable for reading the pushbutton status
    lastState_6 = 0, // variable for reading the pushbutton status
    lastState_7 = 0; // variable for reading the pushbutton status

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
    0xA0, 0x61, 0x0A, 0xAE, 0xA9, 0x84};
IPAddress ip(192, 168, 0, 175);

IPAddress sPlay(192, 168, 0, 25);

unsigned int localPort = 8888;        // local port to listen on
unsigned int destinationPort = 65406; // port we are sending udp message to

// buffers for receiving and sending data
// char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; // buffer to hold incoming packet,
// char ReplyBuffer[] = "acknowledged";       // a string to send back
String udpIdentifier = "bbSensor"; // the string to precede a closure packet

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup()
{
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN_1, INPUT);
  digitalWrite(SENSORPIN_1, HIGH); // turn on the pullup

  Serial.begin(9600);

  //--------------------------------->  udp trigger logic here <----------------------
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10); // Most Arduino shields
  // Ethernet.init(5);   // MKR ETH Shield
  // Ethernet.init(0);   // Teensy 2.0
  // Ethernet.init(20);  // Teensy++ 2.0
  // Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  // Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
  Udp.begin(localPort);
}

void loop()
{
  // read the state of the pushbutton value:
  sensorState_1 = digitalRead(SENSORPIN_1);
  sensorState_2 = digitalRead(SENSORPIN_2);
  sensorState_3 = digitalRead(SENSORPIN_3);
  sensorState_4 = digitalRead(SENSORPIN_4);
  sensorState_5 = digitalRead(SENSORPIN_5);
  sensorState_6 = digitalRead(SENSORPIN_6);
  sensorState_7 = digitalRead(SENSORPIN_7);

  // check if the sensor beam is broken
  // if it is, the sensorState_1 is LOW:
  if (sensorState_1 == LOW)
  {
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    // turn LED off:
    digitalWrite(LEDPIN, LOW);
  }
  //
  // Sensor 1
  if (sensorState_1 && !lastState_1)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_1" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_1 && lastState_1)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_1" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_1 = sensorState_1;
  //
  // Sensor 2
  if (sensorState_2 && !lastState_2)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_2" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_2 && lastState_2)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_2" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_2 = sensorState_2;
  //
  // Sensor 3
  if (sensorState_3 && !lastState_3)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_3" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_3 && lastState_3)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_3" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_3 = sensorState_3;
  //
  // Sensor 4
  if (sensorState_4 && !lastState_4)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_4" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_4 && lastState_4)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_4" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_4 = sensorState_4;
  //
  // Sensor 5
  if (sensorState_5 && !lastState_5)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_5" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_5 && lastState_5)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_5" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_5 = sensorState_5;
  //
  // Sensor 6
  if (sensorState_6 && !lastState_6)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_6" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_6 && lastState_6)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_6" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_6 = sensorState_6;
  //
  // Sensor 7
  if (sensorState_7 && !lastState_7)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_7" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState_7 && lastState_7)
  {
    Serial.println("Broken");
    // UDP LOGIC HERE!!!
    String msgStr = udpIdentifier + "_7" + "_Broken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  lastState_7 = sensorState_7;
  //--------------------------------->  udp trigger logic here <----------------------
  // // if there's data available, read a packet
  // int packetSize = Udp.parsePacket();
  // if (packetSize)
  // {
  //   Serial.print("Received packet of size ");
  //   Serial.println(packetSize);
  //   Serial.print("From ");
  //   IPAddress remote = Udp.remoteIP();
  //   for (int i = 0; i < 4; i++)
  //   {
  //     Serial.print(remote[i], DEC);
  //     if (i < 3)
  //     {
  //       Serial.print(".");
  //     }
  //   }
  //   Serial.print(", port ");
  //   Serial.println(Udp.remotePort());

  //   // read the packet into packetBuffer
  //   Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
  //   Serial.println("Contents:");
  //   Serial.println(packetBuffer);

  //   // send a reply to the IP address and port that sent us the packet we received
  //   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  //   Udp.write(ReplyBuffer);
  //   Udp.endPacket();
  // }
  delay(10);
}
