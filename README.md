# Reklamtavlan

Detta projekt implementerar en enkel reklamtavla med en Arduino Uno och en 16x2 LCD-display.

## Funktioner

- Slumpmässigt val av kund baserat på vikt (weighted random)
- Samma kund visas aldrig två gånger i rad
- Flera meddelanden per kund
- Speciallogik för Petter:
  - Jämn minut → ett meddelande
  - Udda minut → ett annat meddelande
- Text-effekter:
  - NORMAL
  - BLINK
  - SCROLL

## Projektstruktur

- `models.h`  
  Definierar datastrukturer (Customer, Message, Effect)

- `ad_engine.h / ad_engine.cpp`  
  Hanterar val av kund och meddelande

- `effects.h / effects.cpp`  
  Implementerar text-effekter (scroll, blink)

- `main.cpp`  
  Startar systemet och uppdaterar displayen

## Hårdvara

- Arduino Uno
- LCD 16x2

## Simulation

Projektet kan simuleras i Wokwi med samma pin-konfiguration som anges ovan.

### Kopplingar

- RS → 12  
- E  → 11  
- D4 → 4  
- D5 → 5  
- D6 → 6  
- D7 → 7  

## Hur det fungerar

Systemet visar en reklam i taget under en viss tid (t.ex. 20 sekunder).  
När tiden är slut väljs en ny kund slumpmässigt baserat på deras vikt.

Därefter väljs ett meddelande:
- Antingen slumpmässigt
- Eller baserat på tid (för Petter)

Meddelandet visas på LCD:n med en tilldelad effekt:
- NORMAL → statisk text
- BLINK → texten blinkar
- SCROLL → texten scrollar om den är för lång

## Bygg och körning

Projektet är byggt med:
- Visual Studio Code
- PlatformIO

## Designval

- Koden är uppdelad i moduler för bättre struktur och läsbarhet
- Logiken är separerad från hårdvaran
- Effekter hanteras i en egen modul

## Möjliga förbättringar

- Lägga till fler effekter
- Göra systemet datadrivet (t.ex. läsa från fil eller EEPROM)
- Visa kundens namn tillsammans med reklam
- Använda knappar för interaktion
