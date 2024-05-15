
// VCC——5V
// GND——GND
// S0——D3
// S1——D4
// S2——D5
// S3——D6
// OUT——D2
// Pin central del Potenciómetro‐A0

#define S0 0   // D3
#define S1 1   // D4
#define S2 2   // D5
#define S3 4   // D6
#define OUT 10 // D2

const int s0 = 3;
const int s1 = 4;
const int s2 = 5;
const int s3 = 6;
const int out = 2;

byte countRed = 0;
byte countGreen = 0;
byte countBlue = 0;
int Pot = 0;
// inicialización de entradas y salidas
void setup() {
    Serial.begin(9600);
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(out, INPUT);
    digitalWrite(s0, HIGH);
    digitalWrite(s1, HIGH);
}
// Programa principal
void loop() {
    //Función de tomar color 
    getColor();
    //Lectura del potenciómetro
    Pot = analogRead(A0);
    // Imprimir por el puerto serie 
    Serial.print("Pot: ");
    Serial.print(Pot);
    Serial.print(" Red: ");
    Serial.print(countRed, DEC);
    Serial.print(" Green: ");
    Serial.print(countGreen, DEC);
    Serial.print(" Blue: ");
    Serial.println(countBlue, DEC);

    // Recordatorio Valor del potenciómetro Pot = 185
    // Intervalo Rojo – Intervalo verde – Intervalo azul
    if (countRed > 30 && countRed < 45 && countGreen > 65 && countGreen < 80 && countBlue > 55 && countBlue < 75) {
        Serial.println(" ‐ Color Rojo");
    }
    // else if (countRed > 200 && countRed < 230 && countGreen > 185 && countGreen < 220 && countBlue > 80 && countBlue < 115) {
    //     Serial.println(" ‐ Color Azul");
    // }
    // else if (countRed > 170 && countRed < 200 && countGreen > 80 && countGreen < 100 && countBlue > 35 && countBlue < 55) {
    //     Serial.println(" ‐ Color 3");
    // }
    else if (countRed > 50 && countRed < 60 && countGreen > 105 && countGreen < 120 && countBlue > 90 && countBlue < 110) {
        Serial.println(" ‐ Color Blanco");
    }
    // else if (countRed > 20 && countRed < 60 && countGreen > 20 && countGreen < 60 && countBlue > 180 && countBlue < 230) {
    //     Serial.println(" ‐ Color Negro");
    // }
    else if (countRed > 100 /*&& countGreen < 50 && countBlue > 170 && countBlue < 70*/) {
        Serial.println(" ‐ Color Negro");
    }
    else {
        Serial.println("‐");
    }
    delay(300);
}

//Función coger color 
void getColor() {
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    countRed = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s3, HIGH);
    countBlue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s2, HIGH);
    countGreen = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}