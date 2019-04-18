#include<Wire.h>
const int mpu_address = 0x68;
int16_t ACC_X, ACC_Y;
int firstX_read, secondX_read, thirdX_read;
int firstY_read, secondY_read, thirdY_read;
int result12_X, result12_Y;
int result13_X, result13_Y;
int result23_X, result23_Y;
int counter12_X, counter13_X, counter23_X;
int counter12_Y, counter13_Y, counter23_Y;
int heap_X, heap_Y;

void setup() {
  pinMode(11,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(mpu_address);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(mpu_address);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(mpu_address,4,true);
  ACC_X = Wire.read() << 8 | Wire.read();
  ACC_Y = Wire.read() << 8 | Wire.read();
  firstX_read = ACC_X;
  firstY_read = ACC_Y;
  delay(500);
  ACC_X = Wire.read() << 8 | Wire.read();
  ACC_Y = Wire.read() << 8 | Wire.read();
  secondX_read = ACC_X;
  secondY_read = ACC_Y;
  delay(500);
  ACC_X = Wire.read() << 8 | Wire.read();
  ACC_Y = Wire.read() << 8 | Wire.read();
  thirdX_read = ACC_X;
  thirdY_read = ACC_Y;
  result12_X = abs(firstX_read - secondX_read);
  result13_X = abs(firstX_read - thirdX_read);
  result23_X = abs(secondX_read - thirdX_read);
  result12_Y = abs(firstY_read - secondY_read);
  result13_Y = abs(firstY_read - thirdY_read);
  result23_Y = abs(secondY_read - thirdY_read);
  if (result12_X >= 4300)
  {
    counter12_X = 1;
  }
  else
  {
    counter12_X = 0;
  }
  if (result12_Y >= 4300)
  {
    counter12_Y = 1;
  }
  else
  {
    counter12_Y = 0;
  }
  if (result13_X >= 4300)
  {
    counter13_X = 1;
  }
  else
  {
    counter13_X = 0;
  }
  if (result13_Y >= 4300)
  {
    counter13_Y = 1;
  }
  else
  {
    counter13_Y = 0;
  }
  if (result23_X >= 4300)
  {
    counter23_X = 1;
  }
  else
  {
    counter23_X = 0;
  }
  if (result23_Y >= 4300)
  {
    counter23_Y = 1;
  }
  else
  {
    counter23_Y = 0;
  }
  heap_X = counter12_X + counter13_X + counter23_X;
  heap_Y = counter12_Y + counter13_Y + counter23_Y;
  if (heap_X >= 2 or heap_Y >= 2)
  {
    digitalWrite(11,HIGH);
    Serial.print(1);
  }
  else 
  {
    digitalWrite(11,LOW);
    Serial.print(0);
  }
}
