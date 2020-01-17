#include "I2Cdev.h"                                                                              
#include "MPU6050.h"
#include "Wire.h"
 
MPU6050 detect;
int16_t ax, ay, az, gx, gy, gz;
int16_t rec_ax, rec_ay, rec_az, rec_gx, rec_gy, rec_gz;
 
void setup() {
  Wire.begin();
  detect.initialize();
  pinMode(13, OUTPUT);
}
 
void loop() {
  detect.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  delay(15);
  detect.getMotion6(&rec_ax, &rec_ay, &rec_az, &rec_gx, &rec_gy, &rec_gz);
  if (abs(rec_ax-ax)>7000 or abs(rec_ay-ay)>7000){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
}
