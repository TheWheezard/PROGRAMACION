/*
Project07_02. Speed control Motor DC
*/
//Variables & Constant definition
const int IMA1 = 6; //PWM-A
const int IMA2 = 8; //MOTOR A

const int IMB1 = 11; //MOTOR B
const int IMB2 = 5; //PWM-B

const int L293D_enablePin = 9;
// const int pushButtom_Pin = 2;
// const int potentiometerPin = 0;
int valuePotentiometer = 0;
int valuePotentiometerMap = 0;
bool valueRotation = true;

void setup() {
  pinMode(IMA1, OUTPUT);
  pinMode(IMA2, OUTPUT);
  pinMode(L293D_enablePin, OUTPUT);
  //pinMode(pushButtom_Pin, INPUT_PULLUP);
}

void loop() {
  //[OLD]Read Potentiometer and change to the PWM scale (0-255)
  //This value set the speed of the motor
  //It will be proportional to the input from de POT
  valuePotentiometer = setSpeed(analogRead(A0));
  //TODO: change rotation direction

  //Call function with the arguments
  setMotorA(valuePotentiometerMap, valueRotation);
}

int setSpeed(int valuePotentiometer) {
  int speed = 0;
  // if (valuePotentiometer <= 500) {
  //   speed = map(valuePotentiometer, 500, 0, 0, 255);
  //   valueRotation = true;
  // } else if (valuePotentiometer >= 523) {
  //   speed = map(valuePotentiometer, 523, 1023, 0, 255);
  //   valueRotation = false;
  // } else {
  //   speed = map(valuePotentiometer, 501, 522, 0, 0);
  // }
  speed = map(valuePotentiometer, 0, 100, 0, 255);
  return speed;
}

void setMotorA(int speedMotor, bool spinMotor) {
  analogWrite(L293D_enablePin, speedMotor);
  digitalWrite(IMA1, !spinMotor);
  digitalWrite(IMA2, spinMotor);
}

void setMotorB(int speedMotor, bool spinMotor) {
  analogWrite(L293D_enablePin, speedMotor); // need to change the pin
  digitalWrite(IMB1, !spinMotor);
  digitalWrite(IMB2, spinMotor);
}