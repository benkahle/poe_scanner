int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int count;
const int samples = 25; // Number of samples to average
const int approxOrder = 3; // Order of distance approximation function (1,2,3)
int values[samples];

void setup() {
  Serial.begin(9600);
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
      dist = 0.0026*pow(value,3)-0.1943*pow(value,2)-5.8401*value+686.78;
      break;
    case 2:
      dist = 0.1041*pow(value,2)-16.264*value+795.8;
      break;
    case 1:
      dist = -8.3593*value+665.82;
      break;
    default:
      return 0;
      break;
  }
  return dist;
}

int varience(int values[], int average) {
  int sumSquared = 0;
  int length = sizeof(values)/sizeof(int);
  for (int i = 0; i < length, i++) {
    sumSquared += pow(values[i],2);
  }
  int normSumSquared = sumSquared / length;
  return normSumSquared - pow(average,2);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  int i = count % samples;
  int averageValue;
  values[i] = sensorValue;
  if (i == 0) {
    averageValue = average(values);
    Serial.print(average(values));
    Serial.print(",");
    Serial.print(distance(averageValue, approxOrder));
    Serial.print(",");
    Serial.println(varience(values, average(values)));
  }
}

// // Sweep
// // by BARRAGAN <http://barraganstudio.com> 
// // This example code is in the public domain.


// #include <Servo.h> 
 
// Servo myservo;  // create servo object to control a servo 
//                 // a maximum of eight servo objects can be created 
 
// int pos = 0;    // variable to store the servo position 
 
// void setup() 
// { 
//   myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
// } 
 
 
// void loop() 
// { 
//   for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//   {                                  // in steps of 1 degree 
//     myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//     delay(15);                       // waits 15ms for the servo to reach the position 
//   } 
//   for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
//   {                                
//     myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//     delay(15);                       // waits 15ms for the servo to reach the position 
//   } 
// } 