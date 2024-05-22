//https://github.com/cgxeiji/CGx-InverseK

/***
 * @file Cinematica_INV.ino
 * @brief Programa basado en la librería CGx-InverseK para el control de un brazo robótico Braccio.
 * 
 * @author Javier Lopez
 * @author Rafael Lopez
 * @author Cesar Cruz
 * @date 2024-05-22
*/

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

// Variable que almacena el número de veces que se ha ejecutado el bucle principal.
// Requiere descomentar el código pertinente en la función loop para que funcione.
// int bucle = 0;

// Define los pines para el sensor de Color.
#define S0 0   // D3
#define S1 1   // D4
#define S2 2   // D5
#define S3 4   // D6
#define OUT 7 // D2

// Variables para llevar recuento de cubos por colores para apilarlos correctamente.
int cubosRojos = 0;   // Contador de cubos rojos.
int cubosBlancos = 0; // Contador de cubos blancos.
int cubosNegros = 0;  // Contador de cubos negros.

// Define los servos.
Servo barrera;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// Enumerado para identificar los colores.
enum color {
  VACIO,  // == 0
  ROJO,   // == 1
  BLANCO, // == 2
  NEGRO   // == 3
};

/**
 * @brief Inicialización del programa de Arduino.
 * 
 */
void setup() {

  // Inicializar barrera.
  barrera.attach(8, 1000, 2000);  //Asignamos pin.
  barrera.write(0); // El programa inicia con la barrera bajada.

  // Inicializar pines del sensor de color
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  // Preparar los elementos del Braccio para usar con CGx-InverseK
  Link base1;
  Link upperarm;
  Link forearm;
  Link hand;
  Serial.begin(9600);
  Braccio.begin();

  base1.init(0, b2a(0.0), b2a(180.0));
  upperarm.init(125, b2a(15.0), b2a(175.0));
  forearm.init(125, b2a(0.0), b2a(180.0));
  hand.init(190, b2a(0.0), b2a(180.0));

  InverseK.attach(base1, upperarm, forearm, hand);

  
  Serial.println("INIT POSITION"); // Mensaje de depuración para indicar el fin del setup.
  resetArm(); // Colocar el brazo en posición vertical.
}

/**
 * @brief Función de Arduino que se ejecuta en bucle con los pasos del Braccio, sensor de color y barrera.
 * Aquí se puede observar el funcionamiento del programa "paso a paso".
 * 
 */
void loop() {

  // PASO 1: Tomar el cubo de la zona de recogida y llevarlo al sensor de color.
  // Después, comprobar el color.
  comprobarCubo(); // Mover el cubo a la zona del sensor de color.
  delay(1000);
  color c = VACIO; // Inicializar el color a VACIO.
  c = leerColor(); // Leer el color del cubo.
  Serial.print("Color: ");
  Serial.println(c);
  delay(1000);

  // PASO 2: Llevar el cubo a la zona de carga y montarlo en el robot siguelíneas.
  // Después, usar la barrera para enviar el color al robot siguelíneas.
  cargarCubo(); // Mover el cubo a la zona de carga del robot siguelíneas
  delay(1000);
  enviarColor(c); // Enviar el color al robot siguelíneas.
  resetArm();  // Colocar el brazo en posición vertical.
  delay(4000); 

  // PASO 3: Levantar la barrera y esperar un tiempo para que el robot siguelíneas complete el circuito.
  barrera.write(180);  // Subir
  delay(70000);
  barrera.write(0);  // Bajar


  // PASO 4: Descargar el cubo desde la zona de descarga correspondiente.
  // El ajuste del brazo se hará teniendo en cuenta el color del cubo.
  // Después se colocará el cubo en la zona de "almacenaje" correspondiente.
  switch(c) {
    case ROJO:
      descargarRojo();
      break;
    case BLANCO:
      descargarBlanco();
      break;
    case NEGRO:
      descargarNegro();
      break;
    default:
    break;
  }
  delay(2000);

  // RESET POSITION
  resetArm(); // Finalizamos colocando el brazo en posición vertical.

  Serial.println("END LOOP"); // Mensaje de depuración para señalar el fin del loop
  
  // Código no esencial pero útil para detener el loop (descomentar para utilizar):
  // Si solo queremos que funcione una vez
  // while (true){}
  // Si queremos que repita 4 veces (comentar opción anterior)
  // bucle += 1;
  // while (bucle > 3) {}
}

