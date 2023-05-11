#include <QTRSensors.h>
QTRSensors qtr;
int flagTurn = 0;
int flagFastSlow = 0;
int qtrMin[8]{};
int qtrMax[8]{};
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
int SPEED = 255;

void setup() {
  Serial.begin(9600);
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5, A6, A7 }, SensorCount);
  // qtr.setEmitterPin(13);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // Call calibrate() 400 times to make calibration take about +-10 seconds.
  for (int i = 0; i < 240; i++) {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
  // print the calibration minimum values measured when emitters were on
  /* Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++) {
    qtrMin[i] = qtr.calibrationOn.minimum[i];
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
    delay(20);
  }
  Serial.println();*/
  // print the calibration maximum values measured when emitters were on
  /*for (uint8_t i = 0; i < SensorCount; i++) {
    qtrMax[i] = qtr.calibrationOn.maximum[i];
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
    delay(20);
  }*/
  Serial.println();
  Serial.println();
  //delay(1000);
}
void motor(int left, int right) {
  analogWrite(10, left);
  digitalWrite(8, 0);
  digitalWrite(7, 1);
  digitalWrite(6, 1);
  digitalWrite(5, 1);
  digitalWrite(4, 0);
  analogWrite(3, right);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  // read calibrated sensor values and obtain a measure of the line position
  int position = qtr.readLineBlack(sensorValues);
  // print the sensor values as numbers from 0 to 1000
  for (int i = 0; i < SensorCount; i++) {
    Serial.println(sensorValues[i]);
    //  Serial.print('\t');
    //ForwardDirection
    if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] > 400 &&  // sensor #3 and #4 Forward driving
        sensorValues[4] > 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(200, 200);
      flagTurn = 0;
      delay(1);
    }else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] > 400 &&  // sensor #3 Forward driving
        sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(150, 200);
      flagTurn = 0;
      delay(1);
    }
    //Slow and Fast changing speed when all sensors on black line
    /* else if (sensorValues[0] > 400 && sensorValues[1] > 400 && sensorValues[2] > 400 && sensorValues[3] > 400 && 
             sensorValues[4] > 400 && sensorValues[5] > 400 && sensorValues[6] > 400 && sensorValues[7] > 400) {
      if (flagFastSlow == 0) {
        motor(160, 160); //Slower
        flagFastSlow = 1;
        delay(250);
      } else {
        motor(210, 210); //Faster
        flagFastSlow = 0;
        delay(250);
      }*/
    //LeftDirection
    else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] > 400 && sensorValues[3] > 400 &&  //sensor #2 and #3 LEftTurning
             sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(100, 240);
      delay(1);
      flagTurn = 1;
      }else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] > 400 && sensorValues[3] < 400 &&  //sensor #2 LEftTurning
             sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(85, 245);
      delay(1);
      flagTurn = 1;
    } else if (sensorValues[0] < 400 && sensorValues[1] > 400 && sensorValues[2] > 400 && sensorValues[3] < 400 &&  //sensor #1 and #2 LEftTurning
               sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(70, 230);
      flagTurn = 2;
      delay(1);
      }else if (sensorValues[0] < 400 && sensorValues[1] > 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #1 LEftTurning
               sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(60, 230);
      flagTurn = 2;
      delay(1);
    } else if (sensorValues[0] > 400 && sensorValues[1] > 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //Sensors #0 and #1 LeftTurning
               sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(30, 245);
      flagTurn = 2;
      delay(1);
    } 
    else if (sensorValues[0] > 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //Sensors #0 LeftTurning
               sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(25, 255);
      flagTurn = 2;
      delay(1);
    }
    else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #4 and #5 RightTurnring
               sensorValues[4] > 400 && sensorValues[5] > 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(220, 100);
      flagTurn = 3;
      delay(1);
    }
    else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #4 RightTurnring
               sensorValues[4] > 400 && sensorValues[5] < 400 && sensorValues[6] < 400 && sensorValues[7] < 400) {
      motor(220, 50);
      flagTurn = 3;
      delay(1);
    } else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #5 and #6 RightTurnring
               sensorValues[4] < 400 && sensorValues[5] > 400 && sensorValues[6] > 400 && sensorValues[7] < 400) {
      motor(240, 100);
      flagTurn = 4;
      delay(1);
    }  else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #6 RightTurnring
               sensorValues[4] < 400 && sensorValues[5] > 400 && sensorValues[6] > 400 && sensorValues[7] < 400) {
      motor(240, 50);
      flagTurn = 4;
      delay(1);
    } else if (sensorValues[0] < 400 && sensorValues[1] < 400 && sensorValues[2] < 400 && sensorValues[3] < 400 &&  //sensor #6 and #7 RightTurnring
               sensorValues[4] < 400 && sensorValues[5] < 400 && sensorValues[6] > 400 && sensorValues[7] > 400) {
      motor(240, 30);
      flagTurn = 4;
      delay(1);
    } 
    //Find the black line around themselves
    /*else if (sensorValues[0] < 500 && sensorValues[1] < 500 && sensorValues[2] < 500 && sensorValues[3] < 500 &&  //FIND
               sensorValues[4] < 500 && sensorValues[5] < 500 && sensorValues[6] < 500 && sensorValues[7] < 500) {
      motor(0, 200);
      flagTurn == 1 && flagTurn == 2;
      delay(1);
    } else if (sensorValues[0] < 500 && sensorValues[1] < 500 && sensorValues[2] < 500 && sensorValues[3] < 500 &&  //FIND
               sensorValues[4] < 500 && sensorValues[5] < 500 && sensorValues[6] < 500 && sensorValues[7] < 500) {
      motor(200, 0);
      (flagTurn == 3 && flagTurn == 4);
      delay(1);
    }*/
  }
  //Serial.println(position);
  // delay(250);
}