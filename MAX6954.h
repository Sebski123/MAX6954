#ifndef max6954_h
#define max6954_h

#include "Arduino.h"
#include <SPI.h>

#define CS_HIGH digitalWrite(cs, HIGH);
#define CS_LOW digitalWrite(cs, LOW);

class MAX6954
{
public:
  MAX6954(uint8_t mosi, uint8_t sck, uint8_t cs);
  MAX6954(uint8_t cs = SS, SPIClass *theSPI = &SPI);

  void begin();
  void send_data(byte address, byte data);
  void write_char(char c, int col = 0);
  void write_string(char str[], int col = 0);
  void set_global_brightness(int i);
  void clear();

private:
  uint8_t mosi, sck, cs;
  bool hwSPI;
  SPIClass *_spi;
  void pulse_clock();
  void send_address(byte address);
  void send_data(byte data);
};

#endif