// Fade an LED in and out
const int GreenLED = 9;
int AnalogInput = 0;
int AnalogOutput = 0;

void setup() {
	pinMode(GreenLED, OUTPUT);

  //Open the serial port and setting the baudrate to 9.600 bauds
	Serial.begin(9600);
}

void loop() {
	//Read the analog value in A0
	AnalogInput = analogRead(A0);

	//Send the value stored in the variable “AnalogValue” and
	// show it in terminal serial (A value in a range from 0 to 1023)
	Serial.println(AnalogInput);
  AnalogOutput = map(AnalogInput, 0, 1023, 0, 255);
  Serial.println(AnalogOutput);

	//Check condition to switch on the LED
  analogWrite(GreenLED, AnalogOutput);
	
	delay(200);
}