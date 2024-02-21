const int GreenLED = 2; // Alias for LED pin
const int PushButton = 12; // Alias for Pushbutton pin
int First_Value_PushButton = HIGH; // Variable to store the push value
int Second_Value_PushButton = HIGH; // Variable to store the push value
//boolean StateLED = false; // Variable to store the state of the LED

void setup() {
  pinMode(GreenLED, OUTPUT);
  pinMode(PushButton, INPUT_PULLUP);
  digitalWrite(GreenLED, HIGH);
}

void loop(){
  Second_Value_PushButton = digitalRead(PushButton);

  if ((First_Value_PushButton == HIGH) && (Second_Value_PushButton == LOW)){
    shutdownLED();
    delay (100);
  }
}

void shutdownLED() {
  digitalWrite (GreenLED, LOW);
  delay(2000);
  digitalWrite(GreenLED, HIGH);
}