/***
 * @file Coche.ino
 * @brief Código para el control de un coche autónomo siguelíneas. Realiza la detección de líneas,
 * colores y obstáculos mediante sensores LDR, CNY y ultrasonido. Su objetivo es recibir un cubo como carga,
 * completar un recorrido y detenerse en una parada concreta según el color del cubo.
*/

// Pines motor.
// Pin de PWM.
#define M1 9
#define M2 16

// Pin de direccion.
#define IN_M1 11
#define IN_M2 10

// Pin de Standby.
#define SLP_M 15
#define SLP_M2 15

// Pines Sensor CNY.
#define CNY1 4
#define CNY2 3
#define CNY3 2
#define CNY4 1

// Pines Buzzer y LED.
#define BUZZ 5
#define LED 8

//Pines UltraSonido
#define ECHO 12
#define TRIG 13
// Variables para el ultrasonido, por defecto.
long t = 30000;
long d = 30000;

// PIN LDR
#define LDR 14

/**
 * @brief Enumeración para representar los colores detectados por los sensores CNY.
 */
enum color { VACIO,   // == 0
             ROJO,    // == 1
             BLANCO,  // == 2
             NEGRO }; // == 3
             
int c; // COLOR VARIABLE GLOBAL

/**
 * @brief Función para detectar si hay un cubo cargado en el coche.
 * Se utiliza para ello el sensor LDR.
 * @param None
 * @return true si hay carga, false en caso contrario.
 */
bool hayCarga() {  //devolvemos aquí lo que detecte el LDR
  return analogRead(LDR) > 300;
}

/**
 * @brief Inicialización del programa de Arduino.
 * 
 */
void setup() {
  // Inicializamos los pines del sensor de ultrasonido.
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  // Pines de Motores M1 y M2 para velocidad
  pinMode(M1, OUTPUT);  // MOTOR DERECHO
  pinMode(M2, OUTPUT);  // MOTOR IZQUIERDO

  // Pines de Motores M1 y M2 para el sentido
  pinMode(IN_M1, OUTPUT);  // MOTOR DERECHO
  pinMode(IN_M2, OUTPUT);  // MOTOR IZQUIERDO

  // Pin de encendido/apagado de motores
  pinMode(SLP_M, OUTPUT);
  digitalWrite(SLP_M, LOW);  // Dormimos al motor inicialmente (disminuimos consumo)

  // Pines de sensores CNY, de izquierda a derecha
  pinMode(CNY1, INPUT);
  pinMode(CNY2, INPUT);
  pinMode(CNY3, INPUT);
  pinMode(CNY4, INPUT);

  int c = VACIO;  // Inicializamos el color a VACIO
  Serial.begin(230400); // Inicializamos la comunicación serie.
}

/**
 * @brief Función para medir la distancia a un obstáculo mediante el sensor de ultrasonido.
 * @param None
 * @return La distancia en milímetros a un obstáculo.
 */
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
  
  // END TRIGGER PULSE
  return d;
}

/**
 * @brief Función para detectar la presencia de un obstáculo.
 * Utiliza el sensor de ultrasonido y comprueba si la distancia es menor o igual a 150 mm.
 * @param None
 * @return true si hay un obstáculo, false en caso contrario.
 */
bool detectarObstaculo() {
  return ultraSound() <= 150;
}

/**
 * @brief Función para detectar el color de la carga.
 *
 * Realiza el recuento de segundos que tarda el sensor de ultrasonido en detectar un obstáculo.
 * 
 * @note - Si se detecta un obstáculo en ~1 segundo, el color es ROJO.
 * @note - Si se detecta un obstáculo en ~2 segundos, el color es BLANCO.
 * @note - Si se detecta un obstáculo en ~3 segundos, el color es NEGRO.
 *
 * @param None
 * @return El número de segundos pasados antes de detectar el obstáculo.
 * @note Se debe sincronizar con el brazo robótico para que funcione correctamente.
 */
int detectarColor() {
  int count = 0;

  // Mientras no detecte la barrera, contará segundos
  while (!detectarObstaculo()) {
    count++;
    delay(1000);
  }

  Serial.print("count: ");
  Serial.println(count);

  return count;
}


/**
 * @brief Función de Arduino que se ejecuta en bucle con los pasos del robot siguelíneas.
 * Aquí se puede observar el funcionamiento del programa "paso a paso".
 * 
 */
