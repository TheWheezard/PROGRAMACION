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
}

void loop() {
  // Suponiendo que los cubos están alineados y accesibles a las mismas posiciones de base y codo pero a diferentes alturas.
  // Poner brazo en neutral
  Braccio.ServoMovement(20, 0, 120, 5, 5, 90, 10); // Cerrar pinza para agarrar el cubo
  delay(1000);
  
  // Recoger el primer cubo
  comprobarCubo();

  // Mover el primer cubo a la posición de apilamiento
  // Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 43); // Mover hacia la posición de apilamiento
  // delay(1000);
  // Braccio.ServoMovement(20, 45, 95, 175, 175, 90, 43); // Soltar el cubo
  // delay(1000);
  // Braccio.ServoMovement(20, 45, 95, 175, 175, 90, 10); // Soltar el cubo
  // delay(1000);

  // Poner brazo en neutral
  // Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 43); // Brazo neutral
  // delay(1000);
  // Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Base neutral
  // delay(1000);

  // Recoger el segundo cubo
  // Braccio.ServoMovement(20, 90, 95, 175, 175, 90, 10); // Acercarse al segundo cubo
  // delay(1000);
  // Braccio.ServoMovement(20, 90, 95, 175, 175, 90, 43); // Acercarse al segundo cubo
  // delay(1000);
  // Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Cerrar pinza para agarrar el cubo
  // delay(1000);
  
  // Mover el segundo cubo a la posición de apilamiento
  // Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 43); // Mover hacia la posición de apilamiento
  // delay(1000);
  // Braccio.ServoMovement(20, 45, 78, 176, 176, 90, 43); // Soltar el cubo
  // delay(1000);
  // Braccio.ServoMovement(20, 45, 78, 176, 176, 90, 10); // Soltar el cubo
  // delay(1000);

  // Poner brazo en neutral
  // Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 43); // Brazo neutral
  // delay(1000);
  // Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Base neutral
  // delay(1000);

  // Recoger el tercer cubo
  //Braccio.ServoMovement(20, 90, 95, 175, 175, 90, 10); // Acercarse al tercer cubo
  //delay(1000);
  //Braccio.ServoMovement(20, 90, 95, 175, 175, 90, 43); // Acercarse al tercer cubo
  //delay(1000);
  //Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 43); // Cerrar pinza para agarrar el cubo
  //delay(1000);

  // Vuelve neutral
  Braccio.ServoMovement(20, 0, 120, 5, 5, 90, 43); // Cerrar pinza para agarrar el cubo

  while(1); // Detener el loop para evitar que el programa se repita infinitamente
}

// @brief Mueve el cubo de la zona de recogida al sensor de color
void comprobarCubo(){
  // Recoger el primer cubo
  Braccio.ServoMovement(20, 0, 89, 5, 5, 90, 10); // Acercarse al primer cubo
  delay(1000);
  Braccio.ServoMovement(20, 0, 89, 5, 5, 90, 43); // Acercarse al primer cubo
  delay(1000);
  Braccio.ServoMovement(20, 0, 89, 5, 5, 90, 43); // Cerrar pinza para agarrar el cubo
  delay(1000);

  // Mover el tercer cubo encima del segundo
  Braccio.ServoMovement(20, 76, 120, 5, 5, 90, 43); // Mover hacia la posición de apilamiento
  delay(1000);
  Braccio.ServoMovement(20, 76, 91, 15, 10, 90, 43); // Mover hacia la posición de apilamiento
  delay(1000);
  Braccio.ServoMovement(20, 76, 91, 15, 10, 90, 43); // Soltar el cubo
  delay(1000);
  Braccio.ServoMovement(20, 76, 91, 15, 6, 90, 10); // Soltar el cubo
  delay(1000);
}

// @brief Mueve el cubo de la zona de color al vehículo en parada de carga
void cargarCubo(){}
void descargarRojo(){}
void descargarBlanco(){}
void descargarNegro(){}
void descargarAzul(){}
void moverBarrera(){}