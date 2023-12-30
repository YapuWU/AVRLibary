#pragma once
constexpr uint8_t addr = 0x3D;
template<class INTERFACE>
class LCD_SSDBase : public INTERFACE
{
	public:
	
	void init()
	{
		writeCommand(0x8D,0x14); //enablecharge pump
		writeCommand(0xA4); // Entire Display ON
		writeCommand(0xAF); //Set Display ON
		writeCommand(0xA1,0xC8);
		clear();
	}
	void setBlock(uint8_t iColStart,uint8_t iColEnd,uint8_t iRowStart,uint8_t iRowEnd)
	{
		
		writeCommand(iColStart & 0x0F,0x10 | ((iColStart&0xF0)>>4));
		writeCommand(0x20,0x00);  //Horizital mode
		writeCommand(0x21,iColStart,iColEnd);
		
		writeCommand(0x22,iRowStart/8,iRowEnd/8);
	}
	void clear()
	{
		setBlock(0,127,0,63);
		INTERFACE::beginData();
		for(int i=0;i<128*8;i++)
		{
			INTERFACE::write(0);
		}
		INTERFACE::end();
	}
	//protected:
	template<class... Args>
	void writeCommand(Args... args)
	{
		INTERFACE::beginCommand();
		int a[] = {(INTERFACE::write(args),0)...};
		(void)a;
		INTERFACE::end();
	}
};
