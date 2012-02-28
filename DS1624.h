/*
   Copyright 2012 Eric Armstrong.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
