#include "erepl.h"

void setup() {
  Serial.begin(constants::baudRate); 
  
  while (!Serial) {
    delay(10); 
  }
  Serial.flush(); 
}


void loop() {
  Serial.print(constants::shellPrompt);
  String input;
  
  while (true)
  { 

    if (Serial.available() > 0){ 
      char character {Serial.read()};
      if (character == '\n' || character == '\r'){
        Serial.println(""); 
        runCommand(input);
        break; 
      }
      else {
        Serial.print(character);
        input += character;
      }
    }
    delay(10); 
  }
}