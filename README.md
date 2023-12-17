# AVRLibary

This library is trying to utilize the C++11 features to benefit AVR MCU development.
1. Use C++ to organize the libraries. Make the libraries easy to expand.
2. Try to keep the compiled binary as small as possible.

This library will include the following modules:
1. GPIO - Basic PORT and PIN operation
2. I2C - I2C protocol support
3. SPI - SPI protocol support
4. LCD - LCD display support(LCD1602 etc.)


## GPIO
Support basic port and pin operations. This is a basic module that will be used by other modules.

using _PORTB = AVRPort<(const int)&PORTB,(const int)&DDRB,(const int)&PINB>;

using _PINB0=AVRPin<_PORTB,PINB0>;
using _PINB1=AVRPin<_PORTB,PINB1>;

_PORTB::DDR(0xFF);

_PINB0::output_mode();
_PINB0::set();

## I2C
Support I2C master operations. It is organized into two parts. The first part is I2C driver layer. This layer will use TWI, USI, or GPIO to perform basic I2C operations.
The second part is a higher layer. It includes many common functions.

### I2C_TWI  - I2C_TWI.h
This class uses TWI hardware to perform I2C operations. This hardware can be found in many ATmega and ATTiny MCUs.

### I2C_GPIO  - I2C_GPIO.h
This class uses GPIO to perform I2C operations. It can be used on any AVR MCU.

### I2C_USI  - I2C_USI.h
This class uses USI hardware to perform I2C operations. USI can be found on some ATTiny MCU.
