
#include "CytronMotorDriver.h"

//LEFT MOTOR ENCODER PARAMETERS
#define EncA1 19
#define EncB1 18

//RIGHT MOTOR ENCODER PARAMETERS
#define EncA2 35
#define EncB2 34



// Configure the motor driver.
CytronMD motor1(PWM_PWM, 15, 2);   // PWM 1A = Pin 34, PWM 1B = Pin 35.   LEFT MOTOR
CytronMD motor2(PWM_PWM, 27, 26); // PWM 2A = Pin 10, PWM 2B = Pin 11.   RIGHT MOTOR
//int pos=0;

// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(115200);
  //Setting encoders pins to input (receiving data)
  pinMode(EncA1, INPUT);
  pinMode(EncB1, INPUT);
  pinMode(EncA2, INPUT);
  pinMode(EncB2, INPUT);
}


// The loop routine runs over and over again forever.
void loop() {
    //Reading data from the encoders
  int a1 = digitalRead(EncA1);
  int b1 = digitalRead(EncB1);
  int a2 = digitalRead(EncA2);
  int b2 = digitalRead(EncB2);

    //print onto serial monitor
  //Serial.print("LEFT MOTOR ");
  Serial.print(a1*5);
  Serial.print(",x");
  Serial.print(b1*5);
  
  //Serial.print(" RIGHT MOTOR ");
  Serial.print(","); 
  Serial.print(a2*5);
  Serial.print(",");
  Serial.print(b2*5);
  Serial.println();



  motor1.setSpeed(-255);   // Motor 1 runs forward at 50% speed.
  motor2.setSpeed(255);  // Motor 2 runs backward at 50% speed.
  delay(5000);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(5000);

  /*motor1.setSpeed(-255);  // Motor 1 runs backward at 50% speed.
  motor2.setSpeed(-255);   // Motor 2 runs forward at 50% speed.
  delay(1000);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(5000);*/
  /*Serial.println(pos);
  
  motor1.setSpeed(255);   // Motor 1 runs forward at full speed.
  motor2.setSpeed(-255);  // Motor 2 runs backward at full speed.
  delay(1000);
  Serial.println(pos);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(1000);
  Serial.println(pos);

  motor1.setSpeed(-255);  // Motor 1 runs backward at 50% speed.
  motor2.setSpeed(255);   // Motor 2 runs forward at 50% speed.
  delay(1000);
  Serial.println(pos);

  motor1.setSpeed(-255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(255);   // Motor 2 runs forward at full speed.
  delay(1000);
  Serial.println(pos);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(1000);
  Serial.println(pos);
  */


}