/**
 * @brief Función del paso 1. Tiene como objetivo tomar un cubo de la zona inicial 
 * y liberarlo dentro del sensor de color.
 * 
 * @note Debe hacerse notar que el brazo utilizado tenía intercambiados entre sí los ejes X e Y.
 *
 * @see moveArm()
 */
void comprobarCubo() {
  // Orientar el brazo en la primera zona y sobre el cubo
  moveArm(0, -170, 100, 0, 10);

  // Agarrar el primer cubo
  moveArm(0, -170, -55, 0, 10);
  moveArm(0, -170, -55, 0, 45);

  // Elevar brazo con cubo
  moveArm(0, -170, 100, 0, 45);

  // Mover el cubo sobre el sensor de color
  moveArm(200, -70, 100, 74, 45);

  // Orientar muñeca y colocar cubo dentro del sensor de color
  moveArm(202, -90, 0, 70, 45);
  moveArm(202, -90, 0, 70, 10);

  // Elevar brazo sin cubo (para evitar lecturas anómalas del sensor de color)
  moveArm(202, -85, 100, 70, 10);
}

/**
 * @brief Mueve el cubo de la zona de color al vehículo situado en la parada de carga.
 * 
 * @note Debe hacerse notar que el brazo utilizado tenía intercambiados entre sí los ejes X e Y.
 * 
 * @see moveArm()
 */
void cargarCubo() {
  // Orientar muñeca y recoger cubo del sensor de color.
  moveArm(202, -85, -8, 76, 10);
  moveArm(202, -85, -8, 76, 45);

  // Elevar brazo con el cubo.
  moveArm(202, -70, 100, 74, 45);

  // Maniobra de giro de la zona del sensor de color a la zona de carga.
  // Se hace así para evitar colisiones con la barrera en el caso de que esta se pusiera vertical.
  moveArm(130, -78, 100, 74, 45);  // Retraer brazo para la maniobra de giro y evitar colisiones.
  moveArm(0, 170, 100, 74, 45);   // Maniobra de giro hacia la zona de carga (girar brazo).

  // Posicionar el brazo en la zona de carga, sobre el vehículo.
  moveArm(100, 180, 100, 45, 45);

  // Bajar el brazo en la zona de carga del vehículo.
  moveArm(100, 180, 40, 45, 45);
  moveArm(100, 180, 40, 45, 10);

  // Elevar el brazo para evitar colisiones con el vehículo.
  moveArm(100, 180, 100, 45, 10);
}

/**
 * @brief Toma el cubo desde el vehículo en la parada Roja y lo coloca en la zona de almacenaje
 * correspondiente al cubo Rojo. Se considera que no va a haber más de dos cubos Rojos.
 * 
 * @note Debe hacerse notar que el brazo utilizado tenía intercambiados entre sí los ejes X e Y.
 * 
 * @see moveArm()
 */
void descargarRojo() {
  Serial.println("MOVER_ROJO");
  // Orientar el brazo en la zona de recogida de cubos Rojos.
  moveArm(15, 170, 60, 90, 10);
  
  // Bajar el brazo para recoger el cubo Rojo.
  moveArm(15, 170, 45, 90, 10);
  moveArm(15, 170, 45, 90, 47);
  
  // Elevar el brazo con el cubo Rojo.
  moveArm(15, 170, 100, 90, 47);
  
  // Mover el brazo a la zona de almacenaje de cubos Rojos.
  moveArm(135, 15, 100, 90, 47);
  // Soltar el cubo Rojo en la zona de almacenaje.
  if (cubosRojos == 0) { 
    // Si no hay cubos Rojos en la zona de almacenaje.
    moveArm(135, 15, -52, 90, 47); // se coloca directamente en el suelo.
    moveArm(135, 15, -52, 90, 10);
    cubosRojos++; // Se incrementa el contador de cubos Rojos.
  } else { 
    // Si ya hay un cubo Rojo en la zona de almacenaje.
    moveArm(135, 15, -22, 90, 47); // se coloca sobre el cubo existente.
    moveArm(135, 15, -22, 90, 10);
  }
  
  // Elevar el brazo para evitar colisiones con el entorno.
  moveArm(135, 15, 100, 90, 10);
}

