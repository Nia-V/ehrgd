/*
The final robot car code that allows you to use an IR remote to either control the robot maually, follow a line, or avoid obstacles

*/
#include <NewPing.h>//Include Ultrasonic library
#include <IRremote.h> //Include IR Library
#include <Servo.h>//Include servo library
// -----------------VARIABLES AND DECLARATIONS FOR ALL FUNCTIONS
const int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
int toggle;
// ------------------VARIABLES AND DECLARATIONS FOR MANUAL
bool r=0;// Declaring Bool variable named r set to 0
bool l= 0;// Declaring Bool variable named l set to 0
bool u= 0;// Declaring Bool variable named u set to 0
bool d=0;// Declaring Bool variable named d set to 0
// ------------------VARIABLES AND DECLARATIONS FOR AVOIDER
int pos; //Declaring int variable named pos
int time = 0;//declaring int variable named time 
int steve = 90;//declaring int variable named steve equal to 90
bool stopper = 0;//Declaring boolvariable named stopper
Servo myservo; //Creating instance of servo class called myservo
// ---------------------- BASE MVMNT FUNCTION
 void Base(int x, int y , int z, int a){//Defining a function named base with int inputs x, y, z, a.
  analogWrite (5, x);// analog write pin 5 the value of parameter x (LEFT SPEED)
  analogWrite (6, y);// analog write pin 6 the value of parameter y (RIGHT SPEED)
  digitalWrite (7, z);// digital write to pin 7 the value of parameter z(LEFT FORWARD/REVERSE)
  digitalWrite (8, a);// digital write to pin 8 the value of parameter a(RIGHT FORWARD/REVERSE)
  digitalWrite (3, 1);// digital write to pin 3 5V (STANDBY PIN)
  }

// --------------------ALL MVMNT FUNCTION DECLARATIONS
  void STOP(){ // Function to stop mouvment of car
  analogWrite (5, 0);// LEFT SPEED 0
  analogWrite (6, 0); // RIGHT SPEED 0
  digitalWrite (7, 0); // LEFT MOTORS REVERSE
  digitalWrite (8, 0); // RIGHT MOTOR REVERSE
  digitalWrite (3, 0); // ACTIVATE STANDBY
  }

 void Forward(int x){//Declaring the forward function with the int parameter x
  
 Base(x, x, 1, 1);// that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 1 to z ands a 
 }
  
  
  void Backward(int x){//Declaring the backward function with the int parameter x

 Base(x, x, 0, 0);// that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 0 to z ands a 
}

 void Right_F(int  x){//Declaring the Right_F function with the int parameter x
 Base(x/2, x, 1, 1);// that calls the function base and passes the value of parameter x/2 and x to the parameters x and y of base and the value 1 to z ands a 
 }
void Right_B(int  x){//Declaring the Right_B function with the int parameter x
 Base(x/2, x, 0, 0);// that calls the function base and passes the value of parameter x/2 and x to the parameters x and y of base and the value 0 to z ands a 
 }

void Right(int  x){//Declaring the Right function with the int parameter x
  Base(x, x, 0, 1);// that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 0 and 1 to z ands a 
}

void Left(int  x){//Declaring the Left function with the int parameter x
  Base(x, x, 1, 0);// that calls the function base and passes the value of parameter x to the parameters x and y of base and the value 1 and 0 to z ands a 
}
 void Left_F(int  x){//Declaring the Right_B function with the int parameter x
 Base(x, x/2, 1, 1);// that calls the function base and passes the value of parameter x and x/2 to the parameters x and y of base and the value 0 to z ands a
 }
 void Left_B(int  x){//Declaring the Right_B function with the int parameter x
 Base(x, x/2, 0, 0);// that calls the function base and passes the value of parameter x and x/2 to the parameters x and y of base and the value 0 to z ands a
 }
//-----------------------------------MANUAL

//Lets an ir remote control the mouvments of the robot

