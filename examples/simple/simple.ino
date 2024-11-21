#include "TasterEntprellung.h"

#define tasterPin 2

// Initialisiere eine Instanz der TasterEntpreller-Klasse
TasterEntpreller taster(tasterPin, 50);

void setup() {
  // Initialisierung von Serial für Debugging-Zwecke
  Serial.begin(9600);

  // Setup für den Taster
  pinMode(tasterPin, INPUT_PULLUP);
}

void loop() {
  // Aktualisiere den Zustand des Tasters
  taster.aktualisiere();

  // Prüfe, ob der Taster gedrückt wurde und gib entsprechende Ausgabe
  if (taster.wurdeGedrueckt()) {
    Serial.println("Taster wurde kurz gedrückt.");
  }

  // Prüfe, ob der Taster lange gedrückt wurde und gib entsprechende Ausgabe
  if (taster.wurdeLangeGedrueckt()) {
    Serial.println("Taster wurde lange gedrückt.");
  }

  // Zeige den aktuellen Zustand des Tasters an
  if (taster.istGedrueckt()) {
    Serial.println("Taster ist gedrückt.");
  } else {
    Serial.println("Taster ist nicht gedrückt.");
  }

  delay(100); // Kurze Pause für Stabilität
}
