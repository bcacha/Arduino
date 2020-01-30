#define NUM_LEDS    64
#include <FastLED.h>
CRGB leds[NUM_LEDS];

int threshold = 600;
int color = 0;
int calibration[] = {0, 0, 0, 0};
int timeStart[] = {0, 0, 0, 0};
int average[] = {0, 0, 0, 0};
int count[] = {0, 0, 0, 0};
int total[] = {0, 0, 0, 0};
int timer[] = {0, 0, 0, 0};

bool startTimer[] = {false, false, false, false};
bool triggers[] = {false, false, false, false};
bool change[] = {false, false, false, false};
// comment added by Samuel M.

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  //Calibration
  int totalC[] = {0, 0, 0, 0};
  int sensorValueC[] = {analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};
  
  Serial.println("Calibrating");
  for (int n=0; n<500; n++){
    for (int i=0; i<4; i++){
        totalC[i] = totalC[i] + sensorValueC[i]; 
    }
    delay(10);
  }

  for (int i=0; i<4; i++){
    calibration[i] = totalC[i]/500;
    Serial.println(calibration[i]);
  }
  
  digitalWrite(13, LOW);
  FastLED.addLeds<WS2812, 12, GRB>(leds, NUM_LEDS);
    for (int i=0; i<NUM_LEDS; i++){
      leds[i] =  CRGB(0,0,0);
    } 
  FastLED.show();
}

void loop() {

  color = color%255 + 2;

  int sensorValue[] = {analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};
  Serial.print(0); Serial.print(" ");
  Serial.println(1023);
  
  for (int i=0; i<4; i++){
    sensorValue[i] = ((sensorValue[i] - calibration[i])*1023)/(1023-calibration[i]);
    Serial.print(sensorValue[i]); Serial.print(" ");
    if (sensorValue[i] > threshold){
      triggers[i] = true;
    }
    else{
      triggers[i] = false;
    }
    ledLighting(i, triggers);
    if (triggers[i] != change[i] && startTimer[i] == false){
      Serial.print("time start for ");
      Serial.println(String(i));
      timeStart[i] = millis();
      startTimer[i] = true;
    }
    sendTrigger(i, sensorValue[i]);
    change[i] = triggers[i];
  }
  FastLED.show();
  delay(10);
}

//-----------------------------------------------------------------------------------------------------

void sendTrigger(int i, int sensorValue){
    if (startTimer[i] == true){
      timer[i] = 1000 - (millis()-timeStart[i]);
      if (timer[i] > 0){
        count[i]++;
        total[i] = total[i] + sensorValue;
      }
      else{
        average[i] = total[i]/count[i];
        startTimer[i] = false;
        Serial.print("Average[");
        Serial.print(String(i));
        Serial.print("]: ");
        Serial.println(average[i]);
        if (average[i] >= threshold && triggers[i] == true){
          printValues();
        }
        if (average[i] < threshold && triggers[i] == false){
          printValues();
        }
        total[i] = 0;
        count[i] = 0;
      }
    }
}


void printValues(){
  for (int i=0; i<4; i++){
    if (i<3){
      Serial1.print(triggers[i]);
      Serial1.print(", ");
    }
    else{
      Serial1.println(triggers[i]);
    }
  }
}


void ledLighting(int i, bool triggers[]){
    if (triggers[0]==false || triggers[1]==false || triggers[2]==false || triggers[3]==false){ 
      if (triggers[i] == true){
        changeColor(i);
      }
      else{
        turnOff(i);
      }
    }
    else{
      rainbowSweep(i);
    }
}


void changeColor(int i){
    for (int n=i*16; n<(i*16)+16; n++){
      leds[n] =  CHSV((i*64),255,255);
    }
}


void turnOff(int i){
    for (int n=i*16; n<(i*16)+16; n++){
      leds[n] =  CHSV(0,0,0);
    }
}


void rainbowSweep(int i){
    for (int n=0; n<NUM_LEDS; n++){
      leds[n] =  CHSV((color%255)+(n*4),255,255);
    }
}
