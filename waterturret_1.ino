

#include <XBOXUSB.h>
#include <AccelStepper.h>
#include <Stepper.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
XBOXUSB Xbox(&Usb);
AccelStepper accstepperx(1,5,4);
AccelStepper accsteppery(1,7,6);
int maxspeed = 2000;
int accspeed = 1000;
float xangle=0,yangle=0;
int stp=1;
void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
   accstepperx.setMaxSpeed(maxspeed);
   accstepperx.setAcceleration(accspeed);
   accstepperx.setCurrentPosition(0); 
   accsteppery.setMaxSpeed(maxspeed);
   accsteppery.setAcceleration(accspeed);
   accsteppery.setCurrentPosition(0); 
}
void loop() {
  accstepperx.run();
  accsteppery.run();
  
  Usb.Task();
  if (Xbox.Xbox360Connected) {
    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
      //Serial.print("L2: ");
      //Serial.print(Xbox.getButtonPress(L2));
      Serial.print("\tR2: ");
      Serial.println(Xbox.getButtonPress(R2));
      
    } 
    else{
      
  }
    
        if(Xbox.getAnalogHat(LeftHatX)>7500 && accstepperx.distanceToGo() == 0){
          xangle=xangle+stp;
          Serial.println(xangle);
          accstepperx.moveTo(xangle);
        }
        else if(Xbox.getAnalogHat(LeftHatX)<-7500&& accstepperx.distanceToGo() == 0){
          xangle=xangle-stp;
          Serial.println(xangle);
          accstepperx.moveTo(xangle);
        }
        if(Xbox.getAnalogHat(LeftHatY)>7500 &&accsteppery.distanceToGo() == 0){
          yangle=yangle+stp;
          Serial.println(yangle);
          accsteppery.moveTo(yangle);
        }
        else if(Xbox.getAnalogHat(LeftHatY)<-7500&& accsteppery.distanceToGo() == 0){
          yangle=yangle-stp;
          Serial.println(yangle);
          accsteppery.moveTo(yangle);
        }
        /*
    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        Serial.print(F("LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");
        
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        Serial.print(F("LeftHatY: "));
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");
       
      }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        Serial.print(F("RightHatX: "));
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        Serial.print(F("RightHatY: "));
        Serial.print(Xbox.getAnalogHat(RightHatY));
      }
      Serial.println();
    }
  */
    if (Xbox.getButtonClick(UP)) {
      Xbox.setLedOn(LED1);
      Serial.println(F("Up"));
      stp=stp+10;
      Serial.println(stp);
    }
    if (Xbox.getButtonClick(DOWN)) {
      Xbox.setLedOn(LED4);
      Serial.println(F("Down"));
      stp=stp-10;
      Serial.println(stp);

    }
    if (Xbox.getButtonClick(LEFT)) {
      Xbox.setLedOn(LED3);
      Serial.println(F("Left"));
    }
    if (Xbox.getButtonClick(RIGHT)) {
      Xbox.setLedOn(LED2);
      Serial.println(F("Right"));
    }

    if (Xbox.getButtonClick(START)) {
      Xbox.setLedMode(ALTERNATING);
      Serial.println(F("Start"));
      xangle=0;
      yangle=0;
      accstepperx.moveTo(xangle);
      accsteppery.moveTo(yangle);
    }
    if (Xbox.getButtonClick(BACK)) {
      Xbox.setLedBlink(ALL);
      Serial.println(F("Back"));
    }
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));

    if (Xbox.getButtonClick(L1))
      Serial.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      Serial.println(F("R1"));
    if (Xbox.getButtonClick(XBOX)) {
      Xbox.setLedMode(ROTATING);
      Serial.println(F("Xbox"));
    }

    if (Xbox.getButtonClick(A))
      Serial.println(F("A"));
    if (Xbox.getButtonClick(B))
      Serial.println(F("B"));
    if (Xbox.getButtonClick(X))
      Serial.println(F("X"));
    if (Xbox.getButtonClick(Y))
      Serial.println(F("Y"));
  }
  //delay(1);
}
