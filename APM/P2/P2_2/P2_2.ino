// Fade an LED in and out
const int GreenLED = 9; // Pin with the LED connected
int i = 0; // To count up and down
void setup() {
	pinMode(GreenLED, OUTPUT);
}

void loop(){
	for (i = 0; i < 256; i++) { // loop from 0 to 255 (fade in)
		analogWrite(GreenLED, i); // set the LED brightness
		delay(10); // Wait 10ms because analogWrite
				   // is instantaneous and we would
				   // not see any change
}
  
	for (i = 255; i >= 0; i--) { // loop from 255 to 1 (fade out)
		analogWrite(GreenLED, i); // set the LED brightness
		delay(10); // Wait 10ms
	}
}