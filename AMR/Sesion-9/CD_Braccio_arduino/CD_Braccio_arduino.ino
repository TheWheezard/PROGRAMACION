#include <Braccio.h>
#include <MatrixMath.h>
#include <Servo.h>
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
double r1 = 0;
double r2 = 0;
double r3 = 180;
double r4 = 0;
double r5 = 0;

double q1 = r1 * PI / 180.0;
double q2 = r2 * PI / 180.0;
double q3 = r3 * PI / 180.0;
double q4 = r4 * PI / 180.0;
double q5 = r5 * PI / 180.0;

// double x_3 = PI/2;
// double x_4 = 0;

double L1 = 6.5;
double L2 = 12.5;
double L3 = 12.5;
double L5 = 19.0;


mtx_type A[4][4] = { { cos(q1), 0, sin(q1), 0 }, { 0, sin(q1), 0, -cos(q1) }, { 0, 1, 0, L1 }, { 0, 0, 0, 1 } };
mtx_type B[4][4] = { { cos(q2), sin(q2), 0, L2* cos(q2) }, { sin(q2), -cos(q2), 0, L2* sin(q2) }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
mtx_type C[4][4] = { { cos(q3 - PI / 2), sin(q3 - PI / 2), 0, L3* cos(q3 - PI / 2) }, { sin(q3 - PI / 2), -cos(q3 - PI / 2), 0, L3* sin(q3 - PI / 2) }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
mtx_type D[4][4] = { { cos(q4), 0, sin(q4), 0 }, { sin(q4), 0, -cos(q4), 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
mtx_type E[4][4] = { { cos(q5), sin(q5), 0, 0 }, { sin(q5), cos(q5), 0, 0 }, { 0, 0, 1, L5 }, { 0, 0, 0, 1 } };

mtx_type T1[4][4];
mtx_type T2[4][4];
mtx_type T3[4][4];
mtx_type T[4][4];
void setup() {
  Serial.begin(9600);
  Braccio.begin();
}

void loop() {
  

  // Braccio.ServoMovement(20, r1, r2, r3, r4, r5, 43); // Todo neutral
  Matrix.Print((mtx_type*)A, 4, 4, "A");
  Matrix.Print((mtx_type*)B, 4, 4, "B");
  Matrix.Print((mtx_type*)C, 4, 4, "C");
  Matrix.Print((mtx_type*)D, 4, 4, "D");
  Matrix.Print((mtx_type*)E, 4, 4, "E");

  Matrix.Multiply((mtx_type*)A, (mtx_type*)B, 4, 4, 4, (mtx_type*)T1);
  Matrix.Multiply((mtx_type*)T1, (mtx_type*)C, 4, 4, 4, (mtx_type*)T2);
  Matrix.Multiply((mtx_type*)T2, (mtx_type*)D, 4, 4, 4, (mtx_type*)T3);
  Matrix.Multiply((mtx_type*)T3, (mtx_type*)E, 4, 4, 4, (mtx_type*)T);


  Matrix.Print((mtx_type*)T, 4, 4, "T");
  while (1);
}

double degToRad(double degrees) {
    return degrees * PI / 180.0;
}