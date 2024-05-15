//https://github.com/cgxeiji/CGx-InverseK

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>
// #include "Sensor.cpp"

#define S0 0   // D3
#define S1 1   // D4
#define S2 2   // D5
#define S3 4   // D6
#define OUT 10 // D2

const int s0 = 3;
const int s1 = 4;
const int s2 = 5;
const int s3 = 6;
const int out = 2;

int countRed = 0;
int countGreen = 0;
int countBlue = 0;
int Pot = 0;
// inicialización de entradas y salidas
enum color { VACIO,
             ROJO,
             BLANCO,
             NEGRO };


Servo barrera;
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;



void setup() {

  // Init barrera
  barrera.attach(8, 1000, 2000);  //Set the pin to attach the servo
  barrera.write(0);

  // Init CNY
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

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
    Serial.println("INIT POSITION");
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
  delay(1000);
  color c = leerColor();
  // color c = 1;
  delay(1000);

  cargarCubo();
  enviarColor(c);
  barrera.write(180);  // Subir
  delay(5000);
  barrera.write(0);  // Bajar

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
  delay(8000);

  // RESET POSITION
  float a0, a1, a2, a3;
  if(InverseK.solve(0, 0, 505-75, a0, a1, a2, a3)) {
    Serial.println("-0-");
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
    Serial.println("RESET POSITION");
  } else {
    Serial.println("No solution found!");
  }
  while(true){}
}

// @brief Mueve el cubo de la zona de recogida al sensor de color
void comprobarCubo() {
  float a0, a1, a2, a3;
  float b0, b1, b2, b3;
  InverseK.solve(0, 0, 505 - 75, a0, a1, a2, a3);

  // Orientar el brazo en la primera zona y sobre el cubo
  if (InverseK.solve(0, -170, 100, b0, b1, b2, b3)) {
    Serial.println("-1a-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 10);
  } else {
    Serial.println("No solution found! -1a-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Agarrar el primer cubo
  if (InverseK.solve(0, -170, -55, b0, b1, b2, b3)) {  // -75 ~= 0
    Serial.println("-1b-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 10);
    delay(1000);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 45);
  } else {
    Serial.println("No solution found! -1b-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Elevar brazo con cubo
  if (InverseK.solve(0, -170, 100, b0, b1, b2, b3)) {
    Serial.println("-1a.-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 0, 45);
  } else {
    Serial.println("No solution found! -1a.-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Mover el cubo sobre el CNY
  if (InverseK.solve(200, -78, 100, b0, b1, b2, b3)) {
    Serial.println("-1c-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -1c-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Orientar muñeca y colocar cubo
  if (InverseK.solve(202, -76, 0, b0, b1, b2, b3)) {
    Serial.println("-1d-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 76, 45);
    delay(1000);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 76, 10);
  } else {
    Serial.println("No solution found! -1d-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Soltar cubo
  /* Hay que soltar y elevar*/
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
  float a0, a1, a2, a3;
  float b0, b1, b2, b3;
  InverseK.solve(0, 0, 505 - 75, a0, a1, a2, a3);

  // Orientar muñeca y recoger cubo
  if (InverseK.solve(202, -76, 0, b0, b1, b2, b3)) {
    Serial.println("-2a-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 10);
    delay(1000);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -2a-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Elevar brazo con cubo
  if (InverseK.solve(202, -76, 100, b0, b1, b2, b3)) {
    Serial.println("-2b-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -2b-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }

  // Maniobra de giro hacia la zona de carga (retraer brazo)
  if (InverseK.solve(130, -78, 100, b0, b1, b2, b3)) {
    Serial.println("-2c-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -2c-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }

  // Maniobra de giro hacia la zona de carga (girar brazo)
  if (InverseK.solve(0, 170, 100, b0, b1, b2, b3)) {
    Serial.println("-2d-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -2d-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Posicionar el brazo en la zona de carga
  if (InverseK.solve(95, 180, 100, b0, b1, b2, b3)) {
    Serial.println("-2e-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
  } else {
    Serial.println("No solution found! -2e-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);

  // Bajar el brazo en la zona de carga
  // TODO: Ajustar la altura de la zona de carga y verificar posición del coche
  if (InverseK.solve(95, 180, 0, b0, b1, b2, b3)) {
    Serial.println("-2f-");
    Serial.print(a2b(b0));
    Serial.print(',');
    Serial.print(a2b(b1));
    Serial.print(',');
    Serial.print(a2b(b2));
    Serial.print(',');
    Serial.println(a2b(b3));
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 45);
    delay(1000);
    Braccio.ServoMovement(20, a2b(b0), a2b(b1), a2b(b2), a2b(b3), 74, 10);
  } else {
    Serial.println("No solution found! -2f-");
    Braccio.ServoMovement(20, a2b(a0), a2b(a1), a2b(a2), a2b(a3), 0, 20);
  }
  delay(1000);
}
void descargarRojo() {}
void descargarBlanco() {}
void descargarNegro() {}
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

void recibirColor() {
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    countRed = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s3, HIGH);
    countBlue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s2, HIGH);
    countGreen = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}
// Programa principal
color leerColor() {
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
    if (countRed > 30 && countRed < 45 && countGreen > 65 && countGreen < 80 && countBlue > 55 && countBlue < 75) {
        Serial.println(" ‐ Color Rojo");
        return ROJO;
    }
    // else if (countRed > 200 && countRed < 230 && countGreen > 185 && countGreen < 220 && countBlue > 80 && countBlue < 115) {
    //     Serial.println(" ‐ Color Azul");
    // }
    // else if (countRed > 170 && countRed < 200 && countGreen > 80 && countGreen < 100 && countBlue > 35 && countBlue < 55) {
    //     Serial.println(" ‐ Color 3");
    // }
    else if (countRed > 50 && countRed < 60 && countGreen > 105 && countGreen < 120 && countBlue > 90 && countBlue < 110) {
        Serial.println(" ‐ Color Blanco");
        return BLANCO;
    }
    // else if (countRed > 20 && countRed < 60 && countGreen > 20 && countGreen < 60 && countBlue > 180 && countBlue < 230) {
    //     Serial.println(" ‐ Color Negro");
    // }
    else if (countRed > 100 /*&& countGreen < 50 && countBlue > 170 && countBlue < 70*/) {
        Serial.println(" ‐ Color Negro");
        return NEGRO;
    }
    else {
        Serial.println("‐ VACIO");
        return VACIO;
    }
    delay(300);
}
