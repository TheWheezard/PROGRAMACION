/**
 * @file E9_1.ino
 * @brief Programa para determinar el color de un objeto utilizando el sensor de color TCS3200 y Arduino.
 * @author Javier Lopez
 */

 // Pines del TCS3200 conectados a Arduino
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 2

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int Pot = 0;
char letter = ' ';


/**
 * @brief Configura los pines y la comunicación en serie.
 * @author Javier Lopez
 */
void setup() {
  // Configurar las salidas
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Configurar que la señal sensorOut es una entrada
  pinMode(sensorOut, INPUT);
  // Configurar la frecuencia al 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  // Comenzar comunicación en serie
  Serial.begin(9600);
}

/**
 * @brief Función principal que determina el color del objeto y cuenta los colores detectados.
 * @details Utiliza la lógica de comparación de frecuencias para determinar el color del objeto.
 * @details Luego, utiliza la función countColors para contar los colores detectados.
 * @author Javier Lopez
 */
void loop() {
  checkColor();

  if (redFrequency < 35 && redFrequency >= 25 && greenFrequency < 100 && greenFrequency >= 90 && blueFrequency < 75 && blueFrequency >= 65) {
    Serial.println("Cubo Rojo");
  }
  //// if (redFrequency < 30 && redFrequency >= 26 && greenFrequency < 97 && greenFrequency >= 93 && blueFrequency < 72 && blueFrequency >= 67) {
  ////   Serial.println("Cubo verde");
  //// }
  else if (redFrequency < 15 && greenFrequency < 15 && blueFrequency < 15) {
    Serial.println("Cubo Blanco");
  }
  else if (redFrequency < 50 && greenFrequency < 30 && blueFrequency < 15) {
    Serial.println("Cubo Azul");
  }
  else if (redFrequency >= 110 && greenFrequency >= 110 && blueFrequency >= 80) {
    Serial.println("Cubo Negro");
  }
  delay(500);
}

/**
 * @brief Lee las frecuencias de los fotodiodos para cada color y las imprime por pantalla.
 * @details Configura los fotodiodos con filtros rojo, verde y azul para leer las frecuencias de salida.
 * @details Luego, imprime por pantalla los valores de las frecuencias de cada color.
 * @author Javier Lopez
 */
void checkColor() {
  //Serial.println("Comprobando colores...");
  // Lee e imprime por pantalla el valor del potenciómetro
  // Pot = analogRead(A0);
  //Serial.print("Pot: ");
  //Serial.print(Pot);
  // Configurar los fotodiodos con filtro rojo RED (R) para que sean leídos
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Leer la frecuencia de salida
  redFrequency = pulseIn(sensorOut, LOW);
  // Imprimir por pantalla el valor de rojo RED (R)
  //Serial.print("R = ");
  //Serial.print(redFrequency);
  //delay(100);

  // Configurar los fotodiodos con filtro verde GREEN (G) para que sean leídos
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Leer la frecuencia de salida
  greenFrequency = pulseIn(sensorOut, LOW);
  // Imprimir por pantalla el valor de verde GREEN (G)
  //Serial.print(" G = ");
  //Serial.print(greenFrequency);
  //delay(100);

  // Configurar los fotodiodos con filtro azul BLUE (B) para que sean leídos
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Leer la frecuencia de salida
  blueFrequency = pulseIn(sensorOut, LOW);
  // Imprimir por pantalla el valor de azul BLUE (B)
  // Serial.print(" B = ");
  // Serial.print(blueFrequency);

  // Serial.println();
  //delay(100);
}

// void printColor() {
//   Pot = analogRead(A0);
//   Serial.print("Pot: ");
//   Serial.print(Pot);
//   Serial.print("Red: ");
//   Serial.print(redFrequency, DEC);
//   Serial.print(" Green: ");
//   Serial.print(greenFrequency, DEC);
//   Serial.print(" Blue: ");
//   Serial.print(blueFrequency, DEC);
//   Serial.println();
//   delay(1000);
// }