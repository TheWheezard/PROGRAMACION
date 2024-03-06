/* Para este ejercicio he heredado el funcionamiento de los pines 2 y 3 de ejercicios anteriores
   con el propósito de aún poder comprobar visualmente si el sensor se está calibrando o ya está funcionando*/

// These constants won't change:
const int sensorPin = A0; // pin that the sensor is attached to
const int ledStartTest = 2;  // LED to notice calibration starts
const int ledStopTest = 3;   // LED to notice calibration ends
const int outputLED = 9;  // LED for the final result
const int calTime = 15000;   // Sets the calibration time
const int timer = 1000;      // Sets the waiting time to read again

// variables:
int sensorValue = 0;     // the sensor value
int sensorMin = 1023;    // minimum sensor value
int sensorMax = 0;       // maximum sensor value
int sensorValueMap = 0;  // the sensor value mapped
void setup() {
  pinMode(ledStartTest, OUTPUT);
  pinMode(ledStopTest, OUTPUT);
  pinMode(outputLED, OUTPUT);
  //To initialize the serial port
  Serial.begin(9600);
  // turn on LED START to signal the start of the calibration period:
  digitalWrite(ledStartTest, HIGH);
  digitalWrite(ledStopTest, LOW);
  digitalWrite(outputLED, LOW);

  /* Checks if the program execution time is less than 15ms
  If the calibration time has not finished, the calibration
  continues*/
  while (millis() < calTime) {
    sensorValue = analogRead(sensorPin);
    // To record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
    // To record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
  // To warn the end of the calibration period
  digitalWrite(ledStartTest, LOW);
  digitalWrite(ledStopTest, HIGH);
}

void loop() {
	//Read the analog value in A0
	sensorValue = analogRead(sensorPin);

  // Compare analog reading to the average of sensorMax & sensorMin
  if (sensorValue < (sensorMax + sensorMin)/2) digitalWrite(outputLED, HIGH);
  else digitalWrite(outputLED, LOW);
}
