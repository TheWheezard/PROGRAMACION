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

// PIN LDR
#define LDR 14

/**
 * @brief Enumeración para representar los colores detectados por los sensores CNY.
 */
enum color { VACIO,
             ROJO,
             BLANCO,
             NEGRO,
             AZUL };
int c; // COLOR GLOBAL VARIABLE

/**
 * @brief Función para detectar si hay un cubo cargado en el coche.
 *
 * @param None
 * @return true si hay carga, false en caso contrario.
 */
bool hayCarga() {  //devolvemos aquí lo que detecte el LDR
  // return true;
  return analogRead(LDR) > 300;
}

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

  int c = VACIO;  
  Serial.begin(230350);
}

/**
 * @brief Función para detectar la presencia de un obstáculo.
 *
 * @param None
 * @return true si hay un obstáculo, false en caso contrario.
 */
bool detectarObstaculo() {
  return ultraSound() <= 150;
}

/**
 * @brief Función para detectar el color de la superficie.
 *
 * Realiza lecturas de los sensores CNY hasta detectar un obstáculo.
 *
 * @param None
 * @return El número de lecturas realizadas antes de detectar el obstáculo.
 * 
 * @note Revisar su funcionamiento. Hay que sincronizar con brazo robótico 
 * para que funcione correctamente.
 */
int detectarColor() {
  int count = 0;
  while (!detectarObstaculo()) {
    count++;
    delay(1000);
  }
  Serial.print("count: ");
  Serial.println(count);
  return count;
  // return ROJO;
}

// @note Revisar su funcionamiento. Hay que sincronizar con brazo robótico
// para que funcione correctamente.
// @note El principal problema es que ultraSound a veces devuelve ceros y desconocemos el motivo
void loop() {
  long distancia = ultraSound(); // definitivamente vamos a añadir esto a ver si funciona
  if (distancia <= 130 && distancia > 0) { // así saltamos los ceros
    Serial.println("close");
    digitalWrite(SLP_M, LOW);
    while (!hayCarga()) {}
    while (c == VACIO) { c = detectarColor(); }
  } else if (distancia != 0) {
    Serial.println("go");
    // Uso de sensores CNY
    int inCNY1 = analogRead(CNY1);  //5
    int inCNY2 = analogRead(CNY2);  //6
    int inCNY3 = analogRead(CNY3);  //7
    int inCNY4 = analogRead(CNY4);  //8
    if ((inCNY1 >= 350 && inCNY4 < 350 && inCNY2 > 350 && inCNY3 > 350) && c <= ROJO) { // ROJO
      digitalWrite(SLP_M, LOW);
      while(hayCarga()){}
      delay(4000);
      c = VACIO;
      digitalWrite(SLP_M, HIGH);
    } else if ((inCNY1 >= 350 && inCNY4 >= 350 && inCNY2 > 350 && inCNY3 > 350) && c >= NEGRO) { // NEGRO
      digitalWrite(SLP_M, LOW);
      while(hayCarga()){}
      delay(4000);
      c = VACIO;
      digitalWrite(SLP_M, HIGH);
    } else if ((inCNY1 < 350 && inCNY4 >= 350 && inCNY2 > 350 && inCNY3 > 350) && c >= BLANCO) { // BLANCO
      digitalWrite(SLP_M, LOW);
      while(hayCarga()){}
      delay(4000);
      c = VACIO;
      digitalWrite(SLP_M, HIGH);
    } else if (inCNY2 < 350 && inCNY3 < 350) {
      digitalWrite(SLP_M, LOW);
      delay(1000);
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 20);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 20);  // Establecemos la velocidad de giro (valor entre 0-255)
      // Establecemos sentido de giro
      digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente
      delay(1000);
      // if (inCNY1 >= 350) {
      //   digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      //   analogWrite(M1, 0);         // Establecemos la velocidad de giro (valor entre 0-255)
      //   analogWrite(M2, 20);        // Establecemos la velocidad de giro (valor entre 0-255)
      // } else if (inCNY4 >= 350) {
      //   digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      //   analogWrite(M1, 20);        // Establecemos la velocidad de giro (valor entre 0-255)
      //   analogWrite(M2, 0);         // Establecemos la velocidad de giro (valor entre 0-255)
      // }
    } else if (inCNY2 < 350 && inCNY3 >= 350) {  // Si se desvía a la dcha, reducimos motor dcho
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 14);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 25);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

      //delay(1000);  // Mantenemos el estado del motor 1 segundo
    } else if (inCNY2 >= 350 && inCNY3 < 350) {  // Si se desvía a la izqda reducimos motor izquierdo
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 25);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 14);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

      //delay(1000);  // Mantenemos el estado del motor 1 segundo
    } else {
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255)

      //digitalWrite(SLP_M, HIGH); // Despertamos el motor
      analogWrite(M2, 30);  // Establecemos la velocidad de giro (valor entre 0-255)

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

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
    Serial.print(t);
    Serial.print(" ");
    Serial.println(d);
  
  // 1/(0,034*2) = 59
  // END TRIGGER PULSE
  return d;
}