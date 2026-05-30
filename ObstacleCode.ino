#include <Servo.h>

// Motor driver pins
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;
const int ENA = 9;
const int ENB = 10;

// Ultrasonic sensor pins
const int trigPin = 12;
const int echoPin = 11;

// Servo
Servo scanner;
const int servoPin = 3;

// Distance threshold
const int obstacleThreshold = 20; // in cm

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Enable motors at full speed
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);

  // Ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo
  scanner.attach(servoPin);
  scanner.write(90); // Face forward
  delay(500);
}

void loop() {
  int distance = measureDistance();

  if (distance < obstacleThreshold) {
    stopMotors();
    delay(500);

    int leftDist = lookAround(150); // Look left
    int rightDist = lookAround(30); // Look right

    if (leftDist > rightDist && leftDist > obstacleThreshold) {
      turnLeft();
      delay(400);
    }
    else if (rightDist > obstacleThreshold) {
      turnRight();
      delay(400);
    }
    else {
      moveBackward();
      delay(500);
    }
  }
  else {
    moveForward();
  }

  delay(100);
}

// Measure distance in front
int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);
  int distance = duration * 0.034 / 2;

  return distance;
}

// Scan with servo
int lookAround(int angle) {
  scanner.write(angle);
  delay(500);
  return measureDistance();
}

// Movement functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
