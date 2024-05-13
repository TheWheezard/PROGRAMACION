//https://github.com/cgxeiji/CGx-InverseK

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

enum color {VACIO, ROJO, BLANCO, NEGRO};

void setup() {
  
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

  float a0, a1, a2, a3;
  float b0, b1, b2, b3;

  // InverseK.solve() return true if it could find a solution and false if not.

  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
  if(InverseK.solve(0, 0, 505-75, a0, a1, a2, a3)) {
    Serial.println("-0-");
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  } else {
    Serial.println("No solution found!");
  }
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
  // delay(1000);
  // color c = leerColor();
  // delay(1000);
  // moverBarrera(c);

  // cargarCubo();
  // delay(100000);
  // switch(c) {
  //   case ROJO:
  //     descargarRojo();
  //     break;
  //   case BLANCO:
  //     descargarBlanco();
  //     break;
  //   case NEGRO:
  //     descargarNegro();
  //     break;

  //   default;
  // }
  delay(30000);

  float a0, a1, a2, a3;
  if(InverseK.solve(0, 0, 505-75, a0, a1, a2, a3)) {
    Serial.println("-0-");
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  } else {
    Serial.println("No solution found!");
  }
  while(true){}
}

// @brief Mueve el cubo de la zona de recogida al sensor de color
void comprobarCubo() {
  float a0, a1, a2, a3;
  float b0, b1, b2, b3;
  InverseK.solve(0, 0, 505-75, a0, a1, a2, a3);

  // Orientar el brazo en la primera zona y sobre el cubo
  if(InverseK.solve(0, -200, 100, b0, b1, b2, b3)) { // try -75 for Z
    Serial.println("-1a-");
    Serial.print(a2b(b0)); Serial.print(',');
    Serial.print(a2b(b1)); Serial.print(',');
    Serial.print(a2b(b2)); Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 10);
  } else {
    Serial.println("No solution found! -1a-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(6000);

  // Recoger el primer cubo
  if(InverseK.solve(0, -200, -2, b0, b1, b2, b3)) { // try -75 for Z
    Serial.println("-1b-");
    Serial.print(a2b(b0)); Serial.print(',');
    Serial.print(a2b(b1)); Serial.print(',');
    Serial.print(a2b(b2)); Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 10);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 45);
  } else {
    Serial.println("No solution found! -1b-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(6000);

  // Elevar
  if(InverseK.solve(0, -200, 100, b0, b1, b2, b3)) { // try -75 for Z
    Serial.println("-1a-");
    Serial.print(a2b(b0)); Serial.print(',');
    Serial.print(a2b(b1)); Serial.print(',');
    Serial.print(a2b(b2)); Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 45);
  } else {
    Serial.println("No solution found! -1a-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(6000);

  // Mover el cubo al CNY
  if(InverseK.solve(200, -50, 100, b0, b1, b2, b3)) { // try -75 for Z
    Serial.println("-1c-");
    Serial.print(a2b(b0)); Serial.print(',');
    Serial.print(a2b(b1)); Serial.print(',');
    Serial.print(a2b(b2)); Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 45);
    delay(2000);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 10);
  } else {
    Serial.println("No solution found! -1c-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(6000);
  /* Habría que orientar y bajar */

  // Soltar cubo
  /* Habría que soltar y elevar*/
  
}
// @brief Mueve el cubo de la zona de color al vehículo en parada de carga
void cargarCubo(){}
void descargarRojo(){}
void descargarBlanco(){}
void descargarNegro(){}
void descargarAzul(){}
color leerColor(){}
void moverBarrera(color c){}


// Quick conversion from the Braccio angle system to radians
float b2a(float b) {
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) {
  return (a + HALF_PI) * 180 / PI;
}