void Man(){
   if (irrecv.decode(&results)){// If the IR module recieves a signal
 
        if (results.value == 0XFFFFFFFF)//And if the input button of the remote is repeated giving the signal results FFFFFFFF
          results.value = key_value;//then the key pressed is equal to the last key pressed

        switch(results.value){// if results.value is equal to....
          case 0xFF629D: //the VOL + button then... 
          Serial.println("VOL+");// Serial print Vol +
          u= 1;// bool u is equal to 1
          d=0;// bool d is equal to 0
          l=0;// bool l is equal to 0
          r=0;// bool r is equal to 0
          break;

case 0xFF22DD://the |<< button then...
          Serial.println("|<<");// Serial print |<<
          u= 0;// bool u is equal to 0
          d=0;// bool d is equal to 0
          l=1;// bool l is equal to l
          r=0;// bool r is equal to 0
          break;

 case 0xFFC23D://the >>| button then...
          Serial.println(">>|");// Serial print >>|
         u= 0;// bool u is equal to 0
          d=0;// bool d is equal to 0
          l=0;// bool l is equal to 0
          r=1;// bool r is equal to 1
          break ;          

 case 0xFFA857://the VOL + button then...
          Serial.println("VOL-");// Serial print Vol -
          u= 0;// bool u is equal to 0
          d=1;// bool d is equal to 1
          l=0;// bool l is equal to 0
          r=0;// bool r is equal to 0
          break ;  
}

   
   
   if(r == 1){//if r is equal to 1
     Right(100);//Move right at speed 100
   }
   if(u == 1){//if u is equal to 1
     Forward(100);//Move forward at speed 100
   }
   if(l == 1){//if l is equal to 1
     Left(100);//Move left at speed 100
   }
   if(d == 1){//if d is equal to 1
     Backward(100);//Move backward at speed 100
   }
   }
   }

  // --------------------------------LINE FOLLOWER

// Makes the robot follow the path of a black line

 void linefollower(){ //Declare the line follower function as
int right;// declare the int right
int left;// declare the int left
int middle;// declare the int middle
middle = analogRead(A1);//middle is equal to the bit voltage at A1
right =analogRead(A0);//right is equal to the bit voltage at A0
left = analogRead(A2);//left is equal to the bit voltage at A2

if(middle - right >= 0  && middle - left >= 0){// If middle is greater than left and right then... 
  Forward(60);// Move forward with a speend of 100
}
if(right - middle >= 0 && right- left>= 0){// If right is greater than middle and left then...
Right(50);// move right with a speed of 75
}
if(left- middle>= 0 && left - right>=0 ){// If left is greater than middle and right then...
  Left(50);// move left with a speed of 75
}
}
 // -------------------------------------OBSTACLE AVOIDER 

 // Makes the robot move until it sees an obstacle at which point it will scan to find a clear path

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
  

void setup(){
  Serial.begin(9600);// begin serial comunication
  irrecv.enableIRIn();// begin IR reciever 
  irrecv.blink13(true);// Blink the led built in if recieving a signal fromn the IR module
  myservo.attach(10);  // declare the servo pin as pin 10

}

void loop(){
  if (irrecv.decode(&results)){// If the IR module recieves a signal
 
        if (results.value == 0XFFFFFFFF)//And if the input button of the remote is repeated giving the signal results FFFFFFFF
          results.value = key_value;//then the key pressed is equal to the last key pressed

        switch(results.value){// if results.value is equal to....
           case 0xFFA25D:// the On/off button then...
          Serial.println("ON/OFF"); // serial print on/ off
          toggle = 0;// set toggle equal go 0
          break;
          case 0xFF30CF:// the 1 button
          Serial.println("1");// serial print 1
          STOP();// stop moving
          delay(1000);// delay 1 second
         toggle = 1;// set toggle equal to 1
          break ;
          case 0xFF18E7:// the 2 button
          Serial.println("2");// serial print 2
          STOP();// stop moving
          delay(1000);// delay 1 second
         toggle = 2;// set toggle equal to 1
          break ;
          case 0xFF7A85:// the 3 button
          Serial.println("3");// serial print 3
          STOP();// stop moving
          delay(1000);// delay 1 second
          toggle = 3;// set toggle equal to 3
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
if(toggle == 3){// if toggle is equal to 3
  Man();// call the manual fuinction
}
if(toggle == 2){// if toggle is equal to 2
  Avoider();// call the obstacle avoider fuinction
}
if(toggle == 1){// if toggle is equal to 1
  linefollower();// call the Line follower fuinction
}
if(toggle == 0){// if toggle is equal to 0
  STOP();// call the stop fuinction
}
}
