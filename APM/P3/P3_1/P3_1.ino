const int LDR_pin = 0;
int LDR_val = 0; // Variable to store the read value
const float Resolution = 0.0049; // Arduino’s ADC resolution
const int timer = 1000; //

void setup() {
  Serial.begin(9600); // Setup serial terminal
}
void loop(){
  LDR_val = analogRead(LDR_pin); // To read input LDR value
  // PRINTING ON SCREEN
  Serial.print("Digital value = "); // To print without return
  Serial.print("\t"); // To print a tab
  Serial.print(LDR_val); // Integer Value (0-1023)
  Serial.print("\t"); // To print a tab
  Serial.print("Tension LDR = ");
  Serial.print("\t"); // To print a tab
  // Calculation of equivalent voltage according to the ADC resolution
  Serial.println(LDR_val*Resolution); //Prints and return line
  // Wait before to read again the sensor
  delay(timer);
}