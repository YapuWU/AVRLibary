#pragma once
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/twi.h>
#include <util/delay.h>
#include "common.h"
class I2C_ATMEGA
{
	public:
	static void init()
	{
		TWCR |= 1<<TWEN;
		SetLowSpeed();
	}
	static I2CRet begin(uint8_t iAddr, bool bRead)
	{
		bool bLoop = true;
		do
		{
			TWCR = 1<<TWSTA | 1<<TWINT | 1<<TWEN;
			
			iAddr = iAddr<<1;
			if(bRead)
			{
				iAddr |= 0x01;
			}
			
			switch(GetStatus())
			{
				case TW_START:
				case TW_REP_START:
				break;
				default:
				return I2CRet::FAIL;
				break;
			}
			
			switch(internalWrite(iAddr))
			{
				case TW_MT_SLA_NACK:
				case TW_MR_SLA_NACK:
				return I2CRet::NACK;
				break;
				case TW_MT_ARB_LOST:
				break;
				default:
				bLoop = false;
				break;
			}
		}while(bLoop);
		
		return I2CRet::SUCCESS;
	}
	static void end()
	{
		TWCR = 1<<TWINT|1<<TWSTO|1<<TWEN;
	}
	
	static void SetLowSpeed()
	{
		TWBR = CalculateTWBR(F_CPU,100000);
	}
	static void SetHighSpeed()
	{
		TWBR = CalculateTWBR(F_CPU,400000);
	}
	
	static uint8_t read()
	{
		TWCR |= 1<<TWEA;
		TWCR |= 1<<TWINT ;
		GetStatus();
		return TWDR;
	}
	
	static uint8_t read_last()
	{
		TWCR &= ~(1<<TWEA);
		TWCR |= 1<<TWINT ;
		GetStatus();
		return TWDR;
	}
	
	static I2CRet write(uint8_t val)
	{
		I2CRet ret = I2CRet::SUCCESS;
		switch( internalWrite(val))
		{
			case TW_MT_DATA_ACK:
			break;
			case TW_MT_DATA_NACK:
			return I2CRet::NACK;
			break;
			case TW_MT_ARB_LOST:
			TWCR |= 1<<TWINT;
			return I2CRet::LOST_ARB;
			break;
		}
		return ret;
	}
	

	protected:
	static uint8_t GetStatus()
	{
		loop_until_bit_is_set(TWCR,TWINT);
		return TWSR & 0xF8;
	}
	
	private:
	constexpr static uint8_t CalculateTWBR(uint32_t iCpuFreq,uint32_t iFreq)
	{
		return (iFreq*16)>iCpuFreq?0: (uint8_t)(((iCpuFreq/iFreq)-16 )/ 2);
	}
	static inline uint8_t internalWrite(uint8_t val)
	{
		TWDR = val;
		TWCR = 1<<TWINT| 1<<TWEN;
		return GetStatus();
	}
};
