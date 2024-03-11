/*
--------------------------------------
Project05_02.- Reading the serial port
--------------------------------------
*/

int redLED = 11;
int greenLED = 12;
char letter;

void setup() {
  Serial.begin(9600);  //Starts Serial comunication
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {  //Checks if there is a byte in Serial Port
    letter = Serial.read();      //Reads the value from Serial port

    switch (letter) {
      case 'a': // Ambos LEDs encendidos
        Serial.println("Ambos LEDs encendidos");
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, HIGH);
        break;

      case 'b': // LED verde encendido 1s
        Serial.println("LED verde encendido");
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
        delay(1000);
        digitalWrite(greenLED, LOW);
        break;

      case 'c': // mantener encendido LED rojo
        Serial.println("LED rojo encendido");
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);
        break;

      case 'd': // parpadeo LED rojo
        Serial.println("LED rojo parpadeando");
        digitalWrite(greenLED, LOW);
        parpadearLED(redLED);
        delay(500);
        break;

      default:
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
    }
    delay(1000);
  }
}

void parpadearLED(int redLED) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(redLED, HIGH);
    delay(500);
    digitalWrite(redLED, LOW);
    delay(500);
  }
}