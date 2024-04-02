#include <Servo.h>  // Servo's library

Servo miservo;  //It declares servo object
int angulo = 0;

void setup() {
  miservo.attach(9, 1000, 2000);  //Set the pin to attach the servo
}

void loop() {
  //Neutral position
  miservo.write(90);
  delay(3000);
  //Decrease the angle from 90
  for (angulo = 90; angulo > 0; angulo--) {
    miservo.write(angulo);
    delay(100);
  }
  delay(5000);
}