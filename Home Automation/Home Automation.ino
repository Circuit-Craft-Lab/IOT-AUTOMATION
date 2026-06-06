#include <IRremote.hpp>

int IR_PIN = 2;
int relay1 = 11;
int relay2 = 12;

bool state1 = LOW;
bool state2 = LOW;

void setup() {
Serial.begin(9600);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);

IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
if (IrReceiver.decode()) {

unsigned long code = IrReceiver.decodedIRData.decodedRawData;
Serial.println(code, HEX);

// Button 1
if (code == 0xFD02BF00) {
state1 = !state1;
digitalWrite(relay1, state1);
}
// Button 2
if (code == 0xFC03BF00) {
state2 = !state2;
digitalWrite(relay2, state2);
}

IrReceiver.resume();
}
}