void loop() {
  long distancia = ultraSound(); // Leemos la distancia a obstáculos mediante el sensor de ultrasonido.

  // Comprobamos si hay un obstáculo o no en el camino.
  // NOTA: A veces la lectura devuelve ceros, se ha determinado que la causa podría ser la conexión de pines concretos.
  // Hasta entonces se ha solventado el problema mediante lógica en el código.
  if (distancia <= 130 && distancia > 0) { // PASOS 1 y 2: CARGAR CUBO Y RECIBIR COLOR.
    // Si se ha detectado la barrera, nos encontramos en la zona de carga. Esperamos a que se cumplan los pasos 1 y 2 del Braccio.
    Serial.println("closed");
    digitalWrite(SLP_M, LOW); // Detenemos el motor.
    while (!hayCarga()) {} // Esperamos a que se cargue el cubo.
    while (c == VACIO) { c = detectarColor(); } // Detectamos el color del cubo.
  } 
  else if (distancia != 0) { 
    // Si no hay obstáculo, avanzamos.
    Serial.println("go");
    // Uso de sensores CNY
    int inCNY1 = analogRead(CNY1);  //5
    int inCNY2 = analogRead(CNY2);  //6
    int inCNY3 = analogRead(CNY3);  //7
    int inCNY4 = analogRead(CNY4);  //8

    // Comprobamos los valores de los sensores CNY para determinar el patrón del suelo.
    if ((inCNY1 >= 350 && inCNY4 < 350 && inCNY2 > 350 && inCNY3 > 350) && c <= ROJO) { // ROJO
      // Si el patrón del suelo es la parada del cubo ROJO y el color del cubo es ROJO, se hace el paso 4.
      digitalWrite(SLP_M, LOW); // Detenemos el motor.
      while(hayCarga()){} // Esperamos a que se descargue el cubo.
      delay(4000); // Esperamos 4 segundos para evitar colisiones.
      c = VACIO;  // Reiniciamos el color del cubo.
      digitalWrite(SLP_M, HIGH); // Despertamos el motor.
    } 
    else if ((inCNY1 < 350 && inCNY4 >= 350 && inCNY2 > 350 && inCNY3 > 350) && c >= BLANCO) { // BLANCO
      // Si el patrón del suelo es la parada del cubo BLANCO y el color del cubo es BLANCO, se hace el paso 4.
      digitalWrite(SLP_M, LOW); // Detenemos el motor.
      while(hayCarga()){} // Esperamos a que se descargue el cubo.
      delay(4000); // Esperamos 4 segundos para evitar colisiones.
      c = VACIO; // Reiniciamos el color del cubo.
      digitalWrite(SLP_M, HIGH); // Despertamos el motor.
    }
    else if ((inCNY1 >= 350 && inCNY4 >= 350 && inCNY2 > 350 && inCNY3 > 350) && c >= NEGRO) { // NEGRO
      // Si el patrón del suelo es la parada del cubo NEGRO y el color del cubo es NEGRO, se hace el paso 4.
      digitalWrite(SLP_M, LOW); // Detenemos el motor.
      while(hayCarga()){} // Esperamos a que se descargue el cubo.
      delay(4000); // Esperamos 4 segundos para evitar colisiones.
      c = VACIO; // Reiniciamos el color del cubo.
      digitalWrite(SLP_M, HIGH); // Despertamos el motor.
    }
    else if (inCNY2 < 350 && inCNY3 < 350) {
      // Si el robot se encuentra en el PASO 3 (seguir el circuito) y no detecta la línea, se moverá hacia atrás con un leve giro hasta recuperarla.
      
      // digitalWrite(SLP_M, LOW);
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor.
      analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255).
      analogWrite(M2, 20);        // Establecemos la velocidad de giro (valor entre 0-255).

      // Establecemos sentido de giro
      digitalWrite(IN_M1, HIGH);  // El pin de direccion IN_M1 estara en HIGH. El otro pin de direccion estara en LOW internamente.
      digitalWrite(IN_M2, HIGH);  // El pin de direccion IN_M2 estara en HIGH. El otro pin de direccion estara en LOW internamente.
    }
    else if (inCNY2 < 350 && inCNY3 >= 350) {
      // Si el robot se encuentra en el PASO 3 (seguir el circuito) y se desvía a la dcha, reducimos velocidad del motor dcho.

      digitalWrite(SLP_M, HIGH);  // Despertamos el motor.
      analogWrite(M1, 20);        // Establecemos la velocidad de giro (valor entre 0-255).
      analogWrite(M2, 30);        // Establecemos la velocidad de giro (valor entre 0-255).

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente.
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente.
    }
    else if (inCNY2 >= 350 && inCNY3 < 350) {
      // Si el robot se encuentra en el PASO 3 (seguir el circuito) y se desvía a la izqda, reducimos velocidad del motor izqdo.

      digitalWrite(SLP_M, HIGH);  // Despertamos el motor.
      analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255).
      analogWrite(M2, 15);        // Establecemos la velocidad de giro (valor entre 0-255).

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente.
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente.
    }
    else {
      // Si el robot se encuentra en el PASO 3 (seguir el circuito) y se mantiene en la línea, avanzamos.
      // Movemos el motor en un sentido de giro
      digitalWrite(SLP_M, HIGH);  // Despertamos el motor
      analogWrite(M1, 30);        // Establecemos la velocidad de giro (valor entre 0-255).
      analogWrite(M2, 30);        // Establecemos la velocidad de giro (valor entre 0-255).

      // Establecemos sentido de giro
      digitalWrite(IN_M1, LOW);  // El pin de direccion IN_M1 estara en LOW. El otro pin de direccion estara en HIGH internamente.
      digitalWrite(IN_M2, LOW);  // El pin de direccion IN_M2 estara en LOW. El otro pin de direccion estara en HIGH internamente.
    }
  }
}