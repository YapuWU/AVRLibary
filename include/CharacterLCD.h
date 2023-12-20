#pragma once
template<class LCDBase>
class CharacterLCD : public LCDBase
{
	public:
	template<class FONT>
	void text(uint8_t iCol,uint8_t iRow,uint8_t iChar)
	{
		LCDBase::setBlock(iCol,iCol+FONT::width - 1,iRow,iRow+FONT::height-1);
		LCDBase::beginData();
		for(uint8_t i = 0;i<FONT::bytesPerChar;i++)
		{
			LCDBase::write(FONT::getByte(iChar,i));
			//_delay_ms(100);
		}
		LCDBase::end();
	}	
	
	template<class FONT>
	void text(uint8_t iCol,uint8_t iRow,const char* cStr)
	{
		uint8_t iColStart = iCol;
		while(*cStr!='\0')
		{
			text<FONT>(iColStart,iRow,*cStr);
			cStr++;
			iColStart += FONT::width;
		}
		
	}
};
