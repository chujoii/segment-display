/*
  ssdrcs.h - Library for "seven segment display RC shift".
  Created by Roman V. Prikhodchenko, October 2, 2010.
  Released into the GPLv3.
 */

#ifndef Ssdrcs_h
#define Ssdrcs_h

#include "WProgram.h"

class Ssdrcs
{
public:
	Ssdrcs(int ssdrcsLedPin);
	void SSDdecimal(unsigned int num, boolean zero);
	int testSSD();
private:
	int _ntime;
	int _strob;
	int _ssdrcsLedPin;

	void writebit(int num);
	unsigned int generateSSDonenum(unsigned int num, boolean zero, boolean dot);
	int writeSSDonenum(unsigned int num, boolean zero, boolean dot);
	unsigned int decimalLO(unsigned int num);
	unsigned int decimalHI(unsigned int num);
};

#endif
