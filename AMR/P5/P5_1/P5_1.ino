/*
--------------------------------------
Project05_01.- Reading the serial port
--------------------------------------
*/

int greenLED = 12;
char letter;

void setup() {
  Serial.begin(9600);  //Starts Serial comunication
  pinMode(greenLED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { //Checks if there is a byte in Serial Port
    letter = Serial.read();  //Reads the value from Serial port
    
    // If the real letter is 'Y' switch on the LED
    if ((letter == 'Y') || (letter == 'y')) {
      digitalWrite(greenLED, HIGH);
    }
    
    // If the real letter is 'N' switch on the LED
    else if ((letter == 'N') || (letter == 'n')) {
      digitalWrite(greenLED, LOW);
    }
  }
}