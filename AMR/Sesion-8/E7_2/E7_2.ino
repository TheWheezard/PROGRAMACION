// Programa para que el motor cambie su sentido de giro cada segundo

// Pines motor (cambiar segun usados)
// Pin de PWM
#define M1 9
#define M2 16

// Pin de direccion
#define IN_M1 11
#define IN_M2 10

// Pin de Standby
#define SLP_M1 15
#define SLP_M2 15

// Pines Sensor CNY
#define CNY1 4
#define CNY2 3
#define CNY3 2
#define CNY4 1

// Pines Buzzer
#define BUZZ 5

#define LED 8

//Pines UltraSonido
#define ECHO 12
#define TRIG 13

void setup() {

  //MOTORES M1 Y M2
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(IN_M1, OUTPUT);
  pinMode(IN_M2, OUTPUT);

  pinMode(SLP_M1, OUTPUT);

  digitalWrite(SLP_M1, LOW);  // Dormimos al motor inicialmente (disminuimos consumo)

  // SENSORES CNY
  pinMode(CNY1, INPUT);
  pinMode(CNY2, INPUT);
  pinMode(CNY3, INPUT);
  pinMode(CNY4, INPUT);

  Serial.begin(230400);
}

void loop() {
    // Uso de sensores CNY
    int inCNY1 = analogRead(CNY1); //5
    int inCNY2 = analogRead(CNY2); //6
    int inCNY3 = analogRead(CNY3); //7
    int inCNY4 = analogRead(CNY4); //8
    Serial.print(inCNY1);
    Serial.print(", ");
    Serial.print(inCNY2);
    Serial.print(", ");
    Serial.print(inCNY3);
    Serial.print(", ");
    Serial.print(inCNY4);
    Serial.print("\n");
    delay(1000);
}