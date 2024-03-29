#include "musical_notes.h"
#include "musical_figures.h"

int buzzer = 9;

int cumple_n[26] = { Sol4, Sol4, La4, Sol4, Do5, Si4, Sol4, Sol4, La4, Sol4, Re5, Do5, Sol4, Sol4, Sol5, Mi5, Do5, Si4, La4, Fa5, Fa5, Mi5, Do5, Re5, Do5 };
int cumple_f[26] = { C, C, N, N, N, B, C, C, N, N, N, B, C, C, N, N, N, N, N, C, C, N, N, N, B };

int lotr_n[18] = { La4, Sol4, Sol4, Sol4, La4, Z, Re5, Mi5, Fa5, Mi5, Re5, Do5, Re5, Mi5, Re5, Do5, Si4, La4 };
int lotr_f[18] = { N+C, N, S, S, B, C, S, S, N, S, S, N, S, S, N+C, N, C, N+C };

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // tone(buzzer, Z, B);
  // noTone(buzzer);
  for (int nota = 0; nota < 26; nota++) {
    tone(buzzer, lotr_n[nota], lotr_f[nota]);
    delay(lotr_f[nota]);
    noTone(buzzer);
    delay(10);
  }
}