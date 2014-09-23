int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int count;
const int samples = 25;
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

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  int i = count % samples;
  values[i] = sensorValue;
  if (i == 0) {
    Serial.println(average(values)); 
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