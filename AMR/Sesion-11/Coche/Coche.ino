/**
 * @file Coche.ino
 * @brief Programa para controlar el movimiento de un coche con motores y sensores.
 */



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

/**
 * @brief Enumeración para representar los colores detectados por los sensores CNY.
 */
enum color { VACIO, ROJO, BLANCO, NEGRO, AZUL };



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

  // Una vez iniciado todo, lo ponemos en modo "avanzar"
  // para que se coloque por sí solo en la zona de carga
  avanzarCargar();
}

void loop() {
  // Uso de sensores CNY
  // int inCNY1 = analogRead(CNY1); //5
  // int inCNY2 = analogRead(CNY2); //6
  // int inCNY3 = analogRead(CNY3); //7
  // int inCNY4 = analogRead(CNY4); //8
  // Serial.print(inCNY1);
  // Serial.print(", ");
  // Serial.print(inCNY2);
  // Serial.print(", ");
  // Serial.print(inCNY3);
  // Serial.print(", ");
  // Serial.print(inCNY4);
  // Serial.print("\n");
  // delay(1000);


  int c = color::VACIO;
  while (c == color::VACIO) {
    c = detectarColor();
  }

  delay(4000);
  while (detectarObstaculo()) {}

  switch (c) {
  case color::ROJO:
    avanzaRojo();
    break;

  case color::NEGRO:
    avanzaNegro();
    break;

  case color::BLANCO:
    avanzaBlanco();
    break;

  default: // TODO: Decidir qué hacer
    break;
  }

  while (hayCarga()) {}
  delay(2000);

  avanzarCargar();
}

/**
 * @brief Función para detectar el color de la superficie.
 *
 * Realiza lecturas de los sensores CNY hasta detectar un obstáculo.
 *
 * @param None
 * @return El número de lecturas realizadas antes de detectar el obstáculo.
 */
int detectarColor() {
  int count = 0;
  while (count < 4) {
    if (!detectarObstaculo())
      count++;
    else return count;
    delay(2000);
  }
  return count;
}

/**
 * @brief Función para detectar la presencia de un obstáculo.
 *
 * @param None
 * @return true si hay un obstáculo, false en caso contrario.
 */
bool detectarObstaculo() { return ultraSound() <= 150; }

/**
 * @brief Función para detectar si hay un cubo cargado en el coche.
 *
 * @param None
 * @return true si hay carga, false en caso contrario.
 */
bool hayCarga() {} //devolvemos aquí lo que detecte el LDR

/**
 * @brief Función para medir la distancia mediante un sensor de ultrasonido.
 *
 * @param None
 * @return La distancia medida en centímetros.
 */
long ultraSound() {
  long t = 30000;
  long d = 30000;
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

/**
 * @brief Función para avanzar el coche.
 *
 * Mueve el coche hacia adelante o hacia atrás dependiendo de las lecturas de los sensores CNY.
 * Si no detecta línea, el coche se mueve hacia atrás.
 * Si detecta línea en el sensor izquierdo, el coche se desvía a la derecha.
 * Si detecta línea en el sensor derecho, el coche se desvía a la izquierda.
 * Si detecta línea en ambos sensores, el coche avanza hacia adelante.
 *
 * @param None
 * @return None
 */
void avanza() {
  int inCNY2 = analogRead(CNY2);  //6
  int inCNY3 = analogRead(CNY3);  //7

  if (inCNY2 < 350 && inCNY3 < 350) { // Marcha atrás hasta detectar línea
    digitalWrite(SLP_M1, LOW);
    delay(1000);
    // Movemos el motor en un sentido de giro
    digitalWrite(SLP_M1, HIGH);  // Despertamos el motor
    analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255)

    //digitalWrite(SLP_M1, HIGH); // Despertamos el motor
    analogWrite(M2, 30);  // Establecemos la velocidad de giro (valor entre 0-255)
    // Establecemos sentido de giro
    digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente
    digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente
    delay(1000);
  }
  else if (inCNY2 < 350 && inCNY3 >= 350) {  // Si se desvía a la izqda, reducimos motor dcho
    // Movemos el motor en un sentido de giro
    digitalWrite(SLP_M1, HIGH);  // Despertamos el motor
    analogWrite(M1, 50);        // Establecemos la velocidad de giro (valor entre 0-255)

    //digitalWrite(SLP_M1, HIGH); // Despertamos el motor
    analogWrite(M2, 130);  // Establecemos la velocidad de giro (valor entre 0-255)

    // Establecemos sentido de giro
    digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
    digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

    //delay(1000);  // Mantenemos el estado del motor 1 segundo
  }
  else if (inCNY2 >= 350 && inCNY3 < 350) {  // Si se desvía a la izqda reducimos motor dcho
    // Movemos el motor en un sentido de giro
    digitalWrite(SLP_M1, HIGH);  // Despertamos el motor
    analogWrite(M1, 130);       // Establecemos la velocidad de giro (valor entre 0-255)

    //digitalWrite(SLP_M1, HIGH); // Despertamos el motor
    analogWrite(M2, 50);  // Establecemos la velocidad de giro (valor entre 0-255)

    // Establecemos sentido de giro
    digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente
    digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente

    //delay(1000);  // Mantenemos el estado del motor 1 segundo
  }
  else { // Hacia adelante
    // Movemos el motor en un sentido de giro
    digitalWrite(SLP_M1, HIGH);  // Despertamos el motor
    analogWrite(M1, 130);       // Establecemos la velocidad de giro (valor entre 0-255)

    //digitalWrite(SLP_M1, HIGH); // Despertamos el motor
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

/**
 * @brief Función para avanzar el coche hasta detectar la parada del color rojo.
 *
 * @param None
 * @return None
 */
void avanzaRojo() {
  int inCNY1 = analogRead(CNY1);  //5
  int inCNY4 = analogRead(CNY4);  //8

  while (!(inCNY1 >= 350 && inCNY4 < 350)) {
    avanza();
  }
}

/**
 * @brief Función para avanzar el coche hasta detectar la parada del color blanco.
 *
 * @param None
 * @return None
 */
void avanzaBlanco() {
  int inCNY1 = analogRead(CNY1);  //5
  int inCNY4 = analogRead(CNY4);  //8

  while (!(inCNY1 < 350 && inCNY4 >= 350)) {
    avanza();
  }
}

/**
 * @brief Función para avanzar el coche hasta detectar la parada del color negro.
 *
 * @param None
 * @return None
 */
void avanzaNegro() {
  int inCNY1 = analogRead(CNY1);  //5
  int inCNY4 = analogRead(CNY4);  //8

  while (!(inCNY1 >= 350 && inCNY4 >= 350)) {
    avanza();
  }
}

/**
 * @brief Función para avanzar el coche hasta la zona de carga.
 *
 * Avanza el coche y verifica la distancia medida por el sensor de ultrasonido.
 * Si la distancia es menor o igual a 200 cm, el motor se pone en modo standby.
 *
 * @param None
 * @return None
 */
void avanzarCargar() {
  avanza();
  if (ultraSound() <= 200) {
    digitalWrite(SLP_M1, LOW);
  }
}