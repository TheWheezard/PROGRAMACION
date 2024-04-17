// Programa para que el motor cambie su sentido de giro cada segundo

// Pines motor (cambiar segun usados)
// Pin de PWM
#define M1 9
#define M2 16

// Pin de direccion
#define IN_M1 11
#define IN_M2 10

// Pin de Standby
#define SLP_M 15
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
long t = 30000;
long d = 30000;

void setup() {
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  //MOTORES M1 Y M2
  pinMode(M1, OUTPUT);  // MOTOR DERECHO
  pinMode(M2, OUTPUT);  // MOTOR IZQUIERDO

  pinMode(IN_M1, OUTPUT);
  pinMode(IN_M2, OUTPUT);

  pinMode(SLP_M, OUTPUT);

  digitalWrite(SLP_M, LOW);  // Dormimos al motor inicialmente (disminuimos consumo)

  // SENSORES CNY
  pinMode(CNY1, INPUT);
  pinMode(CNY2, INPUT);
  pinMode(CNY3, INPUT);
  pinMode(CNY4, INPUT);

  Serial.begin(230350);
}

// TODO: CON ULTRASONIDO PIERDE EL CNY
void loop() {
  
  if (ultraSound() <= 200) {
    digitalWrite(SLP_M, LOW);
  } else {
    // Uso de sensores CNY
    int inCNY1 = analogRead(CNY1);  //5
    int inCNY2 = analogRead(CNY2);  //6
    int inCNY3 = analogRead(CNY3);  //7
    int inCNY4 = analogRead(CNY4);  //8
    if (inCNY2 < 350 && inCNY3 < 350) {
      digitalWrite(SLP_M, LOW);
      delay(1000);
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 30);  // Establecemos la velocidad de giro (valor entre 0-255)
      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente
      delay(1000);
      if (inCNY1 >= 350) {
        digitalWrite(SLP_M, HIGH);  // Despertamos el motor
        analogWrite(M1, 0);         // Establecemos la velocidad de giro (valor entre 0-255)
        analogWrite(M2, 30);        // Establecemos la velocidad de giro (valor entre 0-255)
      } else if (inCNY4 >= 350) {
        digitalWrite(SLP_M, HIGH);  // Despertamos el motor
        analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255)
        analogWrite(M2, 0);         // Establecemos la velocidad de giro (valor entre 0-255)
      }
    } else if (inCNY2 < 350 && inCNY3 >= 350) {  // Si se desvía a la dcha, reducimos motor dcho
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 50);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 130);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

      //delay(1000);  // Mantenemos el estado del motor 1 segundo
    } else if (inCNY2 >= 350 && inCNY3 < 350) {  // Si se desvía a la izqda reducimos motor izquierdo
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 130);       // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 50);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

      //delay(1000);  // Mantenemos el estado del motor 1 segundo
    } else {
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 130);       // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 130);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

      //delay(1000);  // Mantenemos el estado del motor 1 segundo

      // // Movemos el motor en el sentido de giro opuesto

      // //Establecemos sentido de giro opuesto
      // digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente
      // digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente

      // delay(1000);  // Mantenemos el estado del motor 1 segundo
    }
  }
  //Serial.print(inCNY1);
  //Serial.print(", ");
  //Serial.print(inCNY2);
  //Serial.print(", ");
  //Serial.print(inCNY3);
  //Serial.print(", ");
  //Serial.print(inCNY4);
  //Serial.print("\n");
  //delay(1000);
}

long ultraSound() {
  // TRIGGER PULSE
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);  //Enviamos un pulso de 10us
  digitalWrite(TRIG, LOW);

  t = pulseIn(ECHO, HIGH);  //obtenemos el ancho del pulso
  d = t / 59;               //escalamos el tiempo a una distancia
  // Serial.print(t);
  // Serial.print(" ");
  // Serial.println(d);
  // 1/(0,034*2) = 59
  // END TRIGGER PULSE
  return d;
}