#pragma once
template<class I2C>
class LCDSSD_I2C
{
	public:	
	void setAddress(uint8_t addr)
	{
		m_iAddress = addr;
	}
	void beginCommand()
	{
		I2C::begin(m_iAddress,false);
		I2C::write(0x00);
	}
	void beginData()
	{
		I2C::begin(m_iAddress,false);
		I2C::write(0x40);
		
	}
	void end()
	{
		I2C::end();
	}
	void write(uint8_t val)
	{
		I2C::write(val);
	}
	private:
	uint8_t m_iAddress;
};