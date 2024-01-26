#pragma once
#include <stdint.h>

template<class MOSI,class SCK>
class SPI_OUTONLY_GPIO
{
    public:
    static void init()
    {
        MOSI::output_mode();
        SCK::output_mode();
        dataOrder = 0;
    }
    static void write(uint8_t val)
    {
        if(dataOrder)
        {
            writeLSB(val);
        }
        else
        {
            writeMSB(val);
        }
    }
    static void setMSB()
    {
        dataOrder = 0;
    }
    static void setLSB()
    {
        dataOrder = 1;
    }
private:
    static void writeMSB(uint8_t val)
    {
        for(int i=0;i<8;i++)
        {
            if((0x80 & val))
            {
                MOSI::set();
            }
            else
            {
                MOSI::clear();
            }
            val<<=1;
            SCK::set();
            SCK::clear();
        }
    }
    static void writeLSB(uint8_t val)
    {

    }
    static uint8_t dataOrder;  //MSB
};

template<class MOSI,class SCK>
uint8_t SPI_OUTONLY_GPIO<MOSI,SCK>::dataOrder = 0;