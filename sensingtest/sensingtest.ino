#include <Servo.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int count = 0;
const int servoPin1 = 5;
const int servoPin2 = 6;
const int samples = 25; // Number of samples to average
const int approxOrder = 3; // Order of distance approximation function (1,2,3)
int values[samples];
Servo servo1;
Servo servo2; 
int servo1Pos = 0;
int servo2Pos = 0;
const int servoStart = 40;
const int servoEnd = 140;

void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
}

int average(int values[]) {
  int sum = 0;
  int length = sizeof(values)/sizeof(int);
  for (int i = 0; i < length; i++) {
    sum += values[i];
  }
  return sum/length;
}

float distance(int value, int order) {
  float dist;
  switch (order) {
    case 3:
      dist = -0.000001211*pow(value,3)+0.0015*pow(value,2)-0.7193*value+154.49;
      break;
    case 2:
      dist = 0.0002*pow(value,2)-0.2315*value+99.687;
      break;
    case 1:
      dist = -0.113*value+79.55;
      break;
    default:
      return 0;
      break;
  }
  return dist;
}

unsigned long varience(int values[], int average) {
  unsigned long sumSquared = 0;
  int length = sizeof(values)/sizeof(int);
  for (int i = 0; i < length; i++) {
    sumSquared += pow(values[i],2);
  }
  unsigned long normSumSquared = sumSquared / length;
  return normSumSquared - pow(average,2);
}


/*
* Do a full scan of one direction
* type: 0 = horizontal
* type: 1 = vertical 
*/
void scan(int type) {
  Servo servo;
  int *servoPos;
  if (!type) {
    servo = servo1;
    servoPos = &servo1Pos;
  } else {
    servo = servo2;
    servoPos = &servo2Pos;
  }
  int averageValue;
  for (*servoPos = servoStart; *servoPos < servoEnd; (*servoPos)++) {
    servo.write(*servoPos);
    for (int i = 0; i < samples; i++) {
      values[i] = analogRead(sensorPin);
      delay(1);
    }
    averageValue = average(values);
    Serial.print(servo1Pos);
    Serial.print(",");
    Serial.print(servo2Pos);
    Serial.print(",");
    Serial.println(distance(averageValue, approxOrder));
  }
  //Give time to reset to start
  servo.write(servoStart);
  delay(300);
}


void loop() {
  scan(0);
  scan(1);
}