

#include <IRremote.hpp>

void setup() {
Serial.begin(9600);
IrReceiver.begin(2, ENABLE_LED_FEEDBACK); // OUT pin connected to D2
Serial.println("IR Receiver Started");
}

void loop() {
if (IrReceiver.decode()) {
Serial.print("HEX Code: 0x");
Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
IrReceiver.resume();
}
}
