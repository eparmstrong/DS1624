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




#include "DS1624.h"

#define BASE 72
DS1624::DS1624(uint8_t A){
	address = A | BASE;
}


void DS1624::startConversion(){
	Wire.beginTransmission(address);
	Wire.write(0xEE);
	Wire.endTransmission();
}

void DS1624::stopConversion(){
	Wire.beginTransmission(address);
	Wire.write(0x22);
	Wire.endTransmission();
}

void DS1624::setOneShot(){
	if( !(readConfig() & 0x01)) {
		Wire.beginTransmission(address);
		Wire.write(0xAC);
		Wire.write(1);
		Wire.endTransmission();
	}
}

void DS1624::setContinuous(){
	if( readConfig() & 0x01) {
		Wire.beginTransmission(address);
		Wire.write(0xAC);
		int zero = 0; //Stupid C++
		Wire.write(zero);
		Wire.endTransmission();
	}
}

uint8_t DS1624::readConfig(){
	Wire.beginTransmission(address);
	Wire.write(0xAC);
	Wire.endTransmission();
	Wire.requestFrom((int)address,1);
	return Wire.read();
}

void DS1624::waitForConversion(){ 
	uint8_t C = readConfig();
	if ((C & 0x1)&&(!(C & 0x80))) { //if oneShot mode and not done
		while(!(readConfig() & 0x80)) 
			;// Busy wait until done
	}
}

uint16_t DS1624::temprature16(){
	waitForConversion();
	Wire.beginTransmission(address);
	Wire.write(0xAA);
	Wire.endTransmission();
	Wire.requestFrom((int)address,2);
	uint8_t temprature = Wire.read();
	uint8_t fraction = Wire.read();
	return (uint16_t)((temprature << 8) | fraction);
}

float DS1624::temprature(){
	  waitForConversion();
	  Wire.beginTransmission(address);
	  Wire.write(0xAA);
	  Wire.endTransmission();
	  Wire.requestFrom((int)address,2);
	  int8_t temprature = Wire.read();
	  uint8_t fraction = Wire.read();
	  return toFloat(temprature, fraction);
}

float DS1624::toFloat(uint16_t temp){
	int T = (int8_t)((temp && 0xFF00) >> 8); //gcc does evil things with this
	int frac = temp && 0x00FF;
	return toFloat(T,frac);
}

float DS1624::toFloat(int8_t T, uint8_t frac){
	return (float)( T + ((frac >> 3) * 0.03125));
}



