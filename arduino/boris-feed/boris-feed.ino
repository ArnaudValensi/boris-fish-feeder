#include <Servo.h> 

/**
 * TIME_BETWEEN_FEEDS_IN_MINUTES is the time between two rations.
 */
#define TIME_BETWEEN_FEEDS_IN_MINUTES (24 * 60) // Every day

/**
 * IDLE_SPEED is the value sent to the servo motor to have a speed of 0.
 * Here I'm using a Futaba S3003 modified to have a continuous rotation, so
 * if I give a value from 89 to 0 it controls the speed counter clockwise
 * and if I give a value from 91 to 180 it controls the speed clockwise.
 */
#define IDLE_SPEED 90

/**
 * SPEED is the value added to IDLE_SPEED to move the servo.
 */
#define SPEED       9

/**
 * STEP_TIME is the time we need at the given speed (SPEED) to give one 
 * ration of food.
 * To get a good value I timed how long it takes to spin 10 turn. The 
 * result was 29.71. It is divided by the total number of rations,
 * multiplicated by 1000 to get it in milliseconds.
 */
#define STEP_TIME   (29.71 / 10 / 8 * 1000)

/**
 * SERVO_PIN is the digital pin on the arduino where the servo is connected.
 */
#define SERVO_PIN   9

/**
 * Variables
 */
Servo myservo;

int incomingByte = 0;
unsigned int tmpTime = 0;
int nbElapsedFeeds = 0;
const unsigned int TIME_BETWEEN_FEEDS = (TIME_BETWEEN_FEEDS_IN_MINUTES * 60 * 1000);

/**
 * Setup
 */
#define p(x)  Serial.print(x);
#define pln(x)  Serial.println(x);
 
void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  myservo.write(IDLE_SPEED);
}

/**
 * Main loop
 */
void loop() {
  delay(1000);

  tmpTime = millis() / TIME_BETWEEN_FEEDS;
  
  if (tmpTime > nbElapsedFeeds) {
    nbElapsedFeeds = tmpTime;

    myservo.write(IDLE_SPEED + SPEED);
    delay(STEP_TIME);
    myservo.write(IDLE_SPEED);
  }
}