/**
 * @brief Toma el cubo desde el vehículo en la parada Blanca y lo coloca en la zona de almacenaje
 * correspondiente al cubo Blanco. Se considera que no va a haber más de dos cubos Blancos.
 * 
 * @note Debe hacerse notar que el brazo utilizado tenía intercambiados entre sí los ejes X e Y.
 * 
 * @see moveArm()
 */
void descargarBlanco() {
  Serial.println("MOVER_BLANCO");
  // Debido a las limitaciones en las articulaciones del brazo, se hace una maniobra de giro.
  resetArm(); // Colocar el brazo en posición vertical.

  // Orientar el brazo en la zona de recogida de cubos Blancos.
  moveArm(-15, 145, 60, 90, 10);

  // Bajar el brazo para recoger el cubo Blanco.
  moveArm(-15, 145, 20, 90, 10);
  moveArm(-15, 145, 20, 90, 47);

  // Elevar el brazo con el cubo Blanco.
  moveArm(-15, 145, 100, 90, 47);

  // Mover el brazo a la zona de almacenaje de cubos Blancos.
  moveArm(170, 15, 100, 90, 47);

  // Soltar el cubo Blanco en la zona de almacenaje.
  if (cubosBlancos == 0) {
    // Si no hay cubos Blancos en la zona de almacenaje.
    moveArm(170, 15, -52, 90, 47); // se coloca directamente en el suelo.
    moveArm(170, 15, -52, 90, 10);
    cubosBlancos++; // Se incrementa el contador de cubos Blancos.
  } else {
    // Si ya hay un cubo Blanco en la zona de almacenaje.
    moveArm(170, 15, -22, 90, 47); // se coloca sobre el cubo existente.
    moveArm(170, 15, -22, 90, 10);
  }

  // Elevar el brazo para evitar colisiones con el entorno.
  moveArm(170, 15, 100, 90, 10);
}

/**
 * @brief Toma el cubo desde el vehículo en la parada Negra y lo coloca en la zona de almacenaje
 * correspondiente al cubo Negro. Se considera que no va a haber más de dos cubos Negro.
 * 
 * @note Debe hacerse notar que el brazo utilizado tenía intercambiados entre sí los ejes X e Y.
 * 
 * @see moveArm()
 */
void descargarNegro() {
  Serial.println("MOVER_NEGRO");

  // Debido a las limitaciones en las articulaciones del brazo, se hace una maniobra de giro.
  resetArm(); // Colocar el brazo en posición vertical.

  // Orientar el brazo en la zona de recogida de cubos Negros.
  moveArm(-15, 150, 60, 90, 10);

  // Bajar el brazo para recoger el cubo Negro.
  moveArm(-15, 150, 10, 90, 10);
  moveArm(-15, 150, 10, 90, 47);

  // Elevar el brazo con el cubo Negro.
  moveArm(-15, 150, 100, 90, 47);

  // Mover el brazo a la zona de almacenaje de cubos Negros.
  moveArm(205, 15, 100, 90, 47);

  // Soltar el cubo Negro en la zona de almacenaje.
  if (cubosNegros == 0) {
    // Si no hay cubos Negro en la zona de almacenaje.
    moveArm(205, 15, -52, 90, 47); // se coloca directamente en el suelo.
    moveArm(205, 15, -52, 90, 10);
    cubosNegros++; // Se incrementa el contador de cubos Negro.
  } else {
    // Si ya hay un cubo Negro en la zona de almacenaje.
    moveArm(205, 15, -22, 90, 47); // se coloca sobre el cubo existente.
    moveArm(205, 15, -22, 90, 10);
  }

  // Elevar el brazo para evitar colisiones con el entorno.
  moveArm(205, 15, 100, 90, 10);
}

/**
 * @brief Función que dado un color c, mueve la barrera para indicárselo al robot siguelíneas.
 * @note - Para el color Rojo la barrera se mantiene levantada ~1s.
 * @note - Para el color Blanco la barrera se mantiene levantada ~2s.
 * @note - Para el color Negro la barrera se mantiene levantada ~3s.
 * 
 * @param c Enumerado que identifica el color que se debe transmitir.
 */
