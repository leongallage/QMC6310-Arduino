#include "QMC6310.h"
#include <math.h>
#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

bool QMC6310::begin() {
  Wire.begin();
  Wire.beginTransmission(QMC6310_ADDRESS);
  Wire.write(QMC6310_CONTROL_1);
  //Wire.write(0x1D); // Set mode to continuous, ODR to 200Hz, OSR to 512
  Wire.write(0x1D); // Set mode to continuous, ODR to 200Hz, OSR to 512  (AJT edit)
  return (Wire.endTransmission() == 0); // Return true if transmission was successful
}
float QMC6310::calculateAzimuth(int16_t x, int16_t y) {
  // Convert magnetic field readings to azimuth angle
  float heading = atan2((float)y, (float)x); // atan2 returns the angle in radians
  heading = heading * 180 / PI; // Convert radians to degrees

  // Normalize the heading
  if (heading < 0) {
    heading += 360;
  }

  return heading; // In degrees
}

float QMC6310::calculateElevation(int16_t x, int16_t y, int16_t z) {
  // Assuming the sensor is level, the elevation can be calculated as:
  float pitch = atan2(-x, sqrt(y * y + z * z)) * 180 / PI; // Convert radians to degrees
  return pitch;
}

bool QMC6310::readData(int16_t &x, int16_t &y, int16_t &z) {
  // Check if data is ready
  Wire.beginTransmission(QMC6310_ADDRESS);
  Wire.write(QMC6310_STATUS);
  if (Wire.endTransmission() != 0 || Wire.requestFrom(QMC6310_ADDRESS, 1) != 1) {
    return false; // I2C transmission error
  }
  if ((Wire.read() & QMC6310_STATUS_DRDY) == 0) {
    return false; // Data not ready
  }

  // Read data
  Wire.beginTransmission(QMC6310_ADDRESS);
  Wire.write(QMC6310_X_LSB);
  if (Wire.endTransmission() != 0 || Wire.requestFrom(QMC6310_ADDRESS, 6) != 6) {
    return false; // I2C transmission error
  }
  x = Wire.read() | Wire.read() << 8;
  y = Wire.read() | Wire.read() << 8;
  z = Wire.read() | Wire.read() << 8;

  // Check if data is within expected range
  if (x < -32768 || x > 32767 || y < -32768 || y > 32767 || z < -32768 || z > 32767) {
    return false; // Data out of range
  }

  return true; // Data read successfully
}