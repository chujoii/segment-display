/*
  ssdrcs.h - Library for "seven segment display RC shift".
  Created by Roman V. Prikhodchenko, October 2, 2010.
  Released into the GPLv3.
 */

#ifndef ssdrcs_h
#define ssdrcs_h

#include "Arduino.h"

class ssdrcs
{
public:
	ssdrcs(byte ssdrcsLedPin);
	void SSDdecimal(int num, boolean zero);
	void SSDhex(byte num, boolean zero);
	byte testSSD();
private:
	byte _ntime;
	byte _strob;
	byte _ssdrcsLedPin;

	void writebit(byte num);
	byte generateSSDonenum(byte num, boolean zero, boolean dot);
	byte writeSSDonenum(byte num, boolean zero, boolean dot);
	byte decimalLO(byte num);
	byte decimalHI(byte num);
	byte hexLO(byte num);
	byte hexHI(byte num);
};

#endif
