#include <math.h>
#include <Braccio.h>
#include <Servo.h>

#define PI 3.1415926535897932384626433832795

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// Definimos las longitudes del robot
float L1 = .065;
float L2 = .125;
float L3 = L2;
float L5 = .19;

double correctionq2 = 25;
// double correctionq2 = 1;
double correctionq3 = 10;
// double correctionq3 = 1;

void setup() {
  Serial.begin(9600);
  Braccio.begin();
}

//TODO
// COGER LA FUNCIÓN IKINE DEL EJERCICIO 1
void ikine(float p[3], float q[6]) {
  // Calculamos el punto del extremo del robot simplificado de 3 GDL
  float v[2];
  float x, y, z;
  v[0] = L5 * p[0] / sqrt(p[0] * p[0] + p[1] * p[1]);
  v[1] = L5 * p[1] / sqrt(p[0] * p[0] + p[1] * p[1]);
  x = p[0] - v[0];
  y = p[1] - v[1];
  z = p[2] - L1;

  // TODO
  // Calculamos q_1
  q[0] = atan2(y, x);

  // TODO
  // Calculamos q_3
  float cos_q3, sin_q3;
  float p2 = x * x + y * y + z * z;
  cos_q3 = -(L2 * L2 + L3 * L3 - p2) / (2 * L2 * L3);
  sin_q3 = -sqrt(1 - cos_q3 * cos_q3);
  q[2] = atan2(sin_q3, cos_q3);

  // TODO
  // Calculamos q_2
  float alpha, beta;
  beta = atan2(z, sqrt(x * x + y * y));
  alpha = atan2(L3 * sin(q[2]), L2 + L3 * cos(q[2]));
  q[1] = beta - alpha + (correctionq2*PI/180);

  // Ajustamos q_3 para el rango de movimiento de nuestro robot
  q[2] = PI / 2 + q[2] + (correctionq3*PI/180);

  // Definimos q_4 para que el efector final esté siempre paralelo al suelo
  q[3] = -(q[1] + q[2]) + PI;

  // pasamos los ángulos a grados
  for (int i = 0; i < 3; i++)
    q[i] = q[i] * 180 / PI;
  
  //Imprimimos valores
  print_q(q);
}


void print_q(float *q) {
  Serial.println("----------");
  for (int i = 0; i < 6; i++) {
    Serial.print("q");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(q[i]);
  }
  Serial.println("----------");
}

void loop() {
  char comando = 0;
  float q[6] = { 0, 90, 90, 90, 0, 50 };
  
  // DESPL EN X/Y/Z RESPECTO DE BASE!!!!!!
  // Imagina que la base está en el origen de coordenadas [0,0,0]
  // y el extremo del robot se desplaza respecto de la base
  // float pos_1[3] = { .3, .25, .1 };
  float pos_1[3] = { .3, 0, .2348 }; // .3 == 30cm, etc
  float pos_2[3] = { -.26, .28, .15 };
  float pos_test[3] = { 1.250, -.1, 0 };
  float q_reposo[6] = { 0, 90, 90, 90, 0, 43 };

  // TODO
  // Definir el valor de la pinza para que al cerrar coja la pieza
  float valor_cierre = 50;

  // Ponemos el robot en posición de reposo inicial
  Braccio.ServoMovement(20, q_reposo[0], q_reposo[1], q_reposo[2], q_reposo[3], q_reposo[4], q_reposo[5]);
  

  if (Serial.available() > 0) {
    comando = Serial.read();

    if (comando == '1') {
      //TODO
      // Secuencia para mover la pieza de pos_1 a pos_2 y volver a posición de reposo inicial
      pos_1[2] += .05;
      ikine(pos_1, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 10);
      delay(100);
      pos_1[2] -= .05;
      ikine(pos_1, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 10);
      delay(100);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], valor_cierre);
      delay(100);

      ikine(pos_2, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], valor_cierre);
      delay(100);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 10);
      delay(100);
      pos_2[2] += .05;
      ikine(pos_2, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 10);
      delay(100);
      Braccio.ServoMovement(20, q_reposo[0], q_reposo[1], q_reposo[2], q_reposo[3], q_reposo[4], q_reposo[5]);
      delay(1000);
    } else if (comando == '2') {
      //TODO
      // Secuencia para mover la pieza de pos_1 a pos_2 y volver a posición de reposo inicial
      pos_2[2] += .05;
      ikine(pos_2, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 73);
      delay(100);
      pos_2[2] -= .05;
      ikine(pos_2, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 73);
      delay(100);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], valor_cierre);
      delay(100);

      ikine(pos_1, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], valor_cierre);
      delay(100);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 73);
      delay(100);
      pos_1[2] += .05;
      ikine(pos_1, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], 73);
      delay(100);
      Braccio.ServoMovement(20, q_reposo[0], q_reposo[1], q_reposo[2], q_reposo[3], q_reposo[4], q_reposo[5]);
      delay(1000);
    } else if (comando == '3') {
      delay(1000);
      ikine(pos_test, q);
      Braccio.ServoMovement(20, q[0], q[1], q[2], q[3], q[4], q[5]);
    }

    delay(20);
  }
  // Serial.println(comando);

  //print_q(q);
}
