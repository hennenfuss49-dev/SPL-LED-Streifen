#include "Arduino.h"

class TasterEntpreller {
private:
    const int pin;
    bool zustandBtn;
    bool letzterZustand;
    unsigned long entprellZeit;
    unsigned long entprellIntervall;
    unsigned long gedruecktZeit;  // Zeit, in der der Taster gedrückt wurde
    bool langerDruckErkannt;
public:
    TasterEntpreller(int pinNum, unsigned long entprellIntervallMillis) 
    : pin(pinNum), entprellIntervall(entprellIntervallMillis), letzterZustand(false), gedruecktZeit(0) 
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

                // Wenn der Taster gedrückt wurde, die Zeit speichern
                if (zustandBtn) {
                    gedruecktZeit = millis();
                } else if(langerDruckErkannt){
                    langerDruckErkannt = false;
                }
                
            }
        }
    }

    // Methode für den aktuellen entprellten Zustand
    bool istGedrueckt()
    {
        return zustandBtn;
    }

    // Methode für die steigende Flankenerkennung (Taster wurde gedrückt)
    bool wurdeGedrueckt() 
    {
        if (!zustandBtn && letzterZustand && (millis() - gedruecktZeit < 1900)) {
          
            letzterZustand = zustandBtn;
            return true;
        }
        letzterZustand = zustandBtn;
        return false;
    }

    // Methode, die erkennt, ob der Taster länger als 2 Sekunden gedrückt wurde
    bool wurdeLangeGedrueckt() 
    {
        if (zustandBtn && (millis() - gedruecktZeit >= 2000) && !langerDruckErkannt) {
            langerDruckErkannt = true; 
            return true;
        }
        return false;
    }
};

TasterEntpreller taster(5, 50);

void setup(){
  Serial.begin(9600);
}

void loop(){
  taster.aktualisiere();
  if(taster.wurdeGedrueckt())
    Serial.println("JJJJJ");
  if(taster.wurdeLangeGedrueckt()){
  Serial.println("jas");

  }
}