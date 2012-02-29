#include <Wire.h>
#include <DS1624.h>
/*
  The DS1624 constructor takes the address of the chip. 0-7 inclusive.
  In this case address 1: A0 = high, A1 = low, and A2 = low.
  And it is in the box with my Arduino so I am calling it boxTemp.
*/

DS1624 boxTemp = DS1624(1);

void setup() {
  /*
    I have my DS1624 chip on a small board with a 4 pin
    header pluged in to analog pins 2-5. Using pins A2 
    as power and A3 as ground for my DS1624.  This works
    becasue the DS1624 draws at most 1mA.  If you have
    more power hungry devices on the bus, use the +5v and
    ground pins to power the bus.
  */
  
  pinMode(17,OUTPUT);
  digitalWrite(17, LOW);
  pinMode(16,OUTPUT);
  digitalWrite(16,HIGH);
  
  
/*
  This DS1624 library uses the Wire library, so you have
  to call Wire.begin() before you can use the DS1624 library.
 */
  Wire.begin();

/*
  This puts the DS1624 in one shot mode. It check to see if
  the DS1624 is allready in one shot mode to avoid writing
  to the EEPROM to many times. It has a 50k limit.
 */
  boxTemp.setOneShot();

  Serial.begin(9600);
}



void loop() {
/* In one shot mode this starts one converion. */
  boxTemp.startConversion();

/* This busy waits until the conversion is done, then reads
   it back. If you don't want to busy wait, then you can call
   this function after 1S(max conversion time) or 0.4S(normal
   conversion time at 20C).
 
   *Warning*
   In one shot mode If you have not called startConversion
   since the last time you call temprature, temprature
   will hang.
 */
  float T = boxTemp.temprature();
  Serial.println(T, 4);

}
