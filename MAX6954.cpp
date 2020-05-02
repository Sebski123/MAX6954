//#include "Arduino.h"
#include "MAX6954.h"

MAX6954::MAX6954(uint8_t mosi, uint8_t clk, uint8_t cs)
{
    data_out = mosi;
    clock = clk;
    chip = cs;

    pinMode(data_out, OUTPUT);
    pinMode(clock, OUTPUT);

    pinMode(chip, OUTPUT);

    digitalWrite(chip, HIGH);
}

void MAX6954::begin()
{
    // Digit Type - all 14 segments
    send_data(0x0C, 0xFF); 
    // Scan Limit - 6 digits
    send_data(0x03, 0x05);
    // Configuration - normal operation and global brightness
    send_data(0x04, 0x01);
}

void MAX6954::send_data(byte address, byte data){
    send_address(address);
    send_data(data);
}

void MAX6954::write_string(char str[], int col /*= 0*/)
{
  int i = 0;
  for (int digit = 0x20 + col; digit <= 0x25; digit++)
  {
    //If end of string is reached return
    if (str[i] == '\0')
      return;
    
    //Write char
    send_data(digit, str[i]);
    i++;
  }
}

void MAX6954::set_global_brightness(int i)
{
  if (i > 15)
    i = 15;
  if (i < 0)
    i = 0;

  send_data(0x02, i);
}

void MAX6954::chip_select_low()
{
    digitalWrite(chip, LOW);
}

void MAX6954::chip_select_high()
{
    digitalWrite(chip, HIGH);
}

void MAX6954::sclk()
{
    digitalWrite(clock, HIGH);
    digitalWrite(clock, LOW);
}

void MAX6954::send_address(byte address)
{
    char abit;
    char index;
    chip_select_low();
    for (index = 7; index >= 0; index--)
    {
        abit = ((address >> index) & 0x01);
        if (abit == 1)
        {
            digitalWrite(data_out, HIGH);
            sclk();
        }
        else
        {
            digitalWrite(data_out, LOW);
            sclk();
        }
    }
}

void MAX6954::send_data(byte data)
{
    char abit;
    char index;
    for (index = 7; index >= 0; index--)
    {
        abit = ((data >> index) & 0x01);
        if (abit == 1)
        {
            digitalWrite(data_out, HIGH);
        }
        else
        {
            digitalWrite(data_out, LOW);
        }
        if (index == 0)
        {
            digitalWrite(clock, HIGH);
        }
        else
        {
            sclk();
        }
    }
    chip_select_high();
    digitalWrite(clock, LOW);
}

void MAX6954::clear(){
    write_string("      ");
}