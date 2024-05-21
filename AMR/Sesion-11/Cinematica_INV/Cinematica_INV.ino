//https://github.com/cgxeiji/CGx-InverseK

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

int bucle = 0;

// Define los pines para el sensor CNY70
#define S0 0   // D3
#define S1 1   // D4
#define S2 2   // D5
#define S3 4   // D6
#define OUT 7 // D2
// Define variables globales para el sensor CNY70
byte countRed = 0;
byte countGreen = 0;
byte countBlue = 0;
int Pot = 0;

int cubosRojos = 0;
int cubosBlancos = 0;
int cubosNegros = 0;

// Define los pines para el sensor CNY70 (deprecated)
// const int s0 = 3;
// const int s1 = 4;
// const int s2 = 5;
// const int s3 = 6;
// const int OUT = 2;


// inicialización de entradas y salidas

// Define los servos
Servo barrera;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

enum color {
  VACIO,
  ROJO,
  BLANCO,
  NEGRO
};


void setup() {

  // Init barrera
  barrera.attach(8, 1000, 2000);  //Set the pin to attach the servo
  barrera.write(0);

  // Init CNY70
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  // Setup the lengths and rotation limits for each link
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

  // Attach the links to the inverse kinematic model
  InverseK.attach(base1, upperarm, forearm, hand);

  // InverseK.solve() return true if it could find a solution and false if not.
  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
  Serial.println("INIT POSITION");
  resetArm();
}

void loop() {

  comprobarCubo();
  delay(1000);
  color c = VACIO;
  c = leerColor();
  // color c = 3;
  delay(1000);

  cargarCubo();
  delay(2000);
  enviarColor(c);
  resetArm();

  delay(4000);

  barrera.write(180);  // Subir
  delay(5000);
  barrera.write(0);  // Bajar

  // delay(100000);
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
  delay(3000);

  // RESET POSITION
  resetArm();
  
  // Si solo queremos que funcione una vez
  while (true){}

  // Si queremos que repita 3 veces (comentar opción anterior)
  bucle += 1;
  while (bucle > 3) {}
}

// @brief Mueve el cubo de la zona de recogida al sensor de color
void comprobarCubo() {

  // Orientar el brazo en la primera zona y sobre el cubo
  moveArm(0, -170, 100, 0, 10);

  // Agarrar el primer cubo
  moveArm(0, -170, -55, 0, 10);
  moveArm(0, -170, -55, 0, 45);

  // Elevar brazo con cubo
  moveArm(0, -170, 100, 0, 45);

  // Mover el cubo sobre el CNY
  moveArm(200, -70, 100, 74, 45);

  // Orientar muñeca y colocar cubo
  moveArm(202, -90, 0, 70, 45);
  moveArm(202, -90, 0, 70, 10);

  // Soltar cubo
  /* Hay que soltar y elevar? */
  moveArm(202, -85, 100, 70, 10);
}

