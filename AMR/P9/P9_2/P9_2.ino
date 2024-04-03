// Pines del TCS3200 conectados a Arduino
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 2
// Fijar frecuencia leída por los fotodiodos y el valor inicial del potenciómetro
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int Pot = 0;

void setup() {
    // Configurar las salidas
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Configurar que la señal sensorOut es una entrada
    pinMode(sensorOut, INPUT);
    // Configurar la frecuencia al 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    // Comenzar comunicación en serie
    Serial.begin(9600);
}

void loop() {
    // Lee e imprime por pantalla el valor del potenciómetro
    Pot = analogRead(A0);
    Serial.print("Pot: ");
    Serial.print(Pot);
    // Configurar los fotodiodos con filtro rojo RED (R) para que sean leídos
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Leer la frecuencia de salida
    redFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de rojo RED (R)
    Serial.print("R = ");
    Serial.print(redFrequency);
    delay(100);

    // Configurar los fotodiodos con filtro verde GREEN (G) para que sean leídos
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Leer la frecuencia de salida
    greenFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de verde GREEN (G)
    Serial.print(" G = ");
    Serial.print(greenFrequency);
    delay(100);

    // Configurar los fotodiodos con filtro azul BLUE (B) para que sean leídos
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Leer la frecuencia de salida
    blueFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de azul BLUE (B)
    Serial.print(" B = ");
    Serial.print(blueFrequency);
    
    Serial.println();
    delay(100);
}