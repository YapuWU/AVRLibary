#pragma once
constexpr uint8_t addr = 0x3D;
template<class INTERFACE>
class LCD_SSDBase : public INTERFACE
{
	public:
	
	void init()
	{
		writeCommand(0xA4); // Entire Display ON
		writeCommand(0xAF); //Set Display ON
	}
	void setBlock(uint8_t iColStart,uint8_t iColEnd,uint8_t iRowStart,uint8_t iRowEnd)
	{
		
		writeCommand(iColStart & 0x0F,0x10 | ((iColStart&0xF0)>>4));
		writeCommand(0x20,0x00);  //Horizital mode
		writeCommand(0x21,iColStart,iColEnd);
		
		writeCommand(0x22,iRowStart/8,iRowEnd/8);
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
