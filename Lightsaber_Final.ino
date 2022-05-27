#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>
#include <SD.h> 
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
TMRpcm tmrpcm;   // create an object for use in this sketch
char mychar;
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int ggx, ggy, ggz;
int gyronow;
int gyrolast;

void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 9;
  Serial.begin (9600);
  accelgyro.initialize();
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  //tmrpcm.play("VADER.WAV"); //plays this sound 
  //tmrpcm.setVolume(6);  
}

void loop() {
  // put your main code here, to run repeatedly:
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ggx = gx / 131.00;
  ggy = gy / 131.00;
  ggz = gz / 131.00;
  gyronow = ggy;
  int a = gyrolast - gyronow; // compare angle acceleration
  gyrolast = ggy;
  if(a > 200 || a < 200){
    //play sound1
    //tmrpcm.play(); 
    //tmrpcm.setVolume(6);
    delay(1000);
  }
  if( ggy >= 100){
    //play sound2
    delay(500);
  }
  if( ggy <= -100){
    //play sound3
    delay(500);
  }
  if(ggz >= 100 ||ggz <= -100  ){
    //play sound4
    delay(500);
   
  }
}
