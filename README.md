QMC6310 Magnetometer Library for Arduino

This library provides an interface to interact with the QMC6310 magnetometer sensor using Arduino boards. It allows for the initialization of the sensor, reading of the magnetic field data in three dimensions, and calculation of the azimuth (heading) and elevation (pitch) angles.

Features

Initialize the QMC6310 sensor
Read magnetic field data in x, y, and z directions
Calculate azimuth (heading) relative to the magnetic north
Calculate elevation (pitch) angle
Prerequisites
Before using this library, ensure you have the Arduino IDE installed on your computer. You also need an Arduino board (e.g., Uno, Mega, Leonardo, etc.) and a QMC6310 magnetometer module connected to your Arduino via I2C.

Installation

Download the library as a ZIP file.
Open the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library, and select the downloaded ZIP file.
The library is now installed and ready to use in your sketches.

Usage

Here’s how to use the library in your Arduino sketch:

Include the QMC6310 library at the top of your sketch.
#include <QMC6310.h>

Create an instance of the QMC6310 class.
QMC6310 compass;

In the setup() function, initialize the sensor.
void setup() {
    Serial.begin(9600);
    if (!compass.begin()) {
        Serial.println("Failed to initialize the sensor!");
        while (1);
    }
}
In the loop() function, read the magnetic field data and calculate the azimuth and elevation.
void loop() {
    int16_t x, y, z;
    float azimuth, elevation;

    if (compass.readData(x, y, z)) {
        azimuth = compass.calculateAzimuth(x, y);
        elevation = compass.calculateElevation(x, y, z);

        Serial.print("Azimuth: ");
        Serial.print(azimuth);
        Serial.println(" degrees");

        Serial.print("Elevation: ");
        Serial.print(elevation);
        Serial.println(" degrees");
    } else {
        Serial.println("Error reading sensor data");
    }
    delay(1000); // Delay before next read
 }

Functions
bool begin(): Initializes the sensor and sets it up for reading.
bool readData(int16_t &x, int16_t &y, int16_t &z): Reads the magnetic field data into provided variables.
float calculateAzimuth(int16_t x, int16_t y): Calculates and returns the azimuth (heading) angle in degrees.
float calculateElevation(int16_t x, int16_t y, int16_t z): Calculates and returns the elevation (pitch) angle in degrees.







