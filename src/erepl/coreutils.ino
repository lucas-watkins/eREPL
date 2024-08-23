#include "erepl.h"

uint8_t echo(String args) {
  Serial.println(args); 
  return 0; 
}