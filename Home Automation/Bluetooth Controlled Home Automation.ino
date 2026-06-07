#include <SoftwareSerial.h>

SoftwareSerial BT(10, 9);   // RX, TX

#define RELAY1 4
#define RELAY2 3
#define RELAY3 2

void setup() {

  Serial.begin(9600);   // Serial Monitor
  BT.begin(9600);       // HC-05

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  // Active LOW Relay Module
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  Serial.println("Bluetooth Home Automation Ready");
}

void loop() {

  if (BT.available()) {

    char data = BT.read();

    Serial.print("Button Pressed: ");
    Serial.println(data);

    switch (data) {

      case '1':
        digitalWrite(RELAY1, LOW);
        Serial.println("Relay 1 ON");
        break;

      case '2':
        digitalWrite(RELAY1, HIGH);
        Serial.println("Relay 1 OFF");
        break;

      case '3':
        digitalWrite(RELAY2, LOW);
        Serial.println("Relay 2 ON");
        break;

      case '4':
        digitalWrite(RELAY2, HIGH);
        Serial.println("Relay 2 OFF");
        break;
      case '5':
        digitalWrite(RELAY3, LOW);
        Serial.println("Relay 2 ON");
        break;

      case '6':
        digitalWrite(RELAY3, HIGH);
        Serial.println("Relay 2 OFF");
        break;

      case 'A':
        digitalWrite(RELAY1, LOW);
        digitalWrite(RELAY2, LOW);
        digitalWrite(RELAY3, LOW);
        Serial.println("Both Relays ON");
        break;

      case 'B':
        digitalWrite(RELAY1, HIGH);
        digitalWrite(RELAY2, HIGH);
        digitalWrite(RELAY3, HIGH);
        Serial.println("Both Relays OFF");
        break;

      default:
        Serial.println("Unknown Command");
        break;
    }
  }
}