// @brief Mueve el cubo de la zona de color al vehículo en parada de carga
void cargarCubo() {

  // Orientar muñeca y recoger cubo
  moveArm(202, -85, -8, 76, 10);
  moveArm(202, -85, -8, 76, 45);

  // Elevar brazo con cubo
  moveArm(202, -70, 100, 74, 45);

  // Maniobra de giro hacia la zona de carga (retraer brazo)
  moveArm(130, -78, 100, 74, 45);
  
  // Maniobra de giro hacia la zona de carga (girar brazo)
  moveArm(0, 170, 100, 74, 45);

  // Posicionar el brazo en la zona de carga
  moveArm(95, 180, 100, 74, 45);

  // Bajar el brazo en la zona de carga
  // TODO: Ajustar la altura de la zona de carga y verificar posición del coche
  moveArm(95, 180, 40, 74, 45);
  moveArm(95, 180, 40, 74, 10);
  moveArm(95, 180, 100, 74, 10);
}
void descargarRojo() {
  Serial.println("MOVER_ROJO");
  moveArm(5, 170, 60, 70, 10);
  moveArm(5, 170, 40, 70, 10);
  moveArm(5, 170, 40, 70, 45);
  moveArm(5, 170, 100, 70, 45);
  moveArm(140, 15, 100, 90, 45);
  if (cubosRojos == 0) {
    moveArm(140, 15, -52, 90, 45);
    moveArm(140, 15, -52, 90, 10);
    cubosRojos++;
  } else {
    moveArm(140, 15, -22, 90, 45);
    moveArm(140, 15, -22, 90, 10);
  }
  moveArm(140, 15, 100, 90, 10);
}
void descargarBlanco() {
  Serial.println("MOVER_BLANCO");
  resetArm();
  moveArm(-5, 155, 60, 70, 10);
  moveArm(-5, 155, 10, 70, 10);
  moveArm(-5, 155, 10, 70, 45);
  moveArm(-5, 155, 100, 70, 45);
  moveArm(170, 15, 100, 90, 45);
  if (cubosBlancos == 0) {
    moveArm(170, 15, -52, 90, 45);
    moveArm(170, 15, -52, 90, 10);
    cubosBlancos++;
  } else {
    moveArm(170, 15, -22, 90, 45);
    moveArm(170, 15, -22, 90, 10);
  }
  moveArm(170, 15, 100, 90, 10);
}
void descargarNegro() {
  Serial.println("MOVER_NEGRO");
  resetArm();
  moveArm(-25, 160, 60, 90, 10);
  moveArm(-25, 160, 5, 90, 10);
  moveArm(-25, 160, 5, 90, 45);
  moveArm(-25, 160, 100, 90, 45);
  moveArm(202, 15, 100, 90, 45);
  if (cubosNegros == 0) {
    moveArm(202, 15, -52, 90, 45);
    moveArm(202, 15, -52, 90, 10);
    cubosNegros++;
  } else {
    moveArm(202, 15, -22, 90, 45);
    moveArm(202, 15, -22, 90, 10);
  }
  moveArm(202, 15, 100, 90, 10);
}

// @note En lugar de subir y bajar la barrera varias veces,
// mejor subir la barrera, esperar X segundos y bajar.
color enviarColor(color c) {
  switch (c) {
  case ROJO:
    moverBarrera();
    break;
  case BLANCO:
    moverBarrera();
    moverBarrera();
    break;
  case NEGRO:
    moverBarrera();
    moverBarrera();
    moverBarrera();
    break;

  default:
    break;
  }
}

void moverBarrera() {
  barrera.write(180);  // Subir
  delay(1000);
  barrera.write(0);  // Bajar
  delay(1000);
}


// Quick conversion from the Braccio angle system to radians
float b2a(float b) {
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}

//@brief Recibe los valores 0-255 de los sensores del CNY70
byte readColorFrequency(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(10);
  return pulseIn(OUT, LOW);
}

// @brief Llama a recibirColor() e interpreta el valor recibido, devolviendo el color resultante
color leerColor() {
  color c = VACIO;
  while (c == VACIO) {
    byte red = readColorFrequency(LOW, LOW);      // Rojo
    byte green = readColorFrequency(HIGH, HIGH);  // Verde
    byte blue = readColorFrequency(LOW, HIGH);    // Azul

    Serial.print("Rojo: ");
    Serial.println(red);
    Serial.print("Verde: ");
    Serial.println(green);
    Serial.print("Azul: ");
    Serial.println(blue);

    // String color = determineColor(red, green, blue);
    // Serial.print("Color detectado: ");
    // Serial.println(color);

    delay(1000);  // Retardo entre mediciones

    //Función de tomar color
    // recibirColor();
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
    if (red < 5 && red < blue && red < green && green > 7 && blue > 7) {  // Ajusta estos valores basados en tus pruebas
      c = ROJO;
    } else if (red < 20 && green > 20 && blue > 15) {  // Ajusta estos valores basados en tus pruebas
      c = NEGRO;
    } else if (red < 7 && green < 7 && blue < 7) {  // Ajusta estos valores basados en tus pruebas
      c = BLANCO;
    } else {
      Serial.println("VACIO");
    }

  }
    return c;
}

// @brief Función genérica que mueve el brazo a la posición x,y,z mediante cinemática inversa.
// @param x movimiento en eje X.
// @param y movimiento en eje Y.
// @param z movimiento en eje Z.
// @param m rotación de muñeca.
// @param p movimiento de pinza.
// @note Si no encuentra solución, se pone en vertical.
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

// @brief Función que pone el brazo casi en vertical, usando Cinemática Inversa.
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