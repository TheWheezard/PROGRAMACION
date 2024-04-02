#include <Servo.h>  // Servo's library

// SERVO VARS
Servo miservo;  //It declares servo object
int angulo = 0;

//LEDS
const int ledG = 4;  // LED green
const int ledR = 5;   // LED red
const int pulsador = 2;

// LDR VARS
//const int sensorPin = A0; // pin that the sensor is attached to
const int calTime = 15000;   // Sets the calibration time
int sensorValue = 0;     // the sensor value
int sensorMin = 1023;    // minimum sensor value
int sensorMax = 0;       // maximum sensor value
int sensorValueMap = 0;  // the sensor value mapped

void setup() {
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);
  //arrancaremos con los LEDs encendidos
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  miservo.attach(9, 1000, 2000);  //Set the pin to attach the servo
  miservo.write(0);
  setup_ldr();
  //los LEDs se apagarán al terminar el calibrado
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
}

void setup_ldr() {
  //To initialize the serial port
  Serial.begin(9600);

  /* Checks if the program execution time is less than 15ms
  If the calibration time has not finished, the calibration
  continues*/
  while (millis() < calTime) {
    sensorValue = analogRead(A0);
    // To record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    // To record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}

void loop() {
  if (sensorValue < (sensorMax + sensorMin)/2) {
      digitalWrite(ledR, LOW);
    if (digitalRead(pulsador) == HIGH) {
      miservo.write(0);
      digitalWrite(ledG, HIGH);
    } else {
      miservo.write(180);
      digitalWrite(ledG, LOW);
    }
  }
  else {
    digitalWrite(ledG, LOW);
    digitalWrite(ledR, HIGH);
    delay(2000);
    digitalWrite(ledR, LOW);
    delay(2000);
  }
}