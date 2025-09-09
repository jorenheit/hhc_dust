# HHC-dust
Download hier een voorbeeld-sketch om de fijnstofsensor uit te lezen met een Arduino.

## Voorbereiding (Software)
1. [Download de Arduino IDE](https://www.arduino.cc/en/software/)
2. [Download deze repo als ZIP-bestand](https://github.com/jorenheit/hhc_dust/archive/refs/heads/main.zip) en pak het bestand uit.
3. Open de Arduino IDE, klik op het boeken-icoontje aan de linkerkant en zoek naar "Seeed_PM2_5_sensor_HM3301".
4. Installeer deze bibliotheek.
5. Open "fijnstof.ino" vanuit de Arduino IDE.

## Voorbereiding (Hardware)
Maak de volgende verbindingen tussen de sensor en de Arduino UNO:
1. GND Sensor -> GND Uno
2. VCC Sensor -> 5V Uno
3. SDA Sensor -> SDA Uno
4. SCL Sensor -> SCL Uno

## Programmeren
De setup is klaar dus je kunt beginnen! In de sketch staan comments die je vertellen hoe je het programma verder kunt uitbreiden.
 
