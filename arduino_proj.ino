/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

#define PIN_SERVO_ROT   9
#define PIN_SERVO_TILT  10
#define PIN_SERVO_GRAB  11
#define PIN_SERVO_ELEV  12

#define PIN_THUMB_ROT   A0
#define PIN_THUMB_TILT  A1
#define PIN_BUT_GRAB_S  1
#define PIN_BUT_GRAB_R  2
#define PIN_BUT_ELEV_S  3
#define PIN_BUT_ELEV_R  4

Servo myservo_rot;   // create servo object to control a servo
Servo myservo_tilt;  // create servo object to control a servo
Servo myservo_grab;  // create servo object to control a servo
Servo myservo_elev;  // create servo object to control a servo

int angle_servo_rot = 90;
int angle_servo_tilt = 90;
int angle_servo_grab = 90;
int angle_servo_elev = 90;

int an_thumb_rot = 0;
int an_thumb_tilt = 0;

void setup() {
  myservo_rot.attach(PIN_SERVO_ROT);  // attaches the servo on pin 9 to the servo object
  myservo_tilt.attach(PIN_SERVO_TILT);
  myservo_grab.attach(PIN_SERVO_GRAB);
  myservo_elev.attach(PIN_SERVO_ELEV);

  pinMode(PIN_BUT_GRAB_S, INPUT_PULLUP);
  pinMode(PIN_BUT_GRAB_R, INPUT_PULLUP);
  pinMode(PIN_BUT_ELEV_S, INPUT_PULLUP);
  pinMode(PIN_BUT_ELEV_R, INPUT_PULLUP);
}

void loop() {

  // Process rotation servo
  an_thumb_rot  = analogRead( PIN_THUMB_ROT );

  if( an_thumb_rot > 850 ){
    increment_servo_angle( &angle_servo_rot, 2 );
  }
  else if( an_thumb_rot > 680 ){
    increment_servo_angle( &angle_servo_rot, 1 );
    angle_servo_rot += 1;
  }
  else if( an_thumb_rot < 170 ){
    increment_servo_angle( &angle_servo_rot, -2 );
  }
  else if( an_thumb_rot < 340 ){
    increment_servo_angle( &angle_servo_rot, -1 );
  }
  myservo_rot.write( angle_servo_rot );

  // Process Tilt Servo
  an_thumb_tilt = analogRead( PIN_THUMB_TILT );

  if( an_thumb_tilt > 850 ){
    increment_servo_angle( &angle_servo_tilt, 2 );
  }
  else if( an_thumb_tilt > 680 ){
    increment_servo_angle( &angle_servo_tilt, 1 );
    angle_servo_rot += 1;
  }
  else if( an_thumb_tilt < 170 ){
    increment_servo_angle( &angle_servo_tilt, -2 );
  }
  else if( an_thumb_tilt < 340 ){
    increment_servo_angle( &angle_servo_tilt, -1 );
  }
  myservo_rot.write( angle_servo_tilt );

  // Process Grab servo
  if( !digitalRead( PIN_BUT_GRAB_S ) )
  {
    increment_servo_angle( &angle_servo_grab, 1 );
  }
  else if( !digitalRead( PIN_BUT_GRAB_R ) )
  {
    increment_servo_angle( &angle_servo_grab, -1 );
  }
  myservo_rot.write( angle_servo_grab );

  // Process elev servo
  if( !digitalRead( PIN_BUT_ELEV_S ) )
  {
    increment_servo_angle( &angle_servo_elev, 1 );
  }
  else if( !digitalRead( PIN_BUT_ELEV_R ) )
  {
    increment_servo_angle( &angle_servo_elev, -1 );
  }
  myservo_rot.write( angle_servo_elev );  
  
  delay(15);

}

void increment_servo_angle( int *angle_var, int increment )
{
   *angle_var += increment;

   if( *angle_var < 0 ){
      *angle_var = 0;
   }
   else if( *angle_var > 180 ){
    *angle_var = 180;
   }
}
