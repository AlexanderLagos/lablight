/*
  LabLight - Firmware del sensor BH1750
  Placa: Arduino Uno
  Librería: "BH1750" de Christopher Laws (Arduino IDE > Herramientas > Administrar bibliotecas)

  Conexiones (módulo GY-302 / BH1750):
    VCC  -> 3.3V (o 5V, el módulo GY-302 acepta ambos)
    GND  -> GND
    SDA  -> A4
    SCL  -> A5
    ADDR -> sin conectar (dirección I2C 0x23)

  Salida: una línea por lectura con el valor en lux, por ejemplo "123.5".
  Velocidad: 9600 baudios, aproximadamente 10 lecturas por segundo.
  La interfaz web (index.html) lee estas líneas con la Web Serial API.
  Importante: cerrar el Monitor Serie antes de conectar desde la interfaz.
*/

#include <Wire.h>
#include <BH1750.h>

BH1750 sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Modo continuo de alta resolución: 1 lx de resolución, rango 1 a 65535 lx.
  if (!sensor.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("ERROR: BH1750 no detectado. Revisa SDA/SCL y la alimentacion.");
  }
}

void loop() {
  float lux = sensor.readLightLevel();
  if (lux >= 0) {
    Serial.println(lux, 1);
  }
  delay(100);  // ~10 Hz. El sensor actualiza cada ~120 ms en este modo.
}
