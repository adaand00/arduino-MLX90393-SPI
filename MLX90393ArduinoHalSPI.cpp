
#include "MLX90393Hal.h"
#ifdef MLX90393_ENABLE_ARDUINO
#include "MLX90393ArduinoHalSPI.h"
#include "stdint.h"
#include <Arduino.h>

void MLX90393ArduinoHalSPI::set_spiPort(SPIClass *spiPort, uint32_t spiFreq) {
  if (spiFreq > 10000000){
    spiFreq = 10000000;
  }

  this->spiPort_ = spiPort;
  this->spiPort_->beginTransaction(SPISettings(spiFreq, MSBFIRST, SPI_MODE3));
  delay(10);
  this->spiPort_->transfer(0x00); // Send dummy to force clock high.
}

bool MLX90393ArduinoHalSPI::transceive(const uint8_t *request, size_t request_size, uint8_t *response, size_t response_size) {

  digitalWrite(this->CS_pin_, LOW);

  uint8_t buff[request_size+response_size];
  for (int i = 0; i < request_size+response_size; i++) {
    if(i<request_size)
      buff[i] = request[i];
    else
      buff[i] = 0x00;
  }

  this->spiPort_->transfer(buff, request_size+response_size);

  for (int i = 0; i < response_size; i++) {
    response[i] = buff[i+request_size];
  }

  digitalWrite(this->CS_pin_, HIGH);

  return true;
}

void MLX90393ArduinoHalSPI::set_drdy_pin(int pin) {
  MLX90393Hal::set_drdy_pin(pin);
  if (pin >= 0){
    pinMode(pin, INPUT);
  }  else {
  }
}

bool MLX90393ArduinoHalSPI::read_drdy_pin() {
  return digitalRead(this->drdy_pin_) == HIGH;
}

void MLX90393ArduinoHalSPI::set_CS_pin(int pin) {
  this->CS_pin_ = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(10);
}

void MLX90393ArduinoHalSPI::sleep_millis(uint32_t millis) {
  delay(millis);
}

void MLX90393ArduinoHalSPI::sleep_micros(uint32_t micros) {
  delayMicroseconds(micros);
}

#endif