/*
  ssdrcs.cpp - Library for "seven segment display RC shift".
  Created by Roman V. Prikhodchenko, October 2, 2010.
  Released into the GPLv3.
 */

#include <Ssdrcs.h>




Ssdrcs::Ssdrcs(int ssdrcsLedPin)
{
	_ntime = 10;
	_strob = 1;
	_ssdrcsLedPin = ssdrcsLedPin;
	pinMode(_ssdrcsLedPin, OUTPUT);
}



void Ssdrcs::writebit(int num)
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



unsigned int Ssdrcs::generateSSDonenum(unsigned int num, boolean zero, boolean dot)
{

//                                0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f     zero
	unsigned int ssd_num[] = {0xfa, 0x18, 0x76, 0x3e, 0x9c, 0xae, 0xee, 0x38, 0xfe, 0xbe, 0xfc, 0xce, 0x46, 0x5e, 0xe6, 0xe4, 0x00};
	
	if (zero && (0 == num))
		return ssd_num[16];
	else
		if (dot){
			return (ssd_num[num] | 1);
		}
		else
			return ssd_num[num];
}



int Ssdrcs::writeSSDonenum(unsigned int num, boolean zero, boolean dot)
{
	int z = generateSSDonenum(num, zero, dot);
	for (unsigned int i=0; i<8; i++){
		writebit((1<<i)&z);
	}
}



unsigned int Ssdrcs::decimalLO(unsigned int num)
{
	return (num%10);
}

unsigned int Ssdrcs::decimalHI(unsigned int num)
{
	return (decimalLO((num-decimalLO(num))/10));
}


void Ssdrcs::SSDdecimal(unsigned int num, boolean zero)
{
	int lo = decimalLO(num);
	int hi = decimalHI(num);
	
	if (hi>0)
		writeSSDonenum(lo, false, false);
	else
		writeSSDonenum(lo, zero, false);
	writeSSDonenum(hi, zero, false); 
}

int Ssdrcs::testSSD()
{
	writebit(1);
	for (int j=0; j<16; j++){
		writebit(0);
		delay(200);
	}
	writebit(1);
	for (int j=0; j<16; j++){
		writebit(0);
		delay(200);
	}
}







