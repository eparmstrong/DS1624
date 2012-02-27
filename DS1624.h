
#ifndef DS1624_h
#define DS1624_h

#include <Wire.h>
extern "C" {
#include <stdint.h>
}

class DS1624_c
{
	public:
		DS1624_c();
		void startConversion(uint8_t);
		void stopConversion(uint8_t);
		void setOneShot(uint8_t);
		void setContinuous(uint8_t);
		uint8_t readConfig(uint8_t);
		uint16_t temprature16(uint8_t);
		void waitForConversion(uint8_t);
		float temprature(uint8_t);
		float toFloat(uint16_t);
		float toFloat(int8_t,uint8_t);
};

extern DS1624_c DS1624;

#endif
