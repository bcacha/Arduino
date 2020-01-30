// Firmware program for GPJ workday table with LEDS

#include <Button.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>

int num_buttons = 14;                               // Number of push buttons
int leds_per = 42;                                  // LEDs per button
int led = 13;                                       // Onboard LED for testing

bool pressed = true;
bool released = true;
int button_released = 0;
int time_now = 0;
int timer = 0;
int button_flip[] = {0, 1, 2, 3, 4, 5, 6, 13, 12, 11, 10, 9, 8, 7};
uint8_t comm = 0x53;                                // Comm, data and checksum are the three
uint8_t data[] = {0x41, 0x42, 0x43, 0x44, 0x45,     // Pieces of data being sent
                  0x46, 0x47, 0x48, 0x49, 0x4A,     // uin8_t is used to keep data as one byte each
                  0x4B, 0x4C, 0x4D, 0x4E};
uint8_t checksum[sizeof(data)];


// Create an instance of PushButton reading digital pins 0 to 14 skipping 13 for the onboard LED
PushButton button = PushButton(0, ENABLE_INTERNAL_PULLUP);
PushButton button2 = PushButton(19, ENABLE_INTERNAL_PULLUP);
PushButton button3 = PushButton(2, ENABLE_INTERNAL_PULLUP);
PushButton button4 = PushButton(3, ENABLE_INTERNAL_PULLUP);
PushButton button5 = PushButton(4, ENABLE_INTERNAL_PULLUP);
PushButton button6 = PushButton(5, ENABLE_INTERNAL_PULLUP);
PushButton button7 = PushButton(6, ENABLE_INTERNAL_PULLUP);
PushButton button8 = PushButton(7, ENABLE_INTERNAL_PULLUP);
PushButton button9 = PushButton(8, ENABLE_INTERNAL_PULLUP);
PushButton button10 = PushButton(9, ENABLE_INTERNAL_PULLUP);
PushButton button11 = PushButton(10, ENABLE_INTERNAL_PULLUP);
PushButton button12 = PushButton(11, ENABLE_INTERNAL_PULLUP);
PushButton button13 = PushButton(12, ENABLE_INTERNAL_PULLUP);
PushButton button14 = PushButton(14, ENABLE_INTERNAL_PULLUP);

// Array of pointers to for each button
PushButton* buttons[] = {&button, &button2, &button3, &button4, &button5,
                         &button6, &button7, &button8, &button9, &button10,
                         &button11, &button12, &button13, &button14};

            
void setup(){
      Serial.begin(9600);                           // Open up the serial port so that we can write to it
      Serial1.begin(9600);
      pinMode(led, OUTPUT);                         // Initialize pin 13 for onboard led
      for (int i=0; i<sizeof(data); i++){           // For loop to create the checksum array
        checksum[i] = data[i] + 12;  
      }  

      // When the button is first pressed, call the function onButtonPressed (further down the page)
      for (int i=0; i<num_buttons; i++){
        buttons[i]->onPress(onButtonPressed);
      }
      // When the button is released, call onButtonReleased
      for (int i=0; i<num_buttons; i++){
        buttons[i]->onRelease(onButtonReleased);
      }
      Serial.println("Boot complete"); 

}



void loop(){
    // Check the state of each button
    for (int i=0; i<num_buttons; i++){
      buttons[i]->update();
    }    
    if (pressed == false){
      //Serial.println("button pressed");
      //Serial.println(button_released+1);    
      time_now = millis();
      pressed = true;
      timer = 30000;
    }
    if (timer > 0){
      timer = 30000 - (millis()-time_now);      

      if (timer <= 0){
        char off = 66;
        Serial1.write(off); 
        Serial1.write(";");
      }
    }

    delay(1);
}



// btn is a reference to the button that fired the event. That means you can use the same event handler for many buttons
void onButtonPressed(Button& btn){
    // Depending on which button is pressed, execute serialwriter for button
    if (released == true){
      for (int i=0; i<num_buttons; i++){
        if(btn.is(*buttons[i])){            
          pressed = false;
          released = false;
          button_released = i;
          serialwriter(button_flip[i]);
          i = num_buttons;
        }
      }
    }
}



void onButtonReleased(Button& btn, uint16_t duration){
    // Turn off LEDs when button is released
    digitalWrite(led, LOW); 
    if(btn.is(*buttons[button_released])){            
      released = true;
    }                         
}



void serialwriter(int i){
    uint8_t packet[] = {comm, data[i], checksum[i]};// Create the packet of 3 bytes to be sent
    Serial.write(packet, 3);                        // Writes the packet to serial
    Serial1.write((char)(button_released + 1)+66);
    Serial1.write(";");
    Serial.println();                               // Print a line in serial monitor      
    digitalWrite(led, HIGH);                        // Turns on onboard LED when button triggers
}
