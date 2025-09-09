#include "hhc_dust.h"

// 1. Maak een nieuw Dust::Sensor object aan.
Dust::Sensor sensor;

void setup() {
    Serial.begin(115200);

    // 2. Initialiseer de sensor. Als dit niet goed gaat, zal er een bericht
    //    in de serial monitor verschijnen en stopt het programma.
    sensor.init();

    // 3. Print de header van de tabel die gegenereerd gaat worden (optioneel).
    sensor.printHeader();
}

void loop() {
    // 3. Roep "update" aan op de sensor. De sensor zal dan de meest recente data ophalen.
    sensor.update();

    // 4. Er zijn 3 meetwaarden beschikbaar: 
    //    - pm_1_0: de PM1.0 waarde in ug/m3 
    //    - pm_2_5: de PM2.5 waarde in ug/m3
    //    - pm_10:  de PM10 waarde  in ug/m3
    // 
    //    Deze waarden kun je opvragen en opslaan in een variabele als volgt:
    //    int x = sensor.pm_10;

    // 5. De print-functie stuurt alle drie waarden, gescheiden door een komma,
    //    naar de serial monitor. Dit kun je gebruiken om een CSV-bestand te 
    //    genereren, die makkelijk door bijvoorbeeld Excel ingelezen kan worden.
    sensor.print();

    // 6. Zorg voor een delay tussen de verschillende metingen. Het is niet zinnig
    //    om heel vaak te meten, omdat het niet waarschijnlijk is dat de meetwaarden
    //    zo snel zullen veranderen. De waarde die je naar de delay-functie stuurt 
    //    is gegeven in ms.
    delay(5000);
}
