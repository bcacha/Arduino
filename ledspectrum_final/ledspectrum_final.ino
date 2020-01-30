#define LOG_OUT 1 // use the log output function
#define FFT_N 256 // set to 256 point fft
#include <FFT.h> // include the library
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    112
#define BRIGHTNESS  64

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter - delay() and millis() killed
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  analogReference(EXTERNAL);  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  int change = 0;
  while(1) { // reduces jitter
  thefft();
  int divisor = 6;
  int rows = 8;
  int columns = 14;
  int arra[columns] ; 
  
  for (int n = 2; n < 16 ; n += 1) {
    if ( fft_log_out[n*divisor] < 60){
      arra[n-2] = 1;
      }
    else{
      if ((fft_log_out[n*divisor]-60)/7 >= 8){
        arra[n-2] = 8;
        }
      else{
        arra[n-2] = (fft_log_out[n*divisor]-60)/8;
        }
      }
    }
     for (int j=0 ; j<columns ; j+=1){
      int a = 27-2*j;
      int b = 1+2*j;
      for (int i=0 ; i<rows-arra[j] ; i+=1){
        leds[a*(i-(i/2))+b*(i/2)+j] = CRGB(0,0,0);
        }
      for (int k=rows-arra[j] ; k<rows ; k+=1){
        uint8_t bright = 255;
        leds[a*(k-(k/2))+b*(k/2)+j] = ColorFromPalette( RainbowColors_p, (change+18*j)%255, bright, LINEARBLEND);
        }
      }
  TIMSK0 = 1;
  FastLED.show();
  TIMSK0 = 0;
  change += 1;

   for (int i=0; i<8; i+=1){
   Serial.println(arra[i]);
   }
  delay(5000);
  }
}



void thefft(){
      cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fft_input[i] = k; // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0
    }
    // window data, then reorder, then run, then take output
    fft_window(); // window the data for better frequency response
    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_log(); // take the output of the fft
    sei(); // turn interrupts back on

}



void turnoff() {
  for (int i=0; i<=NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
  delay(1);
}
