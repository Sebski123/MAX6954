#include "MAX6954.h"

#define CS      8   // Chip Select
#define DATAOUT 9   // MOSI
#define DATAIN  11  // MISO
#define CLK     10  // SCK

MAX6954 chip = MAX6954(DATAOUT, DATAIN, CLK, CS);

void setup()
{
    chip.begin();
    chip.clear();
    chip.set_global_brightness(1);
    chip.write_string("maxim");
}

void loop()
{
}