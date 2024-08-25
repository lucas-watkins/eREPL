#include "erepl.h"
#include <ESP8266WiFi.h>

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
  else if (command == "connect"){
    connect(args); 
  }
  else if (command == "ip"){
    ip(); 
  }
  else if (command == "reboot"){
    reboot(); 
  }
  else if (command == "clear"){
    clear();
  }
  else if (command != ""){
    Serial.println("Command Not Found!");
  }
}

// echos string back
void echo(String args) {
  Serial.println(args);  
}

// connect to wifi
void connect(String args){

  #ifdef DEBUG
  Serial.print("Network Name: ");
  Serial.println(args.substring(0, args.indexOf(' '))); 
  Serial.print("Password: ");
  Serial.println(args.substring(args.indexOf(' '), args.length())); 
  #endif /* DEBUG */

  WiFi.begin(args.substring(0, args.indexOf(' ')), args.substring(args.indexOf(' ') + 1, args.length())); 
  
  Serial.println("Connecting");

  // 30 seconds to connect
  unsigned long targetTime {millis() + 30000L}; 
  while (WiFi.status() != WL_CONNECTED && millis() < targetTime){
    Serial.print('.');
    delay(500); 
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!"); 
  }

  ip(); 
}

void ip(){
  Serial.println(WiFi.localIP()); 
}

void reboot(){
  Serial.end();
  // enable and disable watchdog on chip and stall to reboot  
  wdt_disable();
  wdt_enable(WDTO_15MS); 
  while (true){}
}

void clear(){
  Serial.print("\x1b[2J\x1b[H");
}