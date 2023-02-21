#include <Arduino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define LEDPIN 13
// Pin 13 : Arduino has an LED connected on pin 13
// Pin 11: Teensy 2.0 has the LED on pin 11
// Pin  6: Teensy++ 2.0 has the LED on pin 6
// Pin 13: Teensy 3.0 has the LED on pin 13

#define SENSORPIN 2

// variables will change:
int sensorState = 0,
    lastState = 0; // variable for reading the pushbutton status

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
  pinMode(SENSORPIN, INPUT);
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup

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
  sensorState = digitalRead(SENSORPIN);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW)
  {
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    // turn LED off:
    digitalWrite(LEDPIN, LOW);
  }

  if (sensorState && !lastState)
  {
    Serial.println("Unbroken");
    String msgStr = udpIdentifier + "_1" + "_Unbroken";
    char msgChar[msgStr.length() + 1];
    strcpy(msgChar, msgStr.c_str());
    Udp.beginPacket(sPlay, destinationPort);
    Udp.write(msgChar);
    Udp.endPacket();
  }
  if (!sensorState && lastState)
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
  lastState = sensorState;
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
