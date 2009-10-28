int ssdledPin = 12;
int ledPin = 13;
int ntime = 10;
int strob = 1;
//                        0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f     zero
unsigned int ssd_num[] = {0xfa, 0x18, 0x76, 0x3e, 0x9c, 0xae, 0xee, 0x38, 0xfe, 0xbe, 0xfc, 0xce, 0x46, 0x5e, 0xe6, 0xe4, 0x00};



void setup()
{
	pinMode(ssdledPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
}



void writebit(int num)
{
	if (0 != num){
		digitalWrite(ssdledPin, LOW);
		delayMicroseconds(ntime); //delay(ntime);
		digitalWrite(ssdledPin, HIGH);
	}
	else{
		digitalWrite(ssdledPin, HIGH);
		delayMicroseconds(ntime); //delay(ntime);
		digitalWrite(ssdledPin, LOW);
		delayMicroseconds(strob);
		digitalWrite(ssdledPin, HIGH);
	}
}



unsigned int generateSSDonenum(unsigned int num, boolean zero, boolean dot)
{
	if (zero && (0 == num))
		return ssd_num[16];
	else
		if (dot){
			return (ssd_num[num] | 1);
		}
		else
			return ssd_num[num];
}



int writeSSDonenum(unsigned int num, boolean zero, boolean dot)
{
	int z = generateSSDonenum(num, zero, dot);
	for (unsigned int i=0; i<8; i++){
		writebit((1<<i)&z);
	}
}



unsigned int decimalLO(unsigned int num)
{
	return (num%10);
}

unsigned int decimalHI(unsigned int num)
{
	return (decimalLO((num-decimalLO(num))/10));
}


void SSDdecimal(unsigned int num, boolean zero)
{
	int lo = decimalLO(num);
	int hi = decimalHI(num);
	
	if (hi>0)
		writeSSDonenum(lo, false, false);
	else
		writeSSDonenum(lo, zero, false);
	writeSSDonenum(hi, zero, false); 
}

int testSSD()
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



void loop()
{
	testSSD();

	int i;
	for (i=0; i<200; i++){
		SSDdecimal(i, true);
		delay(300);
	}
}
