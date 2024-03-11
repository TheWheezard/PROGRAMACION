#define Do 261.63
#define Silencio 0
int buzzer = 9;
int melodia[] = { Do, Silencio, Do, Do, Silencio };
void setup() {
  pinMode(buzzer, OUTPUT);
}
void loop() {
  for (int nota = 0; nota < 5; nota++) {
    tone(buzzer, melodia[nota], 500);
    delay(500);
    noTone(3);
  }
}