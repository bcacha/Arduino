#define steps 15
#define integration 5
#define mosfet 4
float movingAvg[steps];
float integrate[integration];
float total, itotal;
int n = 0;
int m = 0;
//int voltage = 0;
int limit = 16;
float calibrate = 0;
bool resetState = false;
bool stateSwitch = false;


void setup() {
  Serial.begin(9600);
  pinMode(mosfet, OUTPUT);
  digitalWrite(mosfet, LOW);
  calibration();
//  Serial.println("Ready");
}


void loop() {
  int stateValue = analogRead(A0);
  
  if (resetState == true){
    digitalWrite(mosfet, LOW);
//    Serial.println("turn off led");
    if (stateSwitch == false && stateValue < 512){
       stateSwitch = true;
//       Serial.println("turn switch back on");
    }
    if (stateSwitch == true && stateValue > 512){
//      Serial.println("reset state = false");
      resetState = false;
      stateSwitch = false;
      for (int i=0; i<steps; i++){
        movingAvg[i] = 0;
      }
      for (int i=0; i<integration; i++){
        integrate[i] = 0;
      }
    }
  }
  
  if (resetState == false && stateValue > 512){
//    Serial.println("in main loop");
    digitalWrite(mosfet, HIGH);
    measureCurrent(stateValue);
    n++;    m++;
    if (n == steps){n = 0;}
    if (m == integration){m = 0;}
  }
  if (itotal > limit || stateValue < 512){
    resetState = true;
//    Serial.println("reset state = true");
  }
  delay(1);
}


//---------------------------------------------------------------------------------------------------//


void measureCurrent(int stateValue){
  int sensorValue = analogRead(A4);
  float value = (float(sensorValue)-float(calibrate))*(5000.0/(20.0*1023.0));
  movingAvg[n] = value;
  total = 0.0;
  itotal = 0.0;
  for (int i=0; i<steps; i++){
    total += movingAvg[i];
  }
  float average = total/float(steps);
  integrate[m] = average;
  for (int i=0; i<integration; i++){
    itotal += integrate[i];
  }
  Serial.print(itotal);
  Serial.print(",");
  Serial.println(average);
}

void calibration(){
  int voltage;
  for (int i=0; i<50; i++){
    voltage += analogRead(A4);
    delay(100);
  }
  calibrate = float(voltage)/50.0;
}
