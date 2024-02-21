int arrayLED[] = {2, 3, 4, 5};
const int timer = 1000;
const int PushButton = 12; // Alias for Pushbutton pin
int Value_PushButton = HIGH; // Variable to store the push value
//boolean StateLED = false; // Variable to store the state of the LED

void setup() {
  for (int i=0; i < 4; i++) {
    pinMode(arrayLED[i], OUTPUT);
    digitalWrite(arrayLED[i], LOW);
  }
  pinMode(PushButton, INPUT_PULLUP);
}

void loop(){
  for (int i=0; i < 4; i++) {
    digitalWrite(arrayLED[i], HIGH);
    delay(timer);
    digitalWrite(arrayLED[i], LOW);
  }
  for (int i=3; i <= 0; i--) {
    digitalWrite(arrayLED[i], HIGH);
    delay(timer);
    digitalWrite(arrayLED[i], LOW);
  }
}