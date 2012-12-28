/*
  ssdrcs.cpp - Library for "seven segment display RC shift".
  Created by Roman V. Prikhodchenko, October 2, 2010.
  Released into the GPLv3.
 */

#include <ssdrcs.h>




ssdrcs::ssdrcs(byte ssdrcsLedPin)
{
	_ntime = 10;
	_strob = 1;
	_ssdrcsLedPin = ssdrcsLedPin;
	pinMode(_ssdrcsLedPin, OUTPUT);
}



void ssdrcs::writebit(byte num)
{
	if (0 != num){
		digitalWrite(_ssdrcsLedPin, LOW);
		delayMicroseconds(_ntime); //delay(_ntime);
		digitalWrite(_ssdrcsLedPin, HIGH);
	}
	else{
		digitalWrite(_ssdrcsLedPin, HIGH);
		delayMicroseconds(_ntime); //delay(_ntime);
		digitalWrite(_ssdrcsLedPin, LOW);
		delayMicroseconds(_strob);
		digitalWrite(_ssdrcsLedPin, HIGH);
	}
}



byte ssdrcs::generateSSDonenum(byte num, boolean zero, boolean dot)
{

//                        0     1     2     3     4     5     6     7     8     9     a 10  b 11  c 12  d 13  e 14  f 15 empty16 minus17
	byte ssd_num[] = {0xfa, 0x18, 0x76, 0x3e, 0x9c, 0xae, 0xee, 0x38, 0xfe, 0xbe, 0xfc, 0xce, 0x46, 0x5e, 0xe6, 0xe4, 0x00, 0x04};
	
	if (zero && (0 == num))
		return ssd_num[16];
	else
		if (dot){
			return (ssd_num[num] | 1);
		}
		else
			return ssd_num[num];
}



byte ssdrcs::writeSSDonenum(byte num, boolean zero, boolean dot)
{
	byte z = generateSSDonenum(num, zero, dot);
	for (byte i=0; i<8; i++){
		writebit((1<<i)&z);
	}
}



byte ssdrcs::decimalLO(byte num)
{
	return (num%10);
}

byte ssdrcs::decimalHI(byte num)
{
	return (decimalLO((num-decimalLO(num))/10));
}


void ssdrcs::SSDdecimal(int num, boolean zero)
{
	byte smallnum;
	
	smallnum=byte(abs(num));

	byte lo = decimalLO(smallnum);
	byte hi = decimalHI(smallnum);

	if ((num<0) && (hi==0)) {hi = 17;}
	
	if (hi>0)
		writeSSDonenum(lo, false, false);
	else
		writeSSDonenum(lo, zero, false);

	writeSSDonenum(hi, zero, false); 
}



byte ssdrcs::hexLO(byte num)
{
	return (num & 0x0F);
}

byte ssdrcs::hexHI(byte num)
{
	return (num >> 4);
}


void ssdrcs::SSDhex(byte num, boolean zero)
{
	byte lo = hexLO(num);
	byte hi = hexHI(num);
	
	if (hi>0)
		writeSSDonenum(lo, false, false);
	else
		writeSSDonenum(lo, zero, false);
	writeSSDonenum(hi, zero, false); 
}

byte ssdrcs::testSSD()
{
	writebit(1);
	for (byte j=0; j<16; j++){
		writebit(0);
		delay(200);
	}
	writebit(1);
	for (byte j=0; j<16; j++){
		writebit(0);
		delay(200);
	}
}







