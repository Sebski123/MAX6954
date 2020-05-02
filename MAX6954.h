#ifndef max6954_h
#define max6954_h

#include "Arduino.h"

class MAX6954 {
  public:

    MAX6954(uint8_t out, uint8_t clk, uint8_t cs);

    uint8_t data_out, clock, chip;

    void begin();
    void send_data(byte address, byte data);
    void write_string(char str[], int col = 0);
    void set_global_brightness(int i);
    void clear();

  private:
    void chip_select_low();
    void chip_select_high();
    void sclk();
    void send_address(byte address);
    void send_data(byte data);
};

#endif