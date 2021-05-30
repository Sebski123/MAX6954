//#include "Arduino.h"
#include "MAX6954.h"

MAX6954::MAX6954(uint8_t mosi, uint8_t sck, uint8_t cs)
{
    hwSPI = false;

    this->mosi = mosi;
    this->sck = sck;
    this->cs = cs;

    pinMode(this->mosi, OUTPUT);
    pinMode(this->sck, OUTPUT);
    pinMode(this->cs, OUTPUT);

    digitalWrite(this->sck, LOW);
    digitalWrite(this->mosi, LOW);
    digitalWrite(this->cs, HIGH);
}

MAX6954::MAX6954(uint8_t cs, SPIClass *theSPI)
{
    hwSPI = true;

    this->cs = cs;

    pinMode(this->cs, OUTPUT);
    digitalWrite(this->cs, HIGH);
    _spi = theSPI;
    _spi->begin();
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

void MAX6954::send_data(byte address, byte data)
{
    if (hwSPI)
    {
        byte b0, b1, b2;

        _spi->beginTransaction(SPISettings(26000000, MSBFIRST, SPI_MODE0));
        digitalWrite(cs, LOW);

        b0 = _spi->transfer(address);
        b1 = _spi->transfer(data);

        digitalWrite(cs, HIGH);
        _spi->endTransaction();
    }
    else
    {
        send_address(address);
        send_data(data);
    }
}

void MAX6954::write_char(char c, int col /*= 0*/)
{
    send_data(0x20 + col, c);
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

void MAX6954::pulse_clock()
{
    digitalWrite(sck, HIGH);
    digitalWrite(sck, LOW);
}

void MAX6954::send_address(byte address)
{
    char abit;
    char index;
    CS_LOW
    for (index = 7; index >= 0; index--)
    {
        abit = ((address >> index) & 0x01);
        if (abit == 1)
        {
            digitalWrite(mosi, HIGH);
            pulse_clock();
        }
        else
        {
            digitalWrite(mosi, LOW);
            pulse_clock();
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
            digitalWrite(mosi, HIGH);
        }
        else
        {
            digitalWrite(mosi, LOW);
        }
        if (index == 0)
        {
            digitalWrite(sck, HIGH);
        }
        else
        {
            pulse_clock();
        }
    }
    CS_HIGH
    digitalWrite(sck, LOW);
}

void MAX6954::clear()
{
    for (int i = 0; i < 6; i++)
    {
        send_data(0x20 + i, ' ');
    }
}