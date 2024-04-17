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
}

void loop() {

    // Movemos el motor en un sentido de giro

    digitalWrite(SLP_M1, HIGH); // Despertamos el motor
    analogWrite(M1, 255); // Establecemos la velocidad de giro (valor entre 0-255)

    //digitalWrite(SLP_M1, HIGH); // Despertamos el motor
    analogWrite(M2, 255); // Establecemos la velocidad de giro (valor entre 0-255)

    // Establecemos sentido de giro
    digitalWrite(IN_M1, LOW); // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
    digitalWrite(IN_M2, LOW); // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

    delay(1000); // Mantenemos el estado del motor 1 segundo

    // Movemos el motor en el sentido de giro opuesto

    //Establecemos sentido de giro opuesto
    digitalWrite(IN_M1, HIGH); // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente
    digitalWrite(IN_M2, HIGH); // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente

    delay(1000); // Mantenemos el estado del motor 1 segundo


    // Uso de sensores CNY
    int inCNY1 = analogRead(CNY1);
    int inCNY2 = analogRead(CNY2);
    int inCNY3 = analogRead(CNY3);
    int inCNY4 = analogRead(CNY4);
    Serial.begin(230400);
    Serial.print();
}