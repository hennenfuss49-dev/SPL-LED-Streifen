#include "Arduino.h"

class TasterEntpreller {
private:
    const int pin;
    bool zustandBtn;
    unsigned long entprellZeit;
    unsigned long entprellIntervall;

public:
    TasterEntpreller(int pinNum, unsigned long entprellIntervallMillis) 
    : pin(pinNum), entprellIntervall(entprellIntervallMillis) 
    {
      pinMode(pinNum, INPUT_PULLUP);
    }

    // Methode, die am Anfang jedes Loops aufgerufen wird, um den Tasterzustand zu aktualisieren
    void aktualisiere() 
    {
      bool aktuellerZustand = !digitalRead(pin);

      if (aktuellerZustand != zustandBtn) {
        if (millis() - entprellZeit >= entprellIntervall) {
          entprellZeit = millis();

          zustandBtn = aktuellerZustand;
        }
      }
    }

    bool istGedrueckt()
    {
        return zustandBtn;
    }
};

TasterEntpreller taster(5, 50);

void setup(){
  Serial.begin(9600);
}

void loop(){
  taster.aktualisiere();
  Serial.println(taster.istGedrueckt());
}
