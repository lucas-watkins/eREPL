#include "config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

static String httpGet(const String url, const bool interactive = false){
  if (WiFi.status() == WL_CONNECTED && url.startsWith("http://")){
    WiFiClient client;
    HTTPClient http; 

    http.begin(client, url); 
    const int httpCode {http.GET()}; 

    if (interactive){
      const String httpErrorString {http.errorToString(httpCode)}; 
      Serial.println("HTTP Code: " + static_cast<String>(httpCode) + (httpErrorString == "" ? "" : " (" + httpErrorString + ")"));
      if (httpErrorString == ""){
        Serial.println(""); 
      }
    }

    return http.getString(); 

  } else if (!url.startsWith("http://")){
    Serial.println("Error: URL must start with \"http://\"");
    return ""; 
  } 
  else {
    Serial.println("Error: unable to reach " + url); 
    return "";
  }
}

void runCommand(const String full){
  const String command {full.substring(0, full.indexOf(' '))};
  const String args {full.substring(full.indexOf(' ') + 1, full.length())}; 
  
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
  else if (command == "get"){
    Serial.println(httpGet(args, true)); 
  }
  else if (command != ""){
    Serial.println("Command Not Found!");
  }
}

// echos string back
static void echo(String args) {
  Serial.println(args);  
}

// connect to wifi
static void connect(const String args){

  #ifdef DEBUG
  Serial.print("Network Name: ");
  Serial.println(args.substring(0, args.indexOf(' '))); 
  Serial.print("Password: ");
  Serial.println(args.substring(args.indexOf(' '), args.length())); 
  #endif /* DEBUG */

  WiFi.begin(args.substring(0, args.indexOf(' ')), args.substring(args.indexOf(' ') + 1, args.length())); 
  
  Serial.print("Connecting ");

  // 30 seconds to connect
  unsigned long targetTime {millis() + 30000L}; 
  while (WiFi.status() != WL_CONNECTED && millis() < targetTime){
    Serial.print('.');
    delay(500); 
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.print(" Connected! ");
    Serial.println(" (" + WiFi.localIP().toString() + ')'); 
  }

}

static void ip(){
  Serial.println(WiFi.localIP()); 
}

static void reboot(){
  Serial.end();
  // enable and disable watchdog on chip and stall to reboot  
  wdt_disable();
  wdt_enable(WDTO_15MS); 
  while (true){}
}

static void clear(){
  Serial.print("\x1b[2J\x1b[H");
}