void enviarColor(color c) {
  barrera.write(180);  // Subir la barrera.

  switch (c) {
  case ROJO: // Si el color es rojo, se mantiene la barrera subida 1 segundo.
    delay(1000);
    break;
  case BLANCO: // Si el color es blanco, se mantiene la barrera 1700ms 
               // más el tiempo de subir y bajar la barrera = ~2 segundos.
    delay(1700);
    break;
  case NEGRO: // Si el color es negro, se mantiene la barrera 3 segundos.
    delay(3000);
    break;

  default:
    break;
  }

  barrera.write(0);  // Bajar la barrera.
}

// Función original de CGx-InverseK
// Quick conversion from the Braccio angle system to radians
float b2a(float b) {
  return b / 180.0 * PI - HALF_PI;
}

// Función original de CGx-InverseK
// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}

/**
 * @brief Recibe los valores 0-255 de los sensores R, G ó B del sensor de color. Se define el sensor
 * a utilizar variando el estado de los pines S2 y S3.
 * 
 * @param s2 Estado LOW/HIGH del pin S2.
 * @param s3 Estado LOW/HIGH del pin S3.
 * @return byte - Lectura en bruto del sensor seleccionado.
 */
byte readColorFrequency(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(10);
  return pulseIn(OUT, LOW);
}

/**
 * @brief Función que toma los valores RGB que recibe el sensor de color 
 * y devuelve el color que se corresponde.
 * 
 * @return color - Enumerado que identifica el color detectado.
 * 
 * @related readColorFrequency()
 */
color leerColor() {
  color c = VACIO; // Inicializar el color a VACIO.

  // Bucle para leer el color hasta que se detecte uno.
  while (c == VACIO) {
    // Leer los valores RGB del sensor de color.
    byte red = readColorFrequency(LOW, LOW);      // Rojo
    byte green = readColorFrequency(HIGH, HIGH);  // Verde
    byte blue = readColorFrequency(LOW, HIGH);    // Azul

    // Imprimir los valores RGB por el puerto serie para depuración.
    Serial.print("Rojo: ");
    Serial.println(red);
    Serial.print("Verde: ");
    Serial.println(green);
    Serial.print("Azul: ");
    Serial.println(blue);

    delay(1000);  // Retardo entre mediciones.

    // Lectura del potenciómetro
    int Pot = analogRead(A0);

    // Imprimir por el puerto serie el valor del potenciómetro.
    Serial.print("Pot: ");
    Serial.print(Pot);

    // Determinar el color en función de los valores RGB.
    if (red < 5 && red < blue && red < green && green > 7 && blue > 7) {  // Valores RGB estimados para el color rojo.
      c = ROJO;
    } else if (red < 20 && green > 20 && blue > 15) {  // Valores RGB estimados para el color negro.
      c = NEGRO;
    } else if (red < 7 && green < 7 && blue < 7) {  // Valores estimados para el color blanco.
      c = BLANCO;
    } else {
      Serial.println("VACIO"); // Si no se reconoce un color se imprime "VACIO" y se repite el bucle.
    }
  }

  // Devolvemos el color resultante.
  return c;
}

/**
 * @brief Función genérica que mueve el brazo a la posición x,y,z mediante cinemática inversa.
 * 
 * @param x movimiento en eje X.
 * @param y movimiento en eje Y.
 * @param z movimiento en eje Z.
 * @param m rotación de muñeca.
 * @param p movimiento de pinza.
 * 
 * @note Si no encuentra solución, se pone en vertical.
 */
void moveArm(int x, int y, int z, int m, int p) {
  float b0, b1, b2, b3;
  if (InverseK.solve(x, y, z, b0, b1, b2, b3)) {
    Serial.println("-move arm-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), m, p);
  }
  else {
    Serial.println("No solution found!");
    resetArm();
  }
  delay(1000);
}

/**
 * @brief Función que coloca el brazo en posición vertical usando cinemática inversa.
 * 
 * @note Si no encuentra solución, notifica que no se ha encontrado solución y no hace nada más.
 */
void resetArm() {
  float a0, a1, a2, a3;
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
  if (InverseK.solve(0, 0, 505 - 75, a0, a1, a2, a3)) {
    Serial.println("-0-");
    Serial.print(a2b(a0));
    Serial.print(',');
    Serial.print(a2b(a1));
    Serial.print(',');
    Serial.print(a2b(a2));
    Serial.print(',');
    Serial.println(a2b(a3));
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  else {
    Serial.println("No solution found!");
  }
  delay(1000);
}