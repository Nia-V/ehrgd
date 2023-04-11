#include "Avoider.h"
Avoider::Avoider(int trigger, int echo, int MaxDistance){
  this->trigger = trigger;
  this->echo = echo;
    this->  MaxDistance = MaxDistance;
  }
void Avoider::stopCMaway(int stopDist){




void Avoider(){// Declare the fuction avoider as...

 
#define TRIGGER_PIN  13// defining the trigger pin as pin 13
#define ECHO_PIN     12// defining the echo pin as pin 12
#define MAX_DISTANCE 400// defining max distance as 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);//call the sonar function with parameters trigger pin, echo pin and max distance
 
float duration, distance; //declare the float variables duration and distance
 
int iterations = 5;// declare the int variable iterations and give it the value 5
  duration = sonar.ping_median(iterations); // duration is equalk to the return value of the function sonar.ping_median with parameter interartion
  distance = (duration / 2) * 0.0343;// distance  is equal to duration / 2 * the speed of sound cm/ second
 
  if (distance <= 20){// if distance is less than 20 cm then...
    stopper = 1; //stopper is equal to 1
  
  }
 if (stopper == 1){// if stopper is equal to 1 then...
      STOP();// stop moving
    for (pos = 0; pos <= 180; pos += 1) {//turn servo from o to 180
      myservo.write(pos);  //initiate turning
    delay(15);  // delay 15 milliseconds
    if (distance >= 30){// if the distance read by the sonar is greater than 30, then...
      steve = pos;}  // save the angle of the servo to the variable steve        
  }
  for (pos = 180; pos >= 0; pos -= 1) { //turn servo from o to 180
  myservo.write(pos);  //initiate turning
    delay(15);  // delay 15 milliseconds
    if (distance >= 30){// if the distance read by the sonar is greater than 30, then...
      steve = pos;// save the angle of the servo to the variable steve        
    }}
   
    
if (steve > 95 ){// if the valuye of steve is greaterthan or equal to 95 then ...
 time = map(steve, 95, 180, 500, 2000);//map steve to time so that 90 is equal to 1000 and 180 is equal to 3500
 Left(150);// go left at a speed 200
 delay(time);// delay for the value of time
 steve = 90;// reset steve to 90
stopper = 0;// reset stopper to 90
 }    
  if (steve< 85){// if the valuye of steve is Less than or equal to 85 then ...
 time = map(steve, 0, 85, 500, 2000);//map steve to time so that 0 is equal to 1000 and 85 is equal to 3500
 Right(150);// go right at a speed 200
 delay(time);// delay for the value of time
 steve = 90;// reset steve to 90
stopper = 0;// reset stopper to 90
 } }  
 
  if (stopper == 0){// if stopper is equal to 0 then...
  Forward(75); //moove forward at a speed of 150
  myservo.write(90); // turn servo to face forward
}
 }
  
