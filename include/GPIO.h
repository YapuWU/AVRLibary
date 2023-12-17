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
template<class PORTClass, int pinNum>
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
#ifdef PORTB
using _PORTB = AVRPort<(const int)&PORTB,(const int)&DDRB,(const int)&PINB>;
using _PINB0=AVRPin<_PORTB,0>;
using _PINB1=AVRPin<_PORTB,1>;
using _PINB2=AVRPin<_PORTB,2>;
using _PINB3=AVRPin<_PORTB,3>;
using _PINB4=AVRPin<_PORTB,4>;
using _PINB5=AVRPin<_PORTB,5>;
using _PINB6=AVRPin<_PORTB,6>;
using _PINB7=AVRPin<_PORTB,7>;
#endif

#ifdef PORTC
using _PORTC = AVRPort<(const int)&PORTC,(const int)&DDRC,(const int)&PINC>;
using _PINC0=AVRPin<_PORTC,0>;
using _PINC1=AVRPin<_PORTC,1>;
using _PINC2=AVRPin<_PORTC,2>;
using _PINC3=AVRPin<_PORTC,3>;
using _PINC4=AVRPin<_PORTC,4>;
using _PINC5=AVRPin<_PORTC,5>;
using _PINC6=AVRPin<_PORTC,6>;
using _PINC7=AVRPin<_PORTC,7>;
#endif

#ifdef PORTD
using _PORTD = AVRPort<(const int)&PORTD,(const int)&DDRD,(const int)&PIND>;
using _PIND0=AVRPin<_PORTD,0>;
using _PIND1=AVRPin<_PORTD,1>;
using _PIND2=AVRPin<_PORTD,2>;
using _PIND3=AVRPin<_PORTD,3>;
using _PIND4=AVRPin<_PORTD,4>;
using _PIND5=AVRPin<_PORTD,5>;
using _PIND6=AVRPin<_PORTD,6>;
using _PIND7=AVRPin<_PORTD,7>;
#endif

#ifdef PORTE
using _PORTE = AVRPort<(const int)&PORTE,(const int)&DDRE,(const int)&PINE>;
using _PINE0=AVRPin<_PORTE,0>;
using _PINE1=AVRPin<_PORTE,1>;
using _PINE2=AVRPin<_PORTE,2>;
using _PINE3=AVRPin<_PORTE,3>;
using _PINE4=AVRPin<_PORTE,4>;
using _PINE5=AVRPin<_PORTE,5>;
using _PINE6=AVRPin<_PORTE,6>;
using _PINE7=AVRPin<_PORTE,7>;
#endif

#ifdef PORTF
using _PORTF = AVRPort<(const int)&PORTF,(const int)&DDRF,(const int)&PINF>;
using _PINF0=AVRPin<_PORTF,0>;
using _PINF1=AVRPin<_PORTF,1>;
using _PINF2=AVRPin<_PORTF,2>;
using _PINF3=AVRPin<_PORTF,3>;
using _PINF4=AVRPin<_PORTF,4>;
using _PINF5=AVRPin<_PORTF,5>;
using _PINF6=AVRPin<_PORTF,6>;
using _PINF7=AVRPin<_PORTF,7>;
#endif


