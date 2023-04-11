#include "Display4.h"
#include "timer.h"
const byte table[10]=
{
    B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11100110,  // 9
};

SevSeg::SevSeg(int D1, int D2, int D3, int D4, int latch, int clock, int data){
this->D1= D1;
this->D2= D2;
this->D3= D3;
this->D4= D4;
this->latch = latch;
this->clock = clock;
this->data = data;
}
void SevSeg::init(){
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
}

void SevSeg::display(int x, int y, int z, int a){
int wait = 7;
if(timer()> wait && timer() < (2*wait)){
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
    digitalWrite(D1, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[x]);
           digitalWrite(latch, 1);
        
}

if(timer()>2*wait && timer()<3*wait){
digitalWrite(D1, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
    digitalWrite(D2, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[y]);
           digitalWrite(latch, 1);
        
}

if(timer()>3*wait && timer()<4*wait){

digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D4, 1);
    digitalWrite(D3, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[z]);
           digitalWrite(latch, 1);
         
}

if(timer()>4*wait && timer()<5*wait){

digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 0);
      digitalWrite(latch, 0);
    shiftOut(data, clock, LSBFIRST, table[a]);
           digitalWrite(latch, 1);
        
reset();
}



}
