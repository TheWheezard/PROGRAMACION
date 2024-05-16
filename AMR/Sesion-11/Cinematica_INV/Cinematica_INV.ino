//https://github.com/cgxeiji/CGx-InverseK

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

// Define los pines para el sensor CNY70
#define S0 0   // D3
#define S1 1   // D4
#define S2 2   // D5
#define S3 4   // D6
#define OUT 10 // D2
// Define variables globales para el sensor CNY70
byte countRed = 0;
byte countGreen = 0;
byte countBlue = 0;
int Pot = 0;

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
  // pinMode(S0, OUTPUT);
  // pinMode(S1, OUTPUT);
  // pinMode(S2, OUTPUT);
  // pinMode(S3, OUTPUT);
  // pinMode(OUT, INPUT);
  // digitalWrite(S0, HIGH);
  // digitalWrite(S1, HIGH);

  // Setup the lengths and rotation limits for each link
  Link base1;
  Link upperarm;
  Link forearm;
  Link hand;
  Serial.begin(9600);
  Braccio.begin();

  base1.init(0, b2a(0.0), b2a(180.0));
  upperarm.init(125, b2a(15.0), b2a(165.0));
  forearm.init(125, b2a(0.0), b2a(180.0));
  hand.init(190, b2a(0.0), b2a(180.0));

  // Attach the links to the inverse kinematic model
  InverseK.attach(base1, upperarm, forearm, hand);

  // InverseK.solve() return true if it could find a solution and false if not.
  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
  Serial.println("INIT POSITION");
  resetArm();
  /*
  // Calculates the angles considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3, phi)
  if(InverseK.solve(550, 0, 50, a0, a1, a2, a3, b2a(90.0))) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
    Serial.println("No solution found!");
  }
  */
}

void loop() {

  comprobarCubo();
  delay(1000);
  // color c = leerColor();
  color c = 3;
  delay(1000);

  cargarCubo();
  enviarColor(c);

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
  delay(8000);

  // RESET POSITION
  resetArm();
  while (true) {}
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
  moveArm(200, -72, 100, 74, 45);

  // Orientar muñeca y colocar cubo
  moveArm(202, -68, 0, 76, 45);
  moveArm(202, -68, 0, 76, 10);

  // Soltar cubo
  /* Hay que soltar y elevar? */
  moveArm(202, -68, 100, 76, 10);
  // if(InverseK.solve(200, -61, 100, b0, b1, b2, b3)) {
  //   Serial.println("-1c-");
  //   Serial.print(a2b(b0)); Serial.print(',');
  //   Serial.print(a2b(b1)); Serial.print(',');
  //   Serial.print(a2b(b2)); Serial.print(',');
  //   Serial.println(a2b(b3));
  //   Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 10);
  // } else {
  //   Serial.println("No solution found! -1c-");
  //   Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  // }
  //delay(6000);
}

// @brief Mueve el cubo de la zona de color al vehículo en parada de carga
void cargarCubo() {

  // Orientar muñeca y recoger cubo
  moveArm(202, -68, -8, 76, 10);
  moveArm(202, -68, -8, 76, 45);

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
  moveArm(5, 170, 60, 74, 10);
  moveArm(5, 170, 40, 74, 10);
  moveArm(5, 170, 40, 74, 45);
  moveArm(5, 170, 100, 74, 45);
  moveArm(202, 15, 100, 76, 45);
  moveArm(202, 15, -54, 76, 45);
  moveArm(202, 15, -54, 76, 10);
}
void descargarBlanco() {
  Serial.println("MOVER_BLANCO");
  resetArm();
  moveArm(-5, 160, 60, 74, 10);
  moveArm(-5, 160, 15, 74, 10);
  moveArm(-5, 160, 15, 74, 45);
  moveArm(-5, 160, 100, 74, 45);
  moveArm(202, 35, 100, 76, 45);
  moveArm(202, 35, -54, 76, 45);
  moveArm(202, 35, -54, 76, 10);
}
void descargarNegro() {
  Serial.println("MOVER_NEGRO");
  resetArm();
  moveArm(-25, 160, 60, 90, 10);
  moveArm(-25, 160, 5, 90, 10);
  moveArm(-25, 160, 5, 90, 45);
  moveArm(-25, 160, 100, 90, 45);
  moveArm(202, 45, 100, 76, 45);
  moveArm(202, 45, -54, 76, 45);
  moveArm(202, 45, -54, 76, 10);
}
void descargarAzul() {}

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
  delay(2000);
  barrera.write(0);  // Bajar
  delay(2000);
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
void recibirColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  countRed = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
  digitalWrite(S3, HIGH);
  countBlue = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
  digitalWrite(S2, HIGH);
  countGreen = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);
}

// @brief Llama a recibirColor() e interpreta el valor recibido, devolviendo el color resultante
color leerColor() {
  color c = VACIO;
  while (c == VACIO) {
    //Función de tomar color 
    recibirColor();
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
    if (countRed > 9 && countRed < 15 && countGreen > 15 && countGreen < 20 && countBlue > 6 && countBlue < 15) {
        Serial.println(" ‐ Color Blanco");
        c = BLANCO;
    }
    else if (countRed > 13 && countRed < 20 && countGreen > 65 && countGreen < 75 && countBlue > 50 && countBlue < 60) {
        Serial.println(" ‐ Color Rojo");
        c = ROJO;
    }
    else if (countRed > 30 && countRed < 45 && countGreen > 140 && countGreen < 180 && countBlue > 120 && countBlue < 140) {
        Serial.println(" ‐ Color Negro");
        c = NEGRO;
    }
    else {
      Serial.println("‐ VACIO");
    }
    delay(1000);
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