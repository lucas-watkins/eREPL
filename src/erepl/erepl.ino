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
      // backspace
      else if (character == 127){
        if (input.length() > 0 ){
          input = input.substring(0, input.length() - 1); 
          
          // move back to column 0
          Serial.print("\033[50D");

          for (unsigned int i {0}; i < input.length() + constants::shellPrompt.length() + 1u; i++){
            Serial.print(" ");
          }

          Serial.print("\033[50D");
          Serial.print(constants::shellPrompt + input);
        }
      }
      else {
        Serial.print(character);
        input += character;
      }
    }
    delay(10); 
  }
}