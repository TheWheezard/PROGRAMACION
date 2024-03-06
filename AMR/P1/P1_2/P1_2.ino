const int GreenLED = 2; // Alias for LED pin
const int PushButton = 12; // Alias for Pushbutton pin
int Value_PushButton=0; // Variable to store the push value
void setup() {
pinMode(GreenLED, OUTPUT);
// Set PushPin as INPUT and enable the internal Pull-up
//resistor
pinMode(PushButton, INPUT_PULLUP);
}

void loop(){
  Value_PushButton = digitalRead(PushButton);

  if(Value_PushButton) digitalWrite (GreenLED, HIGH);
  else digitalWrite (GreenLED, LOW);

}