#include <Servo.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
const int servoPin1 = 5;
const int servoPin2 = 6;
const int samples = 25; // Number of samples to average
const int approxOrder = 3; // Order of distance approximation function (1,2,3)
int values[samples];
Servo servo1;
Servo servo2; 
int servo1Pos = 0;
int servo2Pos = 0;

void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
}

/*
* Calculate the average value of a list of integers
*/
float average(int values[]) {
  int sum = 0;
  int length = sizeof(values)/sizeof(int);
  float averageValue = 0;
  for (int i = 0; i < length; i++) {
    sum += values[i];
  }
  averageValue = sum/length;
  return averageValue;
}

/*
* Tranform the IR sensor measurement into centimeters
* value: the value of the IR sensor
* order: the order of the approximation function to use (1,2,3)
*/
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
/*
* Do a full scan of one direction, printing servo angles and distance in cm at each degree 
* type: 0 = horizontal; 1 = vertical
* start: start degree for server
* end: end degree for server
*/
void scan(int type, int start, int end) {
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
  int high;
  int low;
  int add = 0;
  if (start <= end) {
    add = 1;
  } else {
    add = 0;
  }
  *servoPos = start;
  while(1) {
    if (*servoPos == end) {
      break;
    }
    servo.write(*servoPos);
    for (int i = 0; i < samples; i++) {
      values[i] = analogRead(sensorPin);
      delay(2);
    }
    averageValue = average(values);
    Serial.print(servo1Pos);
    Serial.print(",");
    Serial.print(servo2Pos);
    Serial.print(",");
    Serial.println(distance(averageValue, approxOrder));
    if (add) {
      (*servoPos)+=1;
    } else {
      (*servoPos)-=1;
    }
  }
  //Give time to reset to start
  servo.write(start);
  delay(300);
}
 
void loop() {
  int vertStart = 120;
  int vertEnd = 85;
  int hozStart = 180;
  int hozEnd = 130;
  //Start in bottom right corner
  servo2.write(vertStart);
  servo1.write(hozStart);
  //Wait for servos to reach start position
  delay(1000);
  //Print new lines between runs for easy splitting
  for (int k = 0; k < 20; k++) {
    Serial.println("");
  }
  //For each vertical degree, do a horizontal scan.
  for (int i = vertStart; i != vertEnd; i -= 1) {
    servo2Pos = i;
    servo2.write(servo2Pos);
    delay(5);
    scan(0, hozStart, hozEnd);
  }
  delay(10000);
}