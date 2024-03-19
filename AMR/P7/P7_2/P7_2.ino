/*
Project07_02. Speed control Motor DC
*/
//Variables & Constant definition
const int L293D_Pin2 = 7;
const int L293D_Pin7 = 8;
const int L293D_enablePin = 9;
const int pushButtom_Pin = 2;
//const int potentiometerPin = 0;
int valuePotentiometer = 0;
int valuePotentiometerMap = 0;
boolean valuePushButtom = true;

void setup() {
  pinMode(L293D_Pin2, OUTPUT);
  pinMode(L293D_Pin7, OUTPUT);
  pinMode(L293D_enablePin, OUTPUT);
  pinMode(pushButtom_Pin, INPUT_PULLUP);
}

void loop() {
  //Read Potentiometer and change to the PWM scale (0-255)
  //This value set the speed of the motor
  //It will be proportional to the input from de POT
  valuePotentiometer = analogRead(A0);
  valuePotentiometerMap = map(valuePotentiometer, 0, 1023, 0, 255);

  //Read the pushbuttom to set the spin of the motor
  //Turn Right when valuePushButtom=HIGH (default value)
  //Turn Left when valuePushButtom=LOW
  valuePushButtom = digitalRead(pushButtom_Pin);
  //Call function with the arguments
  setMotor(valuePotentiometerMap, valuePushButtom);
}

void setMotor(int speedMotor, boolean spinMotor) {
  analogWrite(L293D_enablePin, speedMotor);
  digitalWrite(L293D_Pin2, !spinMotor);
  digitalWrite(L293D_Pin7, spinMotor);
}