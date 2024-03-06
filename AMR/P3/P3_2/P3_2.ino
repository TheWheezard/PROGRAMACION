// These constants won't change:
const int sensorPin = A0; // pin that the sensor is attached to
const int ledStartTest = 2; // LED to notice calibration starts
const int ledStopTest = 3; // LED to notice calibration ends
const int calTime = 15000; // Sets the calibration time
const int timer = 1000; // Sets the waiting time to read again

// variables:
int sensorValue = 0; // the sensor value
int sensorMin = 1023;    // minimum sensor value
int sensorMax = 0;       // maximum sensor value
int sensorValueMap = 0;  // the sensor value mapped
void setup() {
  pinMode(ledStartTest, OUTPUT);
  pinMode(ledStopTest, OUTPUT);
  //To initialize the serial port
  Serial.begin(9600);
  // turn on LED START to signal the start of the calibration period:
  digitalWrite(ledStartTest, HIGH);
  digitalWrite(ledStopTest, LOW);

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
  //To send the Vmax and Vmin
  Serial.print("Vmax= ");
  Serial.println(sensorMax);
  Serial.print("Vmin= ");
  Serial.println(sensorMin);
  delay(timer);
}