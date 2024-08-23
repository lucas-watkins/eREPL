#include "erepl.h"
#define DEBUG

void runCommand(String full){
  String command {full.substring(0, full.indexOf(' '))};
  String args {full.substring(full.indexOf(' ') + 1, full.length())}; 
  
  #ifdef DEBUG
  Serial.print("Command: ");
  Serial.println(command);
  Serial.print("Args: ");
  Serial.println(args); 
  #endif 
  
  if (command == "echo"){
    echo(args);
  }
}

void echo(String args) {
  Serial.println(args);  
}