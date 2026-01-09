#ifndef SPIDER_H
#define SPIDER_H

#include <Servo.h>

// PINS
#define PWMA 5
#define AIN1 8
#define AIN2 4
#define PWMB 6
#define BIN1 3
#define BIN2 13
#define MOTORS_STBY 7
#define SERVO_HEAD 12

// Ultrasound sensors
#define ECHO_HEAD A0
#define TRIG_HEAD A1
#define ECHO_LEFT A2
#define TRIG_LEFT A3
#define ECHO_RIGHT A4
#define TRIG_RIGHT A5
#define MAX_DISTANCE 400.0 // cm
#define MIN_DISTANCE 2.0 // cm

// CONSTANTS
#define SPEED_MOVE 180
#define SPEED_TURN 150
#define SPEED_TURN_FACTOR 0.9
#define INIT_ANGLE 75


// Movement
const int MOTOR_LEFT[3] = {AIN2, AIN1, PWMA};
const int MOTOR_RIGHT[3] = {BIN1, BIN2, PWMB};

enum direction {
  FORWARD = 0,
  BACKWARD,
  LEFT,
  RIGHT,
};


// Class of our robot
class Spider {
private:
  Servo servo;

  // FUNCTIONS
  // Return distance in cm
  float get_dist(int trig, int echo) {
    // Clean
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    // Send trig
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Calculate distance
    float duration = pulseIn(echo, HIGH, 30000);
    float dist = duration * 0.034 / 2;

    //Return error with very low values
    // or with very HIGH ones
    if (dist < MIN_DISTANCE || dist > MAX_DISTANCE) {
      //dist = get_dist(trig, echo);
      return MAX_DISTANCE;
    }

    // Reactivate when valid dist is obtained
    return dist;
  }

public:
  Spider() {
    // Set pins
    pinMode(MOTORS_STBY, OUTPUT);
    pinMode(MOTOR_LEFT[0], OUTPUT);
    pinMode(MOTOR_LEFT[1], OUTPUT);
    pinMode(MOTOR_RIGHT[0], OUTPUT);
    pinMode(MOTOR_RIGHT[1], OUTPUT);
  
    // us pins
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(TRIG_HEAD, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(ECHO_RIGHT, INPUT);
    pinMode(ECHO_HEAD, INPUT);
  }


  // GETTERS
  float get_dist_head() {
    return get_dist(TRIG_HEAD, ECHO_HEAD);
  }
  float get_dist_left() {
    return get_dist(TRIG_LEFT, ECHO_LEFT);
  }
  float get_dist_right() {
    return get_dist(TRIG_RIGHT, ECHO_RIGHT);
  }


  // SERVO FUNCTIONS
  void head_set_to(int angle) {
    if (!servo.attached()) { // Si está desconectado, conéctalo
        servo.attach(SERVO_HEAD);
    }
    servo.write(angle);
  }


  // INIT / STOP
  void init_all(bool reset_head) {
    digitalWrite(MOTORS_STBY, HIGH);
    set_speed(0, 0);

    // Move servo to original pos
    servo.attach(SERVO_HEAD);
    if (reset_head) {
      head_set_to(INIT_ANGLE);
    }
  }

  // Stop motors, can reset servo pos too
  void stop_all(bool reset_head) {
    digitalWrite(MOTORS_STBY, LOW);
    set_speed(0, 0);

    digitalWrite(MOTOR_LEFT[0], LOW);
    digitalWrite(MOTOR_LEFT[1], LOW);
    digitalWrite(MOTOR_RIGHT[0], LOW);
    digitalWrite(MOTOR_RIGHT[1], LOW);

    // Move servo to original pos
    if (reset_head) {
      head_set_to(INIT_ANGLE);
    }
    servo.detach();
  }

  // set 'speed' speed
  void set_speed(int speed_left, int speed_right) {
    analogWrite(MOTOR_LEFT[2], speed_left * SPEED_TURN_FACTOR);
    analogWrite(MOTOR_RIGHT[2], speed_right);
  }

  void stop() {
    set_speed(0, 0);
    
    digitalWrite(MOTOR_LEFT[0], LOW);
    digitalWrite(MOTOR_LEFT[1], LOW);
    digitalWrite(MOTOR_RIGHT[0], LOW);
    digitalWrite(MOTOR_RIGHT[1], LOW);
  }

  // MOVEMENT FUNCTION
  void move(enum direction dir, int speed = SPEED_MOVE) {
    set_speed(speed, speed);
    
    switch(dir) {
    case FORWARD:
      digitalWrite(MOTOR_LEFT[0], HIGH);
      digitalWrite(MOTOR_LEFT[1], LOW);
      digitalWrite(MOTOR_RIGHT[0], HIGH);
      digitalWrite(MOTOR_RIGHT[1], LOW);
      break;
    case BACKWARD:
      digitalWrite(MOTOR_LEFT[0], LOW);
      digitalWrite(MOTOR_LEFT[1], HIGH);
      digitalWrite(MOTOR_RIGHT[0], LOW);
      digitalWrite(MOTOR_RIGHT[1], HIGH);
      break;
    default:
      stop_all(false);
      Serial.println("Wrong move dir");
    }
  }

  void turn(enum direction dir, int speed = SPEED_TURN) {
    set_speed(speed, speed);
    
    switch(dir) {
    case LEFT:
      digitalWrite(MOTOR_LEFT[0], LOW);
      digitalWrite(MOTOR_LEFT[1], HIGH);
      digitalWrite(MOTOR_RIGHT[0], HIGH);
      digitalWrite(MOTOR_RIGHT[1], LOW);
      break;
    case RIGHT:
      digitalWrite(MOTOR_LEFT[0], HIGH);
      digitalWrite(MOTOR_LEFT[1], LOW);
      digitalWrite(MOTOR_RIGHT[0], LOW);
      digitalWrite(MOTOR_RIGHT[1], HIGH);
      break;
    default:
      stop_all(false);
      Serial.println("Wrong turn dir");
    }
  }
};

#endif