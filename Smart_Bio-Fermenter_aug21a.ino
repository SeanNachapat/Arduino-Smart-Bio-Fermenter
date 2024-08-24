
#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
#include <Servo.h>
#include <Time.h>

MKRIoTCarrier carrier;
Servo myServo;

int servoPin = 5;
float co2;
const int activationTimes[] = {6, 12, 18};

uint32_t red = carrier.leds.Color(255, 0, 0);
uint32_t green = carrier.leds.Color(0, 255, 0);
uint32_t blue = carrier.leds.Color(0, 0, 255);
uint32_t cyan = carrier.leds.Color(0, 255, 255);
uint32_t yellow = carrier.leds.Color(255, 255, 0);
uint32_t off = carrier.leds.Color(0, 0, 0);
uint32_t purple = carrier.leds.Color(160,32,240);
uint32_t white = carrier.leds.Color(255,255,255);

void setup() {
  carrier.noCase();
  carrier.begin();
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  myServo.attach(servoPin);
  status = false;
  carrier.leds.clear();
}

void loop() {
  ArduinoCloud.update();

  // Visualization
  co2 = analogRead(A1);
  Serial.println(co2);
  alcohol = analogRead(A2) / 10.00;
  pH = (analogRead(A3) / 100.000) - 0.600; 

  // Funciton
  if (co2 > 500) {
    for(int i =0; i < 10; i++) {
      carrier.leds.fill(white,0,5);
      carrier.leds.show();
      delay(150);
      carrier.leds.fill(off,0,5);
      carrier.leds.show();
      delay(150);
    }
  }

  if (pH < 4 && alcohol > 210) {
    status = true;
    carrier.leds.fill(green,0,5);
    carrier.leds.show();
    action == false;
  }
}

void onAlcoholChange()  {

}

void onPHChange()  {

}

void onActionChange()  {
  if (action == true) {
    for(int i =0; i < 5; i++) {
      carrier.leds.fill(purple,0,5);
      carrier.leds.show();
      delay(500);
      carrier.leds.fill(off,0,5);
      carrier.leds.show();
      delay(500);
    }
  } else {
    for(int i =0; i < 5; i++) {
      carrier.leds.fill(red,0,5);
      carrier.leds.show();
      delay(500);
      carrier.leds.fill(off,0,5);
      carrier.leds.show();
      delay(500);
    }
  }
}

void onStatusChange() {

}

void onTimerChange() {
  while (action == true) {
    if (timer.isActive()) {
      carrier.leds.fill(green,0,5);
      carrier.leds.show();
      stir();
    } else {
      carrier.leds.fill(off,0,5);
      carrier.leds.show();
    }
  }
}

//method
void stir() {
  while (action == true) {
    for (int pos = 0; pos <= 360; pos++) {
      myServo.write(pos);
      delay(15);
      }
    for (int pos = 360; pos >= 0; pos--) {
        myServo.write(pos);
        delay(15);
    }
  }
}