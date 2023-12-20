#pragma once
template<class FontDESC= FontBytes6X8>
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
    //TODO read program space
		const uint8_t* pCharBuf = FontDESC::font[c - FontDESC::first];
		memcpy(pBuffer, pCharBuf, iBufLen);
		return true;
	}
	static bool outputChar(const char c,void (*OUT)(void*,uint8_t),void* pObj)
	{
		if (c< FontDESC::first || c>FontDESC::last)
		{
			return false;
		}
    //TODO read program space
		const uint8_t* pCharBuf = FontDESC::font[c - FontDESC::first];
		for (uint8_t i = 0; i < bytesPerChar(); i++)
		{
			OUT(pObj, pCharBuf[i]);
		}
		return true;
	}
};
