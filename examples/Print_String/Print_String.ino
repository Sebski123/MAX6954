#include "MAX6954.h"

#define CS 11     // Chip Select
#define DATAOUT 8 // MOSI
#define CLK 9     // SCK

MAX6954 chip = MAX6954(DATAOUT, CLK, CS);
//MAX6954 chip2 = MAX6954(CS);

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