#include "erepl.h"

void setup() {
  Serial.begin(constants::baudRate); 
  while (!Serial) {}
  Serial.flush(); 
}


void loop() {
  Serial.print(constants::shellPrompt);
  while (true)
  {
    String input; 
    if (Serial.available() > 0){ 
      char character {Serial.read()};
      if (character == '\n' || character == '\r'){
        Serial.println(""); 
        Serial.println("Run Command!");
        break; 
      }
      else {
        Serial.print(character);
      }
    }
    delay(10); 
  }
}