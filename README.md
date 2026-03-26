# Reklamtavlan – Arduino LCD Advertising Simulator

## Beskrivning

Detta projekt simulerar en reklamtavla som visar olika reklammeddelanden på en LCD-skärm (16x2).
Olika kunder har olika krav på hur deras meddelanden ska visas, samt olika vikt (hur ofta de visas).

Projektet är implementerat i C++ med Arduino och körs på riktig hårdvara.

---

## Funktionalitet

* Slumpar fram en kund baserat på vikt (betalning)
* Samma kund visas aldrig två gånger i rad
* Varje kund har egna meddelanden
* Stöd för olika effekter:

  * Normal text
  * Scrollande text
  * Blinkande text
* Specialfall för "Svarte Petter":

  * Olika meddelande beroende på jämn/ojämn minut

---

## Teknik
git status
git add README.md
git commit -m "Update README with project description"
git push
* Arduino Uno
* LCD 16x2 (LiquidCrystal)
* C++

---

## Hårdvara

Projektet har testats på riktig hårdvara.

Koppling:

* RS → pin 12
* E → pin 11
* D4 → pin 4
* D5 → pin 5
* D6 → pin 6
* D7 → pin 7
* VSS → GND
* VDD → 5V
* RW → GND
* V0 → GND (kontrast)
* A → 5V (bakgrundsbelysning)
* K → GND

---

## Designval

Projektet är uppdelat i flera moduler:

* `models` – datatyper (Customer, Message)
* `ad_engine` – logik för att välja kund och meddelande
* `effects` – hantering av visuella effekter

Denna struktur gör koden mer läsbar, återanvändbar och lätt att underhålla.

Slumpning baseras på vikt för att simulera olika betalnivåer mellan kunder.

---

## Git-historik

Projektet har utvecklats stegvis med flera commits som visar utvecklingen från enkel implementation till en mer strukturerad lösning.

---

## Installation
1. Klona repot
2. Öppna i Arduino IDE
3. Ladda upp till Arduino Uno


## Simulation

En enkel simulering kan göras i Wokwi vid behov.

---

## Slutsats

Projektet uppfyller alla krav genom att:

* Hantera flera kunder med olika krav
* Visa text på olika sätt (effekter)
* Använda strukturerad och modulär kod
* Testas på riktig hårdvara


