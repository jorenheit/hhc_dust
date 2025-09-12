#pragma once

#include "Seeed_HM330X.h"

/* DATA FORMAT
|Bytes | Content
|------+------------------------------------------------------------------------------
|0-1   |  reserved
|2-3   |  Sensor number
|4-5   |  PM1.0 concentration（CF=1 ，Standard particulate）unit μg/ m3
|6-7   |  PM2.5 concentration（CF=1 ，Standard particulate）unit μg/ m3
|8-9   |  PM10 concentration（CF=1 ，Standard particulate）unit μg/ m3
|10-11 |  PM1.0 concentration （Atmospheric environment）unit μg/ m3
|12-13 |  PM2.5 concentration （Atmospheric environment）unit μg/ m3
|14-15 |  PM10 concentration （Atmospheric environment）unit μg/ m3
|16-17 |  the number of particles with diameter 0.3um or above in 1 liter of air
|18-19 |  the number of particles with diameter 0.5um or above in 1 liter of air
|20-21 |  the number of particles with diameter 1.0um or above in 1 liter of air
|22-23 |  the number of particles with diameter 2.5um or above in 1 liter of air
|24-25 |  the number of particles with diameter 5.0um or above in 1 liter of air
|26-27 |  the number of particles with diameter 10um or above in 1 liter of air
|28    |  Checksum = sum(0:27)
+------+------------------------------------------------------------------------------
*/

namespace Dust {

enum Params {
    DATA_SIZE    = 29,
    PM_1_0_INDEX = 10,
    PM_2_5_INDEX = 12,
    PM_10_INDEX  = 14
};

inline void _stall() { while (1) {} };

struct Sensor {
    HM330X sensor;
    uint16_t pm_1_0, pm_2_5, pm_10;
    unsigned long lastUpdateTime;

    void init() {
        if (sensor.init()) {
            Serial.println("Sensor init failed.");
            _stall();
        }
    }

    bool validate(uint8_t *buf) {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i != DATA_SIZE - 1; ++i) {
            checksum += buf[i];
        }
        return checksum == buf[DATA_SIZE - 1];
    }

    void update() {
        static uint8_t buf[DATA_SIZE];
        if(sensor.read_sensor_value(buf, DATA_SIZE)) {
            Serial.println("ERROR: read_sensor failed.");
            _stall();
        }
        
        if (!validate(buf)) {
            Serial.println("ERROR: checksum failed.");
            _stall();
        }

        auto get = [&](int index) -> uint16_t {
            return (static_cast<uint16_t>(buf[index]) << 8) | buf[index + 1];
        };

        pm_1_0 = get(PM_1_0_INDEX);
        pm_2_5 = get(PM_2_5_INDEX);
        pm_10  = get(PM_10_INDEX);
        lastUpdateTime = millis();
    }

    void wait(unsigned long dt) {
        while (millis() - lastUpdateTime < dt) {}
    }
    void printHeader() {
        Serial.println("t(s), pm1.0 (ug/m3), pm2.5 (ug/m3), pm10 (ug/m3)");
    }

    void print() {
        Serial.print(lastUpdateTime);   Serial.print(", ");
        Serial.print(pm_1_0); Serial.print(", ");
        Serial.print(pm_2_5); Serial.print(", ");
        Serial.println(pm_10);
    }
};

} // namespace Dust
