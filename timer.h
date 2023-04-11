#ifndef timer_h
#define timer_h
#include <Arduino.h>
int lasttime =0;

int timer(){
  return millis()-lasttime;
}
void reset(){
lasttime = millis();
}
#endif