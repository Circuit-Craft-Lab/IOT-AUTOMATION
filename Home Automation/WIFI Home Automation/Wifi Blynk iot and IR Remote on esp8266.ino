#define BLYNK_TEMPLATE_ID "*******"
#define BLYNK_TEMPLATE_NAME "******"
#define BLYNK_AUTH_TOKEN "********"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

char ssid[] = "******";
char pass[] = "*****";

// Relay Pins
#define LED1 D1
#define LED2 D2
#define LED3 D5
#define LED4 D7

// TSOP1838
#define IR_PIN D4

IRrecv irrecv(IR_PIN);
decode_results results;

int l1 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;

// Blynk Controls
BLYNK_WRITE(V0)
{
l1 = param.asInt();
digitalWrite(LED1, l1);
}

BLYNK_WRITE(V1)
{
l2 = param.asInt();
digitalWrite(LED2, l2);
}

BLYNK_WRITE(V2)
{
l3 = param.asInt();
digitalWrite(LED3, l3);
}

BLYNK_WRITE(V4)
{
l4 = param.asInt();
digitalWrite(LED4, l4);
}

BLYNK_WRITE(V3)
{
int m = param.asInt();

l1 = m;
l2 = m;
l3 = m;
l4 = m;

digitalWrite(LED1, m);
digitalWrite(LED2, m);
digitalWrite(LED3, m);
digitalWrite(LED4, m);
}

// IR Remote
void checkIR()
{
if (irrecv.decode(&results))
{
unsigned long value = results.value;

Serial.print("HEX Code: ");
Serial.println(value, HEX);

switch (value)
{
case 0xFD40BF: // Button 1
l1 = !l1;
digitalWrite(LED1, l1);
Blynk.virtualWrite(V0, l1);
break;

case 0xFDC03F: // Button 2
l2 = !l2;
digitalWrite(LED2, l2);
Blynk.virtualWrite(V1, l2);
break;

case 0xFD20DF: // Button 3
l3 = !l3;
digitalWrite(LED3, l3);
Blynk.virtualWrite(V2, l3);
break;

case 0xFDA05F: // Button 4
l4 = !l4;
digitalWrite(LED4, l4);
Blynk.virtualWrite(V4, l4);
break;

case 0xFD609F: // Button 5 = ALL ON/OFF
l1 = !l1;
l2 = l1;
l3 = l1;
l4 = l1;

digitalWrite(LED1, l1);
digitalWrite(LED2, l2);
digitalWrite(LED3, l3);
digitalWrite(LED4, l4);

Blynk.virtualWrite(V0, l1);
Blynk.virtualWrite(V1, l2);
Blynk.virtualWrite(V2, l3);
Blynk.virtualWrite(V4, l4);
Blynk.virtualWrite(V3, l1);
break;
}

irrecv.resume();
}
}

void setup()
{
Serial.begin(9600);

pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);

digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);

irrecv.enableIRIn();

Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
Blynk.run();
checkIR();
}
