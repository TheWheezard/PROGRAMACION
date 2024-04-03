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

int redCount = 0;
int greenCount = 0;
int blueCount = 0;
int whiteCount = 0;
int blackCount = 0;

int redCubeCount = 0;
int blueCubeCount = 0;
int whiteCubeCount = 0;
int blackCubeCount = 0;

int redArray[] = { 0, 0, 0 };
int blueArray[] = { 0, 0, 0 };
int whiteArray[] = { 0, 0, 0 };
int blackArray[] = { 0, 0, 0 };

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
  if (Serial.available() > 0) {  //Checks if there is a byte in Serial Port
    letter = Serial.read();      //Reads the value from Serial port

    // If the real letter is 'Y' switch on the LED
    if ((letter == 'R') || (letter == 'r')) {
      calibrate();

      redArray[0] = redCount / 10;
      redArray[1] = greenCount / 10;
      redArray[2] = blueCount / 10;
    }
    else if ((letter == 'A') || (letter == 'a')) {
      calibrate();

      blueArray[0] = redCount / 10;
      blueArray[1] = greenCount / 10;
      blueArray[2] = blueCount / 10;
    }
    else if ((letter == 'B') || (letter == 'b')) {
      calibrate();

      whiteArray[0] = redCount / 10;
      whiteArray[1] = greenCount / 10;
      whiteArray[2] = blueCount / 10;
    }
    else if ((letter == 'N') || (letter == 'n')) {
      calibrate();

      blackArray[0] = redCount / 10;
      blackArray[1] = greenCount / 10;
      blackArray[2] = blueCount / 10;
    }

    if ((letter == 'K') || (letter == 'k')) {
      checkColor();

      if (redFrequency <= redArray[0] + 5 && redFrequency >= redArray[0] - 5 && greenFrequency <= redArray[1] + 5 && greenFrequency >= redArray[1] - 5 && blueFrequency <= redArray[2] + 5 && blueFrequency >= redArray[2] - 5) {
        redCubeCount++;
        Serial.println("Cubo Rojo");
      }
      //// if (redCount < 30 && redCount >= 26 && greenCount < 97 && greenCount >= 93 && blueCount < 72 && blueCount >= 67) {
      ////   Serial.println("Cubo verde");
      //// }
      else if (redFrequency <= blueArray[0] + 2 && redFrequency >= blueArray[0] - 2 && greenFrequency <= blueArray[1] + 2 && greenFrequency >= blueArray[1] - 2 && blueFrequency <= blueArray[2] + 2 && blueFrequency >= blueArray[2] - 2) {
        blueCubeCount++;
        Serial.println("Cubo Azul");
      }
      else if (redFrequency <= whiteArray[0] + 2 && redFrequency >= whiteArray[0] - 2 && greenFrequency <= whiteArray[1] + 2 && greenFrequency >= whiteArray[1] - 2 && blueFrequency <= whiteArray[2] + 2 && blueFrequency >= whiteArray[2] - 2) {
        whiteCubeCount++;
        Serial.println("Cubo Blanco");
      }
      else if (redFrequency <= blackArray[0] + 5 && redFrequency >= blackArray[0] - 5 && greenFrequency <= blackArray[1] + 5 && greenFrequency >= blackArray[1] - 5 && blueFrequency <= blackArray[2] + 5 && blueFrequency >= blackArray[2] - 5) {
        blackCubeCount++;
        Serial.println("Cubo Negro");
      }
      else
        Serial.println("Color no detectado");
    }
  }
  
  printColor();
}

void calibrate() {
  redCount = 0;
  greenCount = 0;
  blueCount = 0;
  for (int i = 0; i < 10; i++) {
    checkColor();
    redCount += redFrequency;
    greenCount += greenFrequency;
    blueCount += blueFrequency;
  }
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

void printColor() {
  Pot = analogRead(A0);
  Serial.print("Pot: ");
  Serial.print(Pot);
  Serial.print("Red Cubes: ");
  Serial.print(redCubeCount, DEC);
  Serial.print(" Black Cubes: ");
  Serial.print(blackCubeCount, DEC);
  Serial.print(" Blue Cubes: ");
  Serial.print(blueCubeCount, DEC);
  Serial.print(" White Cubes: ");
  Serial.print(whiteCubeCount, DEC);
  Serial.println();
  delay(1000);
}