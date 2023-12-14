#pragma once
#include <avr/io.h>
#include <avr/sfr_defs.h>

/* usage example

using _PORTB = AVRPort<(const int)&PORTB,(const int)&DDRB,(const int)&PINB>;
using _PORTC = AVRPort<(const int)&PORTC,(const int)&DDRC,(const int)&PINC>;
using _PORTD = AVRPort<(const int)&PORTD,(const int)&DDRD,(const int)&PIND>;

using _PINB0=AVRPin<_PORTB,PINB0>;
using _PINB1=AVRPin<_PORTB,PINB1>;

*/


template<uint16_t port_addr,uint16_t ddr_addr,uint16_t pin_addr>
class AVRPort
{
#define AVRPort_PORT  (*((volatile uint8_t*)(port_addr)))
#define AVRPort_DDR  (*((volatile uint8_t*)(ddr_addr)))
#define AVRPort_PIN  (*((volatile uint8_t*)(pin_addr)))
	public:	
	static __attribute__((always_inline)) uint8_t DDR()
	{
		return AVRPort_DDR;
	}
	static __attribute__((always_inline)) void DDR(uint8_t val)
	{
		AVRPort_DDR = val;
	}
	static __attribute__((always_inline)) uint8_t PORT()
	{
		return AVRPort_PORT;
	}
	static __attribute__((always_inline)) void PORT(uint8_t val)
	{
		AVRPort_PORT = val;
	}
	
	static __attribute__((always_inline)) uint8_t PIN()
	{
		return AVRPort_PIN;
	}
	static __attribute__((always_inline)) void PIN(uint8_t val)
	{
		AVRPort_PIN = val;
	}
	
};
template<class PORTClass,int pinNum>
class AVRPin
{
	public:
	static __attribute__((always_inline)) void enable_pullup()
	{
		set();
	}
	
	static __attribute__((always_inline)) void disable_pullup()
	{
		clear();
	}
	
	static __attribute__((always_inline)) void output_mode()
	{
		PORTClass::DDR(PORTClass::DDR() | 1<<pinNum);
	}
	
	static __attribute__((always_inline)) void input_mode()
	{
		PORTClass::DDR(PORTClass::DDR() & ~(1<<pinNum));
	}
	
	static __attribute__((always_inline)) void set()
	{
		PORTClass::PORT(PORTClass::PORT() | 1<<pinNum);
	}
	
	static __attribute__((always_inline)) void clear()
	{
		PORTClass::PORT(PORTClass::PORT() & ~(1<<pinNum));
	}
	
	static __attribute__((always_inline)) uint8_t get()
	{
		return PORTClass::PIN() & (1<<pinNum);
	}
	
	static __attribute__((always_inline)) uint8_t toggle()
	{
		return PORTClass::PIN(PORTClass::PIN() |(1<<pinNum));
	}
};

