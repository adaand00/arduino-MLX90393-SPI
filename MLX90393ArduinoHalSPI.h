#pragma once
#include "MLX90393Hal.h"
#ifdef MLX90393_ENABLE_ARDUINO
#include <Wire.h>
#include <SPI.h>


class MLX90393ArduinoHalSPI : public MLX90393Hal {
  public:
    void set_spiPort(SPIClass *spiPort); // SPI specific
    bool transceive(const uint8_t *request, size_t request_size, uint8_t *response, size_t response_size);
    void set_drdy_pin(int pin) override;
    bool has_drdy_pin() override {return this->drdy_pin_ != -1;}
    bool read_drdy_pin();
    void sleep_millis(uint32_t millis);
    void sleep_micros(uint32_t micros);
    void set_CS_pin(int pin); // SPI specific
  protected:

    SPIClass *spiPort_ = nullptr;
    int CS_pin_ = -1;
};

#endif