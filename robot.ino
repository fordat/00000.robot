/*
 * INITIALIZE YOUR SENSORS!
 */

#define MOTOR_A_1A 9 // right
#define MOTOR_A_1B 10 // right
#define MOTOR_B_1A 5 //left
#define MOTOR_B_1B 6// left
#include <NewPing.h>


int pr0 = 0; //pr0 is photoresistor0 input A0
int pr1 = 1; //pr1 is photoresistor1 input A1
int pr2 = 2; //pr2 is photoresistor2 input A2


int pr0reading = 0; //is the data value reading of pr0 
int pr1reading = 0; //is the data value reading of pr1 
int pr2reading = 0; //is the data value reading of pr2 

int pr0threshold = 1; // photoresistor0's threshold
int pr1threshold = 1; // photoresistor1's threshold
int pr2threshold = 1; // photoresistor2's threshold



int left_sen = A0;   //A = left
int center_sen = A1; //B = center
int right_sen = A2;  //C =right
int ValSens_A = 0; 
int ValSens_B = 0;
int ValSens_C = 0;


boolean frontwall ;
boolean leftwall;
boolean rightwall ; 

//FRONT SENSOR
#define TRIGGER_FRONT 3
#define ECHO_FRONT 4

//LEFT SENSOR
#define TRIGGER_LEFT 12
#define ECHO_LEFT 13
#define MAX_DISTANCE 200

NewPing leftsonar(TRIGGER_LEFT, ECHO_LEFT, MAX_DISTANCE);
NewPing frontsonar(TRIGGER_FRONT, ECHO_FRONT, MAX_DISTANCE);

#define LEFTTHRESHOLD 20
#define FRONTTHRESHOLD 20
#define THRESH 10

#define centerThres 20
#define leftThres 300
#define rightThres 300

  


void setup() {

Serial.begin(9600);
pinMode(MOTOR_A_1A,  OUTPUT); // right
pinMode(MOTOR_A_1B,  OUTPUT); // right
pinMode(MOTOR_B_1A,  OUTPUT); // left
pinMode(MOTOR_B_1B,  OUTPUT); // left

pinMode(left_sen, INPUT);   //A = left
pinMode(center_sen, INPUT);   //A = left
pinMode(right_sen, INPUT);   //A = left
pinMode(ValSens_A, INPUT);   //A = left
pinMode(ValSens_B, INPUT);   //A = left
pinMode(ValSens_C, INPUT);   //A = left

pinMode(TRIGGER_LEFT, OUTPUT);
pinMode(TRIGGER_FRONT, OUTPUT);
pinMode(ECHO_LEFT, INPUT);
pinMode(ECHO_FRONT, INPUT);
}

void loop(){
 
 
   //CALL YOUR FUNCTIONS
   //EXAMPLE BELOW
   
   // call the forward function for 1 second
   // the delay is 1000 ms
   pr0reading = analogRead(pr0);
   pr1reading = analogRead(pr1);
   pr2reading = analogRead(pr2);

   Serial.print(" L: ");
   Serial.print(analogRead(pr0));
   Serial.print(" C: ");
   Serial.print(analogRead(pr1));
   Serial.print(" R: ");
   Serial.print(analogRead(pr2));
   Serial.print(" left reading: ");
   Serial.print(leftsonar.ping_cm());
   Serial.print(" front reading: ");
   Serial.println(frontsonar.ping_cm());
   

 

  // dotted lines
   // RIGHT PR
   if (pr2reading > 0 && pr0reading == 0  && pr1reading > 0) {
    delay(100);
    left(100);
    delay(100);
//    forward();
   }

   // CENTER PR
   else if(pr1reading > 0 && pr0reading == 0 && pr2reading == 0) {
    delay(100);
    backward();
    delay(100);
    Stop();
   }

   // LEFT PR
   else if (pr0reading > 0 && pr1reading > 0 && pr2reading == 0) {
    delay(100);
    right(100);
    delay(100);
 //   forward();
   }
   
//   else {
//    forward();
//    delay(100);
//    Stop();
//   }
    else if (pr0reading > 3 && pr1reading > 3 && pr2reading > 3) {
      Stop();
      // SONARS
    // one sonars uncovered
   if (frontsonar.ping_cm() < THRESH) {
     left(200);
     delay(100);
     Stop();
   }
   if (frontsonar.ping_cm() < THRESH && leftsonar.ping_cm() < THRESH) {
    right(200);
    delay(100);
    Stop();
   }
    }
    else {
      forward();
      delay(100);
      Stop();
    }


   delay(300);

//   Serial.print("left reading: ");
//   Serial.println(leftsonar.ping_cm());
//   Serial.print("front reading: ");
//   Serial.println(frontsonar.ping_cm());
//   if (leftsonar.ping_cm() > THRESH && frontsonar.ping_cm() < THRESH) {
//      left();
//      delay(200);
//      stop();
//   }
//   else if (frontsonar.ping_cm() > THRESH && leftsonar.ping_cm() < THRESH) {
//      forward();
//      delay(200);
//      stop();
//   }
//   else if (frontsonar.ping_cm() < THRESH && leftsonar.ping_cm() < THRESH) {
//      right();
//      
//      delay(200);
//      stop();
//   }
////   else if (frontsonar.ping_cm() < THRESH) {
////      stop();
////      delay(200);
////      backward();
////      delay(200);
////      stop();
////   }
//   delay(500);

 
}

 //WRITE FUNCTIONS HERE
 //EXAMPLE BELOW
        void forward() {
          //LEFT MOTOR
         Serial.print ("forward");
         analogWrite(MOTOR_B_1A, 200);
         analogWrite(MOTOR_B_1B, LOW);
          //RIGHT MOTOR

          
         analogWrite(MOTOR_A_1A, 200);
         analogWrite(MOTOR_A_1B, LOW);
        }

          void right(int power) {
          //LEFT MOTOR
          analogWrite(MOTOR_B_1A, LOW);
          analogWrite(MOTOR_B_1B, power);
          //RIGHT MOTOR
          analogWrite(MOTOR_A_1A, power);
          analogWrite(MOTOR_A_1B, LOW);
          }


         void left(int power) {
          //LEFT MOTOR
          analogWrite(MOTOR_B_1A, power);
          analogWrite(MOTOR_B_1B, LOW);
          //RIGHT MOTOR
          analogWrite(MOTOR_A_1A, LOW);
          analogWrite(MOTOR_A_1B, power);
          }

           void backward() {
          //LEFT MOTOR
          analogWrite(MOTOR_B_1A, LOW);
          analogWrite(MOTOR_B_1B, 200);
          //RIGHT MOTOR
          analogWrite(MOTOR_A_1A, LOW);
          analogWrite(MOTOR_A_1B, 200);
           }
           void Stop() {
          //LEFT MOTOR
          analogWrite(MOTOR_B_1A, LOW);
          analogWrite(MOTOR_B_1B, LOW);
          //RIGHT MOTOR
          analogWrite(MOTOR_A_1A, LOW);
          analogWrite(MOTOR_A_1B, LOW);


           }