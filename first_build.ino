#include <Arduino.h>
#include <Bounce2.h>
#include <MIDI.h>


int btns[4] = {17, 16, 15, 14};
int leds[4] = {13, 10, 7, 4};

// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();
#define BOUNCE_WITH_PROMPT_DETECTION


Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();

int button1_state = 0;
int button2_state = 0;
int button3_state = 0;
int button4_state = 0;



void setup() {

  pinMode(1, OUTPUT); // MIDI

  pinMode(2, OUTPUT); // 1
  pinMode(3, OUTPUT); // 1
  pinMode(4, OUTPUT); // 1

  pinMode(5, OUTPUT); // 2
  pinMode(6, OUTPUT); // 2
  pinMode(7, OUTPUT); // 2

  pinMode(8, OUTPUT); // 3
  pinMode(9, OUTPUT); // 3
  pinMode(10, OUTPUT); // 3

  pinMode(11, OUTPUT); // 4
  pinMode(12, OUTPUT); // 4 
  pinMode(13, OUTPUT); // 4

  // pinMode(14, INPUT_PULLUP);
  // pinMode(15, INPUT_PULLUP);
  // pinMode(16, INPUT_PULLUP);
  // pinMode(17, INPUT_PULLUP);

  button1.attach(14, INPUT_PULLUP);
  button2.attach(15, INPUT_PULLUP);
  button3.attach(16, INPUT_PULLUP);
  button4.attach(17, INPUT_PULLUP);

  // DEBOUNCE INTERVAL IN MILLISECONDS
  button1.interval(10);
  button2.interval(10);
  button3.interval(10); 
  button4.interval(10);

  // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  button1.setPressedState(LOW);
  button2.setPressedState(LOW);
  button3.setPressedState(LOW);
  button4.setPressedState(LOW);

  Serial.begin(4800);
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
}






// void buttonSelect(){
  
// 	int currentButtonState = HIGH;
// 	int lastButtonState = HIGH;
  
//   for(int i=0; i < 4; i++){
// 	  currentButtonState = digitalRead(btns[i]);
//     if (currentButtonState == LOW && lastButtonState == HIGH) {
      
//       ledOn(leds[i]);

//       MIDI.sendControlChange(0, 127, 1);
//       //MIDI.sendControlChange(0, 127, 1);
//       //MIDI.sendProgramChange(2, 1);

//       Serial.print("Button Pressed: --> ");
//       Serial.println(btns[i]);
//       delay(100);
//     }
//     lastButtonState = currentButtonState;
//   }
// }

void printButtonState(int num){
  int state = digitalRead(num);
  
  Serial.print("Button State for pin: ");
  Serial.print(num);
  Serial.print(" --> ");
  Serial.println(state);
  delay(500);
}

void clearButtonStates(){
  button1_state = 0;
  button2_state = 0;
  button3_state = 0;
  button4_state = 0;
};

void ledOn(int pin){
  ledAllOff();

  ledColor(pin, 0, 100, 50);
}

void ledAllOff(){
  for (int i = 0; i < 4; i++){
    ledColor(leds[i], 0, 0, 0);
  }
}

void ledColor(int pinStart, int red_light_value, int green_light_value, int blue_light_value)
 {
  int rChannel = pinStart;
  int gChannel = pinStart - 2;
  int bChannel = pinStart - 1;
  
  digitalWrite(rChannel, red_light_value);
  digitalWrite(gChannel, green_light_value);
  digitalWrite(bChannel, blue_light_value);
}

void loop() {
  
  MIDI.read();

  // UPDATE THE BUTTON BY CALLING .update() AT THE BEGINNING OF THE LOOP:
  button1.update();
  button2.update();
  button3.update();
  button4.update();





  // IF THE BUTTON WAS PRESSED THIS LOOP:
  if ( button1.fell() ) {
      if (button1_state == 0){
        clearButtonStates();

        MIDI.sendControlChange(0, 0, 1);
        MIDI.sendControlChange(27, 127, 1);

        MIDI.sendProgramChange(0, 1);
        MIDI.sendProgramChange(0, 2);
        
        ledAllOff();
        ledColor(4, 0, 1, 1);

        button1_state = 1;
        delay(100);

      } else {
        MIDI.sendControlChange(27, 0, 1);

        ledAllOff();
        ledColor(4, 1, 0, 0);
        button1_state = 0;
        delay(100);
      }

      delay(100);

  } else if ( button2.fell() ){
     
      if (button2_state == 0){
        clearButtonStates();

        MIDI.sendControlChange(0, 0, 1);
        MIDI.sendControlChange(27, 127, 1);

        MIDI.sendProgramChange(1, 1);
        MIDI.sendProgramChange(1, 2);
        
        ledAllOff();
        ledColor(7, 0, 1, 1);

        button2_state = 1;
        delay(100);

      } else {
        MIDI.sendControlChange(27, 0, 1);

        ledAllOff();
        ledColor(7, 1, 0, 0);
        button2_state = 0;
        delay(100);
      }

  } else if ( button3.fell() ){
      
      if (button3_state == 0){
        clearButtonStates();

        MIDI.sendControlChange(0, 0, 1);
        MIDI.sendControlChange(27, 127, 1);

        MIDI.sendProgramChange(3, 1);
        MIDI.sendProgramChange(2, 2);
        
        ledAllOff();
        ledColor(10, 0, 1, 1);

        button3_state = 1;
        delay(100);

      } else {
        MIDI.sendControlChange(27, 0, 1);

        ledAllOff();
        ledColor(10, 1, 0, 0);
        button3_state = 0;
        delay(100);
      }

  } else if ( button4.fell() ){
      
      if (button4_state == 0){
        clearButtonStates();

        MIDI.sendControlChange(0, 0, 1);
        MIDI.sendControlChange(27, 127, 1);

        MIDI.sendProgramChange(4, 1);
        MIDI.sendProgramChange(3, 2);
        
        ledAllOff();
        ledColor(13, 0, 1, 1);

        button4_state = 1;
        delay(100);

      } else {
        MIDI.sendControlChange(27, 0, 1);

        ledAllOff();
        ledColor(13, 1, 0, 0);
        button4_state = 0;
        delay(100);
      }
  }
}
