#ifndef TASK_MEASURE_ELECTRICITY
#define TASK_MEASURE_ELECTRICITY

#include <Arduino.h>
#include "EmonLib.h"

#include "../config/config.h"
#include "../config/enums.h"
#include "mqtt-aws.h"


extern DisplayValues gDisplayValues;
extern EnergyMonitor emon1;
extern unsigned short measurements[];
extern unsigned char measureIndex;

  double filterNoise(double rawValue, double prevValue, double alpha) {
    // alpha ค่าระหว่าง 0 ถึง 1 (เช่น 0.1 หรือ 0.2)
    return (alpha * rawValue) + ((1 - alpha) * prevValue);
    }

void measureElectricity(void * parameter)
{
    for(;;){
      serial_println("[ENERGY] Measuring...");
      long start = millis();

    static double lastAmps = 0; // เก็บค่าก่อนหน้า
    double rawAmps = emon1.calcIrms(1480);
    double amps = filterNoise(rawAmps, lastAmps, 0.2); // ใช้ alpha = 0.2
    lastAmps = amps;
      double watts = amps * HOME_VOLTAGE;

      if (amps <= 0 || isnan(amps)) {
            serial_println("[ERROR] Failed to read amps. Check sensor connection.");
            vTaskDelay(1000 / portTICK_PERIOD_MS); // หน่วงเวลา 1 วินาที แล้วลองใหม่
            continue;
        }

      gDisplayValues.amps = amps;
      gDisplayValues.watt = watts;
      serial_print("Amps");
      serial_println(amps);
      serial_print("watts");
      serial_println(watts);

      measurements[measureIndex] = watts;
      measureIndex++;

      if(measureIndex == LOCAL_MEASUREMENTS){
          #if AWS_ENABLED == true
            xTaskCreate(
              uploadMeasurementsToAWS,
              "Upload measurements to AWS",
              10000,             // Stack size (bytes)
              NULL,             // Parameter
              5,                // Task priority
              NULL              // Task handle
            );
          #endif


          measureIndex = 0;
      }

      long end = millis();

      // Schedule the task to run again in 1 second (while
      // taking into account how long measurement took)
      vTaskDelay((1000-(end-start)) / portTICK_PERIOD_MS);
    }
}

#endif