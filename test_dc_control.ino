
// This alternate version of the code does not require
// atomic.h. Instead, interrupts() and noInterrupts() 
// are used. Please use this code if your 
// platform does not support ATOMIC_BLOCK.
 #include "ESP32Encoder.h"
ESP32Encoder encoder;
//LEFT MOTOR ENCODER PARAMETERS
#define EncA1  15 //19
#define EncB1  13  //18 //green

//RIGHT MOTOR ENCODER PARAMETERS
#define EncA2 35
#define EncB2 34


#define IN2 19
#define IN1 18
const int encoder_CPR = 0;

float count_to_angle(int32_t cnt)
{
  float angle = (float)cnt * 360.0f / (float)encoder_CPR;
  return angle;
}

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  encoder.attachHalfQuad(15,13);//pin
  pinMode(EncA1, INPUT_PULLUP);
  pinMode(EncB1, INPUT_PULLUP);
  encoder.setCount(0);
  
 
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  
}

void loop() {

  // set target position
  //int target = 1200;
  int target = 250*sin(prevT/1e6);

  // PID constants
  float kp = 1;
  float kd = 0;
  float ki = 1;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position
  int pos = 0; 
  noInterrupts(); // disable interrupts temporarily while reading
  pos = posi;
  interrupts(); // turn interrupts back on
  
  // error
  int e = pos - target;

  // derivative
  float dedt = (e-eprev)/(deltaT);

  // integral
  eintegral = eintegral + e*deltaT;

  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;

  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }

  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }

  // signal the motor
  setMotor(dir,pwr,IN1,IN2);


  // store previous error
  eprev = e;

  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
}

void setMotor(int dir, int pwmVal, int in1, int in2){
  
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

void readEncoder(){
  int b = digitalRead(EncB1);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
