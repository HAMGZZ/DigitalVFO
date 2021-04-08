#include <Arduino.h>
#include "MD_AD9833.h"
#include <SPI.h>



/*
 * Rotaory a & b = 4 & 5;
 * rot buntton = pin 2;
*/

// Pins for SPI comm with the AD9833 IC on Uno
#define DATA  11	    // SPI Data/MOSI pin number.  Meg 2560 uses pin 51
#define CLK   13	    // SPI Clock pin number.  Mega 2560 uses pin 52
#define FSYNC 10	    // SPI Load/SS pin number.  Mega 2560 uses pin 53


#define CLK2 4
#define DATA2 5
#define BOT_FREQ 4900000
#define TOP_FREQ 5500000
#define START_FREQ 5000000
#define OFFSET 202

MD_AD9833	AD(FSYNC);  // Hardware SPI

int Freq_Step = 50;

long int lastPulse = 0;


void button();

static int prevNextCode = 0;
static uint16_t store=0;
long int count = 0;

float setFreq = 10;
int MAX_COUNT  = 10;

void rotary();
int read_rotary();

void setup() {
  
  pinMode(CLK2, INPUT);
  pinMode(CLK2, INPUT_PULLUP);
  pinMode(DATA2, INPUT);
  pinMode(DATA2, INPUT_PULLUP);
  pinMode(15, OUTPUT);
  Serial.begin(9600);
  Serial.println("Waiting 2 seconds");
  delay(2000);
  AD.begin();
  Serial.println("AD.Begin");
  AD.setMode(MD_AD9833::MODE_SINE);
  Serial.println("AD.SetWaveform, SINE");
  AD.setFrequency(MD_AD9833::CHAN_0, BOT_FREQ);
  Serial.println("AD.SetFrequency, 4900000");
  
  count = (START_FREQ - BOT_FREQ);
  MAX_COUNT = (TOP_FREQ - BOT_FREQ);
  Serial.println(count);
  Serial.println(MAX_COUNT);
  digitalWrite(15, HIGH);
}

void loop() {
  float curFreq  = 0;

  while(1)
  {  
    rotary();
    setFreq = BOT_FREQ + count;
    if(setFreq != curFreq)
    {
      AD.setFrequency(MD_AD9833::CHAN_0, setFreq + OFFSET);
      Serial.printf("FREQ: %lf\r\n", setFreq);
      curFreq = setFreq;
    }
  }
}




void rotary()
{
  signed int temp = read_rotary();
  long int currentPulse = 0;
  if(temp != 0 && (count >= 0 && count <= MAX_COUNT))
  {
     currentPulse = millis();
     float timeDif = currentPulse - lastPulse;
     float value = (pow(10,round((1/(timeDif/4)))));
     if(value > 1000)
      value = 1000;
     count += temp * value;
     Serial.printf("T: %lf \t\t D: %d \t\t V: %lf \t\t C: %d\n\r",timeDif, temp, value, count);
     lastPulse = currentPulse;
  }
  else if(temp == -1 && count < 0)
  {
     count = MAX_COUNT;
  }
  else if(temp == 1 && count > MAX_COUNT)
  {
     count = 0;
  }
}

// A vald CW or  CCW move returns 1, invalid returns 0.
int read_rotary() 
{
  static int rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode <<= 2;
  if (digitalRead(DATA2)) prevNextCode |= 0x02;
  if (digitalRead(CLK2)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   return 0;
}