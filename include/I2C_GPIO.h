#pragma  once
#include <avr/io.h>
#include <util/delay.h>

#include "common.h"


template< class SCL, class SDA ,int delayInUS=4>
class I2C_GPIO
{
	public:
	static void init()
	{
		SCL::clear();
		SDA::clear();
		SCL::input_mode();
		SDA::input_mode();
	}
	static I2CRet begin(uint8_t iAddr, bool bRead)
	{
		release_sda();
		release_scl();
		delayClock();
		hold_sda();
		delayClock();
		hold_scl();
		delayClock();
		
		return write(iAddr<<1 |(bRead?1:0));
	}
	static void end()
	{
		hold_sda();
		release_scl();
		delayClock();
		release_sda();
		delayClock();
	}
	
	static void SetLowSpeed()
	{
	}
	static void SetHighSpeed()
	{
	}
	
	static uint8_t read()
	{
		uint8_t iRet = 0;
		
		for(uint8_t i=0;i<8;i++)
		{
			iRet <<= 1;
			if(readbit()==I2CRet::NACK)
			{
				iRet|=1;
			}
		}
		writebit(0);
		return iRet;		
	}
	static uint8_t read_last()
	{
		uint8_t iRet = 0;
		
		for(uint8_t i=0;i<8;i++)
		{
			iRet <<= 1;
			if(readbit()==I2CRet::NACK)
			{
				iRet|=1;
			}
		}
		writebit(1);
		return iRet;
	}
	static I2CRet readbit()
	{
		I2CRet ret = I2CRet::NACK;
		
		release_sda();
		delayClock();
		release_scl();
		delayClock();
		if(SDA::get()==0)
		{
			ret = I2CRet::SUCCESS;
		}
		hold_scl();
		return ret;
	}
	static void writebit(bool bit)
	{
		if(bit)
		{
			release_sda();
		}
		else
		{
			hold_sda();
		}
		delayClock();
		release_scl();
		delayClock();
		hold_scl();
	}
	static I2CRet write(uint8_t val)
	{
		for(uint8_t i=0;i<8;i++)
		{
			writebit(val & 0x80);
			val = val<<1;
		}
		
		return readbit();
	}

	protected:
	__attribute__((always_inline)) static void hold_scl()
	{
		SCL::output_mode();
	}
	static void release_scl()
	{
		SCL::input_mode();
		while(SCL::get()==0);
	}
	__attribute__((always_inline)) static void hold_sda()
	{
		SDA::output_mode();
	}
	__attribute__((always_inline)) static void release_sda()
	{
		SDA::input_mode();
	}
	__attribute__ ((noinline)) static void delayClock()
	{
		_delay_us(delayInUS);
	}
};
