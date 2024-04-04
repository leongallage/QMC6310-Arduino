#include "QMC6310.h"
QMC6310 hallSensor;
void setup() {
  Serial.begin(9600);
  if (!hallSensor.begin()) {
    Serial.println("Failed to iniƟalize QMC6310 sensor!");
    while (1);
  }
  Serial.print("X: ");
}
void loop() {
  int16_t x, y, z;
  float azimuth, elevation;
  if (hallSensor.readData(x, y, z)) {
    azimuth = hallSensor.calculateAzimuth(x, y);
    elevation = hallSensor.calculateElevation(x, y, z);

    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.print(z);
    Serial.print(" azimuth: ");
    Serial.print(azimuth);
    Serial.print(" elevation: ");
    Serial.println(elevation);
  } else {
    Serial.print(".");
  }
  delay(3000);
}
