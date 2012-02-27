#include "DS1624.h"

#define BASE 72
DS1624_c::DS1624_c(){
	Wire.begin();
}


void DS1624_c::startConversion(uint8_t address){
	Wire.beginTransmission(address | BASE);
	Wire.write(0xEE);
	Wire.endTransmission();
}

void DS1624_c::StopConversion(uint8_t address){
	Wire.beginTransmission(address | BASE);
	Wire.write(0x22);
	Wire.endTransmission();
}

void DS1624_c::setOneShot(uint8_t address){
	uint8_t A = address | BASE;
	if( !(readConfig(A) & 0x01)) {
		Wire.beginTransmission(A);
		Wire.write(0xAC);
		Wire.write(1);
		Wire.endTransmission();
	}
}

void DS1624_c::setContinuous(uint8_t address){
	uint8_t A = address | BASE;
	if( readConfig(A) & 0x01) {
		Wire.beginTransmission(A);
		Wire.write(0xAC);
		int zero = 0; //Stupid C++
		Wire.write(zero);
		Wire.endTransmission();
	}
}

uint8_t DS1624_c::readConfig(uint8_t address){
	uint8_t A = address | BASE;
	Wire.beginTransmission(A);
	Wire.write(0xAC);
	Wire.endTransmission();
	Wire.requestFrom((int)A,1);
	return Wire.read();
}

void DS1624_c::waitForConversion(uint8_t address){ //readConfig deals with BASE address
	uint8_t C = readConfig(address);
	if ((C & 0x1)&&(!(C & 0x80))) { //if oneShot mode and not done
		while(!(readConfig(address) & 0x80)) 
			;// Busy wait until done
	}
}

uint16_t DS1624_c::temprature16(uint8_t address){
	uint8_t A = BASE | address;
	waitForConversion(address);
	Wire.beginTransmission(A);
	Wire.write(0xAA);
	Wire.endTransmission();
	Wire.requestFrom((int)A,2);
	uint8_t temprature = Wire.read();
	uint8_t fraction = Wire.read();
	return (uint16_t)((temprature << 8) | fraction);
}

float DS1624_c::temprature(uint8_t address){
	  int A = BASE | address;
	  waitForConversion(A);
	  Wire.beginTransmission(A);
	  Wire.write(0xAA);
	  Wire.endTransmission();
	  Wire.requestFrom(A,2);
	  int8_t temprature = Wire.read();
	  uint8_t fraction = Wire.read();
	  return toFloat(temprature, fraction);
}

float DS1624_c::toFloat(uint16_t temp){
	int T = (int8_t)((temp && 0xFF00) >> 8); //gcc does evil things with this
	int frac = temp && 0x00FF;
	return toFloat(T,frac);
}

float DS1624_c::toFloat(int8_t T, uint8_t frac){
	return (float)( T + ((frac >> 3) * 0.03125));
}

DS1624_c DS1624 = DS1624_c();


