#pragma  once
#include <stdint.h>


#include "common.h"

/************************************************************************
The requirement for I2C_Base Class
I2C_Base should be a I2c driver for the I2C hardware,
The following functions are required:
static void init();
static RETSTATUS begin(uint8_t iAddr, bool bRead);
static void end();
bLowSpeed=true  means 100Kbps
bLowSpeed=false means 400kbps
static void SetSpeed(bool bLowSpeed=true);
if bLast==true, I2C master will reply with NACK to the peer to inform that this is the last byte to request
static void set_last(bool bLast);
static uint8_t read();
static RETSTATUS write(uint8_t val);

************************************************************************/


template<class I2C_Base>
class I2C_Master : public I2C_Base
{
	public:
	using I2C_Base::read;
	static uint16_t read(uint8_t* pBuffer, int16_t iLen,bool bNACK = true)
	{
		int16_t i = 0;
		for (int16_t i = 0; i < iLen-1; i++)
		{
			pBuffer[i] = I2C_Base::read();
		}
		if(bNACK)
			pBuffer[i] = I2C_Base::read_last();
		else
			pBuffer[i] = I2C_Base::read();
		
		return iLen;
	}
	using I2C_Base::write;
	static uint16_t  write(const uint8_t* pBuffer, int16_t iLen)
	{
		for (int16_t i = 0; i < iLen; i++)
		{
			switch(I2C_Base::write(pBuffer[i]))
			{
				case I2CRet::LOST_ARB:
				return i;
				break;
				case I2CRet::NACK:
				return i+1;
				break;
				default:
				break;
			}
		}
		return iLen;
	}

	static uint16_t   request(uint8_t iAddr, uint8_t* pBuffer, int16_t iLen)
	{
		uint16_t iRet = 0;
		if (I2C_Base::begin(iAddr, true)==I2CRet::SUCCESS)
		{
			iRet = read(pBuffer, iLen);
		}
		I2C_Base::end();
		return iRet;
	}
	static uint16_t   transmit(uint8_t iAddr, uint8_t* pBuffer, int16_t iLen)
	{
		uint16_t iRet = 0;
		if (I2C_Base::begin(iAddr, false)==I2CRet::SUCCESS)
		{
			iRet = write(pBuffer, iLen);
		}
		I2C_Base::end();
		return iRet;
	}
	template<class T=uint8_t>
	static uint16_t   readRegister(uint8_t iAddr, T regAddr,uint8_t* pBuffer, int16_t iLen)
	{
		uint16_t iRet = 0;
		if (I2C_Base::begin(iAddr, false)==I2CRet::SUCCESS)
		{
			const uint8_t* pAddr = (const uint8_t*)&regAddr;
			int8_t iAddrLen = sizeof(T);
			while(iAddrLen)
			{
				write(pAddr[iAddrLen-1]);
				iAddrLen--;
			}
			I2C_Base::begin(iAddr, true);
			read(pBuffer,iLen);
		}
		I2C_Base::end();
		return iRet;
	}
	
	static uint16_t   writeRegister(uint8_t iAddr, uint8_t regAddr,uint8_t* pBuffer, int16_t iLen)
	{
		uint16_t iRet = 0;
		if (I2C_Base::begin(iAddr, false)==I2CRet::SUCCESS)
		{
			write(regAddr);
			
			iRet = write(pBuffer,iLen);
		}
		I2C_Base::end();
		return iRet;
	}
	protected:
};

//-fno-threadsafe-statics   needed to compile