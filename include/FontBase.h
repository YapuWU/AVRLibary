#pragma once
template<class FontDESC>
class FontBase
{
public:
	static constexpr uint8_t width()
	{
		return FontDESC::width;
	}
	static constexpr uint8_t height()
	{
		return FontDESC::height;
	}
	static constexpr uint8_t bytesPerChar()
	{
		return FontDESC::width * FontDESC::height / 8;
	}
	static bool getChar(const char c, uint8_t* pBuffer, uint8_t iBufLen)
	{
		if (c< FontDESC::first || c>FontDESC::last || iBufLen!=bytesPerChar())
		{
			return false;
		}
		for(uint8_t i=0;i<bytesPerChar();i++)
		{
			pBuffer[i] = FontDESC::getByte(c-FontDESC::first,i);
		}
		return true;
	}
	
	
};
