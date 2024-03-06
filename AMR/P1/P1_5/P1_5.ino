const int GreenLED = 2; // Alias for LED pin
const int PushButton = 12; // Alias for Pushbutton pin

int First_Value_PushButton = HIGH; // It stores the FIRST reading
int Second_Value_PushButton = 0; // It stores the SECOND reading

boolean stateLED = false; // Variable to store the state of the LED

void setup() {
  pinMode(GreenLED, OUTPUT);
pinMode(PushButton, INPUT_PULLUP);
}

void loop(){
  // First time, “First_ValPush” is the initialized value
  // Microcontroller reads a second value from the buttom
  Second_Value_PushButton = digitalRead(PushButton);

  // Check if there was a transition (HIGH to LOW)
  if ((First_Value_PushButton == HIGH) && (Second_Value_PushButton == LOW)){
    stateLED = !stateLED;
    delay (100);
  }

  // if ((Second_Value_PushButton == LOW)){
  //   stateLED = !stateLED;
  // }
  // For future readings, “Second_ValPush” is now the “First_ValPush”
  First_Value_PushButton = Second_Value_PushButton;


  if(stateLED) digitalWrite (GreenLED, HIGH);
  else digitalWrite (GreenLED, LOW);

}