int openTime = 14000;
int closeTime = 14000;
unsigned int pumpTime = 50000;
//int sequence = 0;
int timeBetween = 5; // time(ms) in between each digitalWrite
int numLoop = 5; // number of times to repeat the digitalWrite command

void setup(){
  Serial.begin(9600);
  for (int i=2; i<8; i++){
    pinMode(i, OUTPUT);   // digital sensor is on digital pin 2
    digitalWrite(i, HIGH);
    delay(5);
  }
  Serial.println("clearing tanks");
  reset();
  Serial.println("pumping dirty tank");
  dirtyPump();
  Serial.println("Ready");  
}

void loop(){
  int buttonValue = analogRead(A6);
  int resetButton = analogRead(A7);
  
  if (buttonValue > 900){
    Serial.println("clean pump");
    cleanPump();
    delay(5000);
    dirtyPump();
  } 
//  Serial.println(buttonValue);
//
//  if (buttonValue > 900){
//    for (int i=0; i<60; i++){
//      Serial.println("clean pump");
//      cleanPump();
//      delay(5000);
//      Serial.println("dirty pump");
//      dirtyPump();
//      buttonValue = analogRead(A6);
//      Serial.println(i);
//      delay(15000);
//      if (buttonValue > 900){
//        i = 120;
//        Serial.println("exiting loop");
//      }
//    }
//    delay(10000);
//  }

//  if (sequence == 0){
//    if (buttonValue > 900){
//      Serial.println("clean pump");
//      cleanPump();
//      sequence = 1;
//    }
//  }
//  buttonValue = analogRead(A6);
//  if (sequence == 1){
//    if (buttonValue > 900){
//      Serial.println("dirty pump");
//      dirtyPump();
//      sequence = 0;
//    }
//  }
  
}


//--------------------------------------------------------------------------------------------------------------


void cleanPump(){
  for (int i=0; i<numLoop; i++){
    digitalWrite(3, LOW); // clean water pump
    delay(timeBetween);
  }
    delay(1000);
    digitalWrite(4, LOW); // dirty valve open
    delay(timeBetween);
    delay(6250);
  for (int i=0; i<numLoop; i++){
    digitalWrite(4, HIGH); // dirty valve stop opening
    delay(timeBetween);
  }
  delay(15500);
    delay(pumpTime-34000);
  for (int i=0; i<numLoop; i++){
    digitalWrite(5, LOW); // dirty valve close
    delay(timeBetween);
    digitalWrite(3, HIGH); // clean water stop pumping
    delay(timeBetween);
  }
    delay(2000);
    digitalWrite(6, LOW);
    delay(8250);
  for (int i=0; i<numLoop; i++){
    digitalWrite(5, HIGH); // dirty valve stop closing
    delay(timeBetween);
  }
}

void dirtyPump(){
  for (int i=0; i<numLoop; i++){
    digitalWrite(2, LOW); // dirty water pump
    delay(timeBetween);
    digitalWrite(6, LOW); // clean valve open
    delay(timeBetween);
    }
    delay(openTime);
  for (int i=0; i<numLoop; i++){
    digitalWrite(6, HIGH); // clean valve stop opening
    delay(timeBetween);
    }
    delay(pumpTime-(openTime*2));
  for (int i=0; i<numLoop; i++){
    digitalWrite(7, LOW); // clean valve close
    delay(timeBetween);
    }
    delay(closeTime);
  for (int i=0; i<numLoop; i++){
    digitalWrite(2, HIGH); // dirty water stop pumping
    delay(timeBetween);
    digitalWrite(7, HIGH); // clean valve stop closing
    delay(timeBetween);
    }
}

void reset(){
  for (int i=0; i<numLoop; i++){
    digitalWrite(4, LOW); // dirty valve open
    delay(timeBetween);
    digitalWrite(6, LOW); // clean valve open
    delay(timeBetween);
  }
  delay(openTime+2500);
  for (int i=0; i<numLoop; i++){
    digitalWrite(4, HIGH);
    delay(timeBetween);
    digitalWrite(6, HIGH);
    delay(timeBetween);
  }
  delay(50);
  for (int i=0; i<numLoop; i++){
    digitalWrite(5, LOW); // dirty valve close
    delay(timeBetween);
    digitalWrite(7, LOW); // clean valve close
    delay(timeBetween);
  }
  delay(closeTime+2500);
  for (int i=0; i<numLoop; i++){
    digitalWrite(5, HIGH);
    delay(timeBetween);
    digitalWrite(7, HIGH); 
    delay(timeBetween);
  }
}
