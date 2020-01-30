/*
MOD by Beau at SCPS Unlimited 11/1/2019
to be used only with SK6812 32bit RGBW LEDs
*/
/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Required Connections
--------------------
pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
pin 14: LED strip #2    All 8 are the same length.
pin 7:  LED strip #3
pin 8:  LED strip #4    A 100 ohm resistor should used
pin 6:  LED strip #5    between each Teensy pin and the
pin 20: LED strip #6    wire to the LED strip, to minimize
pin 21: LED strip #7    high frequency ringining & noise.
pin 5:  LED strip #8
pin 15 & 16 - Connect together, but do not use
pin 4 - Do not use
pin 3 - Do not use as PWM.  Normal use is ok.

This test is useful for checking if your LED strips work, and which
color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoSK6812.h>

const int ledsPerStrip = 480;

DMAMEM int displayMemory[ledsPerStrip*8];
int drawingMemory[ledsPerStrip*8];

const int config = SK6812_GRBW | WS2811_800kHz;

OctoSK6812 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
    leds.begin();
    leds.show();
    Serial.begin(9600);
    Serial1.begin(9600);
}


// Less intense...

#define THE_WHITE_OF_THE_RGBW 0x000000FF
#define FULL_WHITE_POWER 0xFFFFFFFF

#define RED    0x16000000
#define GREEN  0x00160000
#define BLUE   0x00001600
#define YELLOW 0x10140000
#define PINK   0x12000900
#define ORANGE 0x10040000
#define WHITE  0x10101000
#define PLUM   0xDDA0DD00

#define RED_WITH_WHITE    0x1600000F
#define GREEN_WITH_WHITE  0x0016000F
#define BLUE_WITH_WHITE   0x0000160F
#define YELLOW_WITH_WHITE 0x1014000F
#define PINK_WITH_WHITE   0x1200090F
#define ORANGE_WITH_WHITE 0x1004000F
#define WHITE_WITH_WHITE  0x1010100F

#define COLOR_ONE         0xd9170100
#define COLOR_TWO         0xff5a0000
#define COLOR_THREE       0xfe960000
#define COLOR_FOUR        0xfed29200
#define COLOR_FIVE        0xff8ba000
#define COLOR_SIX         0x9647b400
#define COLOR_SEVEN       0x25137000



void loop() {
    int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

    // uncomment for voltage controlled speed
    // millisec = analogRead(A9) / 40;

    //colorWipe(THE_WHITE_OF_THE_RGBW, microsec);
    //colorWipe(FULL_WHITE_POWER, microsec);

   // colorWipe(RED_WITH_WHITE, microsec);
   // colorWipe(GREEN_WITH_WHITE, microsec);
   // colorWipe(BLUE_WITH_WHITE, microsec);
   // colorWipe(YELLOW_WITH_WHITE, microsec);
   // colorWipe(PINK_WITH_WHITE, microsec);
   // colorWipe(ORANGE_WITH_WHITE, microsec);
   // colorWipe(WHITE_WITH_WHITE, microsec);

   // colorWipe(RED, microsec);    
   // colorWipe(GREEN, microsec);
   // colorWipe(BLUE, microsec);
   // colorWipe(YELLOW, microsec);
   // colorWipe(PINK, microsec);
   // colorWipe(ORANGE, microsec);
   // colorWipe(WHITE, microsec);

/*colorWipe(COLOR_ONE, microsec);
colorWipe(COLOR_TWO, microsec);
colorWipe(COLOR_THREE, microsec);
colorWipe(COLOR_FOUR, microsec);
colorWipe(COLOR_FIVE, microsec);
colorWipe(COLOR_SIX, microsec);
*/
//unsigned long bignumber = (255/16)*pow(16,7) + (255%16)*pow(16,6);
//Serial.println(bignumber);
//delay(2000);
//colorGradient(48,239,189,0,21,37,114,0,1000);
//colorGradient(21,37,114,0,48,239,189,0,1000);
//colorGradient(48,239,189,0,129,255,0,0,1000);
//colorGradient(129,255,0,0,81,255,13,0,1000);
//colorGradient(81,255,13,0,24,255,142,0,1000);
//colorGradient(24, 255, 142, 0, 48, 239, 189, 0, 1000);

int red = 245;
int greenBlue = 100;
int sat = 10;

Serial1.write(0);


colorGradient(10, 30, 0, 30, 0, 0, 0, 0, 5000);
colorGradient(0, 0, 0, 0, 0, 0, 0, 0, 2500);
colorGradient(0, 0, 0, 0, 0, 0, 15, 15, 5000);
colorGradient(0, 0, 15, 15, 0, 0, 15, 15, 2500);
colorGradient(0, 0, 15, 15, 0, 0, 0, 0, 5000);
colorGradient(0, 0, 0, 0, 0, 0, 0, 0, 2500);
colorGradient(0, 0, 0, 0, 30, 50, 0, 30, 5000);
colorGradient(30, 50, 0, 30, 30, 50, 0, 30, 2500);
colorGradient(30, 50, 0, 30, 10, 30, 0, 30, 5000);
colorGradient(10, 30, 0, 30, 10, 30, 0, 30, 2500);

Serial1.write(1);
//colorGradient(greenBlue/sat, red/sat, 0, 0, 0, 200/sat, 50/sat, 0, 5000);

   
}

void colorWipe(int color, int wait)
{
    for (int i=0; i < leds.numPixels(); i++) {
        leds.setPixel(i, color);
        delayMicroseconds(wait);
        if(i%16 == 1){}
            //leds.show();
    }  
    leds.show();
}

unsigned long colorConv (unsigned long red, unsigned long green, unsigned long blue, unsigned long white){
  unsigned long grbw;
  grbw = (green/16)*pow(16,7) + (green%16)*pow(16,6) +
        (red/16)*pow(16,5) + (red%16)*pow(16,4) +
        (blue/16)*pow(16,3) + (blue%16)*pow(16,2) +
        (white/16)*pow(16,1) + (white%16);
  return grbw;
}


void colorGradient (int green, int red, int blue, int white, int green2, int red2, int blue2, int white2, int timer){
  unsigned long fade;
  float increment = 100;
  float distance[] = {(green-green2)/increment, (red-red2)/increment, (blue-blue2)/increment, (white-white2)/increment};
  for (int i=0; i<increment; i++){
    fade = colorConv(green-distance[0]*i, red-distance[1]*i, blue-distance[2]*i, white-distance[3]*i);
    for (int n=0; n<480*8; n++){
    leds.setPixel(n, fade);
    }
    delay(timer/increment);
    leds.show();
  }
}
