/**
 * @file E9_1.ino
 * @brief Programa para determinar el color de un objeto utilizando el sensor de color TCS3200 y Arduino.
 * @author Javier Lopez
 */

// Pines del TCS3200 conectados a Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int Pot = 0;

int redCount = 0;
int greenCount = 0;
int blueCount = 0;
int whiteCount = 0;
int blackCount = 0;

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
  int colorSwitch = -1;
  // PENDIENTE: Implementar la lógica para determinar el color
  // Concretamente se debe confirmar el rango de valores para cada color
  if (redFrequency > greenFrequency && redFrequency > blueFrequency) {
    Serial.println("Rojo");
    colorSwitch = 1;
  }
  else if (greenFrequency > redFrequency && greenFrequency > blueFrequency) { // Not needed
    Serial.println("Verde");
    colorSwitch = 2;
  }
  else if (blueFrequency > redFrequency && blueFrequency > greenFrequency) {
    Serial.println("Azul");
    colorSwitch = 3;
  }
  else if (redFrequency == greenFrequency && redFrequency == blueFrequency) {
    Serial.println("Blanco");
    colorSwitch = 4;
  }
  else if (redFrequency == greenFrequency) { // Not needed
    Serial.println("Amarillo");
  }
  else if (redFrequency == blueFrequency) { // Not needed
    Serial.println("Morado");
  }
  else if (greenFrequency == blueFrequency) { // Not needed
    Serial.println("Cyan");
  }
  else if (redFrequency == 0 && greenFrequency == 0 && blueFrequency == 0) {
    Serial.println("Negro");
    colorSwitch = 5;
  }
  else { // No necesario para E1, E2, E3
    Serial.println("No se puede determinar el color");
  }

  countColors(colorSwitch); // Para E5 y E6
}

/**
 * @brief Lee las frecuencias de los fotodiodos para cada color y las imprime por pantalla.
 * @details Configura los fotodiodos con filtros rojo, verde y azul para leer las frecuencias de salida.
 * @details Luego, imprime por pantalla los valores de las frecuencias de cada color.
 * @author Javier Lopez
 */
void checkColor() {
  // Lee e imprime por pantalla el valor del potenciómetro
    Pot = analogRead(A0);
    Serial.print("Pot: ");
    Serial.print(Pot);
    // Configurar los fotodiodos con filtro rojo RED (R) para que sean leídos
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Leer la frecuencia de salida
    redFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de rojo RED (R)
    Serial.print("R = ");
    Serial.print(redFrequency);
    delay(100);

    // Configurar los fotodiodos con filtro verde GREEN (G) para que sean leídos
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Leer la frecuencia de salida
    greenFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de verde GREEN (G)
    Serial.print(" G = ");
    Serial.print(greenFrequency);
    delay(100);

    // Configurar los fotodiodos con filtro azul BLUE (B) para que sean leídos
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Leer la frecuencia de salida
    blueFrequency = pulseIn(sensorOut, LOW);
    // Imprimir por pantalla el valor de azul BLUE (B)
    Serial.print(" B = ");
    Serial.print(blueFrequency);
    
    Serial.println();
    delay(100);
}

/**
 * @brief Cuenta los colores detectados y actualiza las variables correspondientes.
 * @param colorSwitch El número del color detectado.
 * @details Utiliza un switch para incrementar la variable correspondiente al color detectado.
 * @details Si se recibe el carácter 'r', reinicia todas las variables de conteo a cero.
 * @details Se utiliza en los ejercicios E5 y E6 para contar los colores detectados por el sensor de color TCS3200. 
 * @author Javier Lopez
 */
void countColors(int colorSwitch){
  char digiButton = '0';

  if (Serial.available()) {
    digiButton = Serial.read();
    if (digiButton == 'c') {
      switch (colorSwitch) {
      case 1:
        redCount++;
        break;
      case 2:
        greenCount++;
        break;
      case 3:
        blueCount++;
        break;
      case 4:
        whiteCount++;
        break;
      case 5:
        blackCount++;
        break;

      default:
        break;
      }
    } else if (digiButton == 'r') {
      redCount = 0;
      greenCount = 0;
      blueCount = 0;
      whiteCount = 0;
      blackCount = 0;
    }
  }
}
