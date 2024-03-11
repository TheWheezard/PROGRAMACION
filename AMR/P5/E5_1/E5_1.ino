/* PRÁCTICA 5 EJERCICIO 1
@author: Javier López Sierra
*/
int analogInput = 0;
int analogOutput = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  analogInput = analogRead(A0);
  analogOutput = map(analogInput, 0, 1023, 0, 10);
  Serial.println(analogOutput);
}
