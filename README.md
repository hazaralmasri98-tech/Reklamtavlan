# Reklamtavlan – AVR-baserad LCD Advertising Simulator

## Beskrivning

Detta projekt simulerar en reklamtavla som visar olika reklammeddelanden på en LCD-skärm (16x2).
Olika kunder har olika krav på hur deras meddelanden ska visas, samt olika vikt (hur ofta de visas).

Projektet är implementerat i **ren C/C++ för AVR** och körs på riktig hårdvara.

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

* ATmega328P (AVR)
* LCD 16x2 (4-bitarsläge)
* Ren C/C++ (utan Arduino-bibliotek)

---

## Hårdvara

Projektet har testats på riktig hårdvara.

Koppling:

* RS → pin 12 (PB4)
* E → pin 11 (PB3)
* D4 → pin 4 (PD4)
* D5 → pin 5 (PD5)
* D6 → pin 6 (PD6)
* D7 → pin 7 (PD7)
* VSS → GND
* VDD → 5V
* RW → GND
* V0 → potentiometer (justering av kontrast)
* A → 5V (bakgrundsbelysning)
* K → GND

---

## Designval


Projektet är uppdelat i flera moduler:

* `models` – datatyper (Customer, Message)
* `ad_engine` – logik för att välja kund och meddelande
* `effects` – hantering av visuella effekter
* `lcd_driver` – låg-nivå styrning av LCD
* `timer` – tidsfunktionalitet med interrupts
* `rng` – pseudo-slumptalsgenerator

Denna struktur gör koden mer läsbar, återanvändbar och lätt att underhålla.

Slumpning baseras på vikt för att simulera olika betalnivåer mellan kunder.

---

## Implementation

Projektet är implementerat i ren C/C++ för AVR och använder inte Arduino-bibliotek.

Följande delar har implementerats direkt:

* timerhantering med AVR-timer och interrupts
* enkel pseudo-slumpgenerator
* LCD-styrning i 4-bitarsläge via AVR-portar (PORTB och PORTD)

---

## Installation

1. Klona repot
2. Öppna projektet i VS Code med PlatformIO
3. Bygg projektet
4. Ladda upp till ATmega328P / Arduino Uno

---

## Simulation

En enkel simulering kan göras i Wokwi vid behov.

---

## Slutsats

Projektet uppfyller alla krav genom att:

* Hantera flera kunder med olika krav
* Visa text på olika sätt (effekter)
* Använda strukturerad och modulär kod
* Implementera hårdvarunära lösningar i AVR
* Testas på riktig hårdvara
