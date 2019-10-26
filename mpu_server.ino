#include <wire.h>
const int mpu_address = 0x68;
const int detect_times = 173;
int16_t rex, rey;
int xyarr[detect_times][2];

void setup(){
    pinMode(11,1);
    Wire.begin();
    Wire.beginTransmission(mpu_address);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);
}

void loop(){
    Wire.beginTransmission(mpu_address);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(mpu_address,4,true);
    for (int i;i<detect_times-1;i++){
        rex = Wire.read() << 8 | Wire.read();
        rey = Wire.read() << 8 | Wire.read();
            xyarr[i][0] = rex;
            xyarr[i][1] = rey;
            delay(3.5);
    }
    if (detect(xyarr)){
            digitalWrite(11,1);
            Serial.print(1);
    }
    else{
            digitalWrite(11,0);
            Serial.print(0);
    }
}

float sigmoid(int x){
    return (1 / (1 + exp(-x)));
}

bool detect(int arr[][2]){
        int sumx, sumy;
        for (int j;j<detect_times-2;j++){
            diffx = sigmoid(abs(arr[j][0] - arr[j+1][0]));
            diffy = sigmoid(abs(arr[j][1] - arr[j+1][1]));
            sumx += diffx;
            sumy += diffy;
        }
        if (sumx==172 or sumy==172)
                return true;
        else
                return false;
}

