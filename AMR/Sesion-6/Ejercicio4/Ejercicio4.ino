#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  Braccio.begin();

  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Todo neutral
  delay(1000);
}

void loop() {
  // Suponiendo que los cubos están alineados y accesibles a las mismas posiciones de base y codo pero a diferentes alturas.
  // Recoger el primer cubo
  Braccio.ServoMovement(30, 75, 115, 150, 177, 90, 10); // Acercarse al primer cubo
  delay(1000);
  Braccio.ServoMovement(20, 75, 115, 150, 177, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);
  Braccio.ServoMovement(20, 75, 20, 175, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);

  Braccio.ServoMovement(20, 90, 115, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);
  Braccio.ServoMovement(20, 90, 20, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);

  Braccio.ServoMovement(20, 105, 115, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);
  Braccio.ServoMovement(20, 105, 20, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);

  Braccio.ServoMovement(20, 115, 115, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);
  Braccio.ServoMovement(20, 115, 20, 150, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);
  //Braccio.ServoMovement(20, 80, 20, 175, 175, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);

  // // Poner brazo en neutral
  // Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 43); // Brazo neutral
  // delay(1000);
  // Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Base neutral
  // delay(1000);


  while(1); // Detener el loop para evitar que el programa se repita infinitamente
}