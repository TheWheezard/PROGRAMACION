
/*
  simpleMovements.ino

 The simpleMovements sketch shows how to move each servo motor of the Braccio

 Created on 18 Nov 2015
 by Andrea Martino

 This example is in the public domain.
 */

#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);
}

void loop() {
   /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees. Allowed values from 0 to 180 degrees
   M2=shoulder degrees. Allowed values from 15 to 165 degrees
   M3=elbow degrees. Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the tongue is open, 73: the gripper is closed.
  */
  
  // PINZA
  
                       //(step delay, M1, M2, M3, M4, M5, M6);
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  mover_pinza();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  rotar_muneca();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  vertical_muneca();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  mover_codo();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  mover_hombro();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  mover_base();
  Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  36);

  // //Wait 1 second
  delay(5000);
}

//M6
void mover_pinza() {
  for (int i=73; i>=10; i--) {
    Braccio.ServoMovement(20,           90,  90, 90, 90, 90,  i);
  }
}

//M5
void rotar_muneca() {
  for (int i=170; i>=10; i--) {
    Braccio.ServoMovement(20,           90,  90, 90, 90, i,  36);
  } 
}

//M4
void vertical_muneca() {
  for (int i=170; i>=10; i--) {
    Braccio.ServoMovement(20,           90,  90, 90, i, 90,  36);
  }
}

//M3
void mover_codo() {
  for (int i=170; i>=10; i--) {
    Braccio.ServoMovement(20,           90,  90, i, 90, 90,  36);
  }
}

//M2
void mover_hombro() {
  for (int i=155; i>=25; i--) {
    Braccio.ServoMovement(20,           90,  i, 90, 90, 90,  36);
  }
}

//M1
void mover_base() {
  for (int i=170; i>=10; i--) {
    Braccio.ServoMovement(20,           i,  90, 90, 90, 90,  36);
  }
}