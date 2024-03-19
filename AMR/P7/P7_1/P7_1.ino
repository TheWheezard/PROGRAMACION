/* Project07_01: Motor DC turning both ways. Driver L293D
*/
//Variables & Constant definition
const int L293D_Pin2 = 7;
const int L293D_Pin7 = 8;

void setup() {
  pinMode(L293D_Pin2, OUTPUT);
  pinMode(L293D_Pin7, OUTPUT);
}

void loop() {
  //Motor-DC turns left
  digitalWrite(L293D_Pin2, HIGH);
  digitalWrite(L293D_Pin7, LOW);
  delay(1000);

  //Stop
  digitalWrite(L293D_Pin2, LOW);
  digitalWrite(L293D_Pin7, LOW);
  delay(1000);

  // Motor-DC turns right
  digitalWrite(L293D_Pin2, LOW);
  digitalWrite(L293D_Pin7, HIGH);
  delay(1000);
  
  //Stop
  digitalWrite(L293D_Pin2, LOW);
  digitalWrite(L293D_Pin7, LOW);
  delay(1000);
}