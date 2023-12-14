#pragma once

/************************************************************************
define common constant for the library
************************************************************************/

//define the return value for I2C
enum class I2CRet:uint8_t
{
	SUCCESS=0,
	FAIL = 1,
	NACK = 2,
	LOST_ARB = 3
};
