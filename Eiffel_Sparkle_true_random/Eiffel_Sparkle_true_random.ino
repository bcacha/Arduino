#include <OctoWS2811.h>

const int ledsPerStrip = 624;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

const int strips = 3;
int n = 0;
int power = 8;
int speed = 5;
int brightness = 100;
int color = 60;
int saturation = 15;
int timeBetween = 1500;
int randTimer[ledsPerStrip*strips];
int timeNow[ledsPerStrip*strips];
int iterationArray[ledsPerStrip*strips];
int brightArray[100];
bool startTime[ledsPerStrip*strips];


void setup() {

  Serial.begin(9600);  
//  delay(2000);
  randomSeed(analogRead(0));

  for (int i=0; i<ledsPerStrip*strips; i++){
    startTime[i] = false;
    timeNow[i] = 0;
    randTimer[i] = random(timeBetween);
  }

  for (int i=0; i<50; i++){
    brightArray[i] = (pow(i,power)*brightness)/pow(49, power);
  }  
  for (int i=50; i>=0; i--){
    brightArray[100-i] = (pow(i,power)*brightness)/pow(50, power);
  }  

  leds.begin();
  leds.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<ledsPerStrip*strips; i++){
    if (startTime[i] == false){
      //Do iteration
      int bright = (iterationArray[i] + 101 - n)%100;
//      Serial.print("[");
//      Serial.print(i);
//      Serial.print(", ");
//      Serial.print(brightArray[bright]);
//      Serial.print("]");
      leds.setPixel(i, makeColor(color, saturation, brightArray[bright]));
      if (bright == 1){
        startTime[i] = true;      
        timeNow[i] = millis();
        randTimer[i] = random(timeBetween);
      }
    }
    if (startTime[i] == true){
      int timer = randTimer[i] - (millis() - timeNow[i]);
//      Serial.print(timer);
//      Serial.print(", ");
      if (timer < 0){
        startTime[i] = false;
        iterationArray[i] = n;
      }
    }
  }
  leds.show();
//  Serial.println();
  delay(speed);
  n++;
  n = n%100;
}
