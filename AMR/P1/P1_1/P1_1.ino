const int GreenLED = 11; // Alias for pin number 11
const int RedLED = 12; // Alias for pin number 12
void setup() {
// initialize the LED pin as an output:
 pinMode(GreenLED, OUTPUT);
 pinMode(RedLED, OUTPUT);

}
void loop(){
 //turn the Green Led on:
 digitalWrite(GreenLED, HIGH);
 digitalWrite(RedLED, LOW);

 // Wait for 1 second
 delay(1000);
 // turn the Red Led on
 digitalWrite(RedLED, HIGH);
 digitalWrite(GreenLED, LOW);
 // Wait for 1 second
 delay(1000);
 }