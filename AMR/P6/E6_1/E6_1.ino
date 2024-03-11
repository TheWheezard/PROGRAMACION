/* PRACTICA 6, EJERCICIO 1
@author: Javier Lopez Sierra
*/
const int buzzer = 9;  //buzzer to arduino pin 9
int bell = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);  // Set buzzer - pin 9 as an output
}

void loop() {
  if (Serial.available() > 0) {
    bell = Serial.parseInt();
    for (int i = 0; i < bell; i++) {
      tone(buzzer, 950);  // Send 1KHz sound signal...
      delay(1000);         // ...for 1 sec
      noTone(buzzer);      // Stop sound...
      delay(1000);         // ...for 1 sec
    }
    noTone(buzzer);      // Stop sound...
  }
}