/* PRÁCTICA 5 EJERCICIO 2
@author: Javier López Sierra
*/

int greenLED = 12;
bool active = false; // true = ON, false = OFF
char letter;

void setup() {
  Serial.begin(9600);  //Starts Serial comunication
  pinMode(greenLED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { //Checks if there is a byte in Serial Port
    letter = Serial.read();  //Reads the value from Serial port
    
    if (letter == 'a') {
      if (active) digitalWrite(greenLED, LOW);
      else digitalWrite(greenLED, HIGH);
      active = !active;
    }
  }
}