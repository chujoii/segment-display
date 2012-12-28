#include <ssdrcs.h>


ssdrcs ssegment(13);                // initialise an instance of class

void setup()
{
	ssegment.testSSD();
}

void loop()
{
//	for (int i = 0; i<100; i++){
//		ssegment.SSDdecimal(i, true);
//		delay(500);
//	}
	delay(1000);
	
	for (int i = 0; i<255; i++){
	  ssegment.SSDhex(i, true);
	  delay(500);
	}
	delay(1000);
}
