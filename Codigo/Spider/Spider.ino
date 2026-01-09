#include "Spider.h"
#include "Control.h"
#include "Thread.h"

// Constants
const int ledPIN = 9;
#define WALL_DIST 15
#define WALL_DIST_RIGHT WALL_DIST + 5
#define WALL_LONG_DIST WALL_DIST + 18
#define WALL_SHORT_DIST WALL_DIST + 5

#define OBSTACLE_DIST 20
#define OBSTACLE_THRESHOLD 10
#define CHECKING_ANGLE INIT_ANGLE + 30

float Kp = 35.0; 
float Kd = 45.0; 
float last_error = 0;
float total_time = 0.0;

float right_distance = 0.0;
float left_distance = 0.0;

// State machine states
enum states {
  MANUAL = 0,
  SEARCH_WALL,
  AVOIDING,
  FOLLOW_WALL,
  TURN
};

enum modes {
  IDLE = 0,
  CASE_1,
  CASE_2
};

enum walls {
  W_FRONT = 0,
  W_LEFT,
  W_RIGHT
};


// Global variables
Spider spider;
enum states state;
enum modes mode;
enum walls wall_side;


bool is_obstacle() {
  delay(100);
  if (spider.get_dist_head() < OBSTACLE_DIST) {
    return true;
  }
  return false;
}

bool confirm_obstacle() {
    // Mirar arriba
    spider.head_set_to(CHECKING_ANGLE);
    delay(500);

    float dist_up = spider.get_dist_head(); 

    // Evitamos valores inválidos
    while (dist_up == MAX_DISTANCE) {
      delay(100);
      dist_up = spider.get_dist_head(); // Update value
    }

    spider.head_set_to(INIT_ANGLE); // Volver a mirar al frente
    delay(500);

    float dist_down = spider.get_dist_head();

    // Evitamos valores inválidos
    while (dist_down == MAX_DISTANCE) {
      delay(100);
      dist_down = spider.get_dist_head();
    }

    // Si la distancia es lo suficientemente grande, es obstáculo
    if (abs(dist_up - dist_down) > OBSTACLE_THRESHOLD) {
      return true;
    }
    
    return false;
}

void follow_wall(enum walls side) {
  float error;

  // Variable para guardar el momento en que debe terminar la espera
  static unsigned long tiempo_espera = 0;

  // Si el tiempo actual es menor al tiempo de espera programado, salimos de la función
  if (millis() < tiempo_espera) {
    return; 
  }

  if (side == W_RIGHT) {
    error = WALL_DIST_RIGHT - spider.get_dist_right();
  } else {
    error = spider.get_dist_left() - WALL_DIST;
  }

  float derivative = error - last_error;
  float output = (Kp * error) + (Kd * derivative);
  
  last_error = error;

  int turn_time = abs(output); 
  turn_time = constrain(turn_time, 0, 250); 

  if (turn_time > 100) { 
      if (output > 0) {
        spider.turn(LEFT);
        delay(turn_time);
      } else {
        spider.turn(RIGHT);
        delay(turn_time);
      } 
  }
  spider.move(FORWARD);
  tiempo_espera = millis() + (turn_time * 3);
}

void avoid_obstacle(enum walls wall_side) {
  enum direction turn_dir;
  
  if (wall_side == W_LEFT) {
    turn_dir = RIGHT;
  } else {
    turn_dir = LEFT;
  }

  // Gira hasta que ya no ve el obstáculo
  while (spider.get_dist_head() - OBSTACLE_DIST < OBSTACLE_THRESHOLD) { 
    spider.turn(turn_dir);
    check_control();
  }

  delay(1250);

  if (is_obstacle()) {
    spider.stop();
    if (confirm_obstacle()) { // obstaculo
      spider.stop();
      return;
    }
  }
  spider.move(FORWARD);
  delay(1350);

  // Avanzamos un poco para salir
  if (wall_side == W_LEFT) {
    while (spider.get_dist_left() - OBSTACLE_DIST < OBSTACLE_THRESHOLD) {
      spider.move(FORWARD);
      check_control();
    }
  } else {
    while (spider.get_dist_right() - OBSTACLE_DIST < OBSTACLE_THRESHOLD) {
      spider.move(FORWARD);
      check_control();
    }
  }
  delay(250);

  // Invertir giro
  if (turn_dir == LEFT) {
    turn_dir = RIGHT;
  } else {
    turn_dir = LEFT;
  }

  spider.turn(turn_dir);
  delay(1250);

  if (is_obstacle()) {
    spider.stop();
    if (confirm_obstacle()) { // obstaculo
      spider.stop();
      return;
    }
  }

  spider.move(FORWARD);
  delay(1000);

  // Volvemos a seguir pared
  state = FOLLOW_WALL;
}

void turn(enum walls wall_side) {
  static unsigned long tiempo_inicio = 0; 
  enum direction turn_dir;

  // Determinar dirección
  if (wall_side == W_RIGHT) {
    turn_dir = LEFT;
  } else {
    turn_dir = RIGHT;
  }

  // Inicializar el timer si es la primera vez que entramos en el giro
  if (tiempo_inicio == 0) {
    tiempo_inicio = millis();
  }

  // Timer
  if (millis() - tiempo_inicio > 1250) {
    spider.stop();
    state = FOLLOW_WALL;
    tiempo_inicio = 0;
    
  } else {
    spider.turn(turn_dir);
  }
}

void detect_wall() {
  if (spider.get_dist_right() < WALL_DIST + 10) {
    wall_side = W_RIGHT;
    state = FOLLOW_WALL;

  } else if (spider.get_dist_left() < WALL_DIST + 10) {
    wall_side = W_LEFT;
    state = FOLLOW_WALL;

  } else if (mode == CASE_2){
    wall_side = W_LEFT;
    bool wall_detected = false;
    while (spider.get_dist_head() > WALL_DIST) {
      spider.move(FORWARD);

      if (is_obstacle() && !wall_detected) {
        spider.stop();
        if (confirm_obstacle()) { // obstaculo
          spider.stop();
          avoid_obstacle(wall_side);
        } else {
          wall_detected = true;
        }
      }
      check_control();
    }
    state = TURN;
  } else {
    spider.turn(LEFT);
  }
}

// Control
void check_control() {
  // LOGICA MANDO IR
  if (irrecv.decode(&results)) {
    // Filtro para evitar el código 0 o lecturas basura
    if (results.value != 0) { 
        switch (results.value) {
        case POWER_ON: 
          spider.init_all(true); 
          break;
        case POWER_OFF: 
          spider.stop_all(false); 
          break;
        case KEY_UP:
          if(mode == IDLE){
            spider.move(FORWARD);
          }
          break;
        case KEY_LEFT:
          if(mode == IDLE){
            spider.turn(LEFT);
          }
          break;
        case KEY_OK: 
          spider.stop();
          mode = IDLE;
          state = MANUAL;
          break;
        case KEY_RIGHT:
          if(mode == IDLE){
            spider.turn(RIGHT);
          }
          break;
        case KEY_DOWN:
          if(mode == IDLE){
            spider.move(BACKWARD); 
          }
          break;
        case KEY_1:
          mode = CASE_1;
          state = SEARCH_WALL;
          break;
        case KEY_2:
          mode = CASE_2;
          state = SEARCH_WALL;
          break;
        }
    Serial.println(results.value, HEX);
    irrecv.resume();
    }
  }
}


void setup() {
  Serial.begin(9600);

  // Setup remote control
  irrecv.enableIRIn();

  // Setup spider
  spider = Spider();

  spider.init_all(true);
  // Begining state
  state = 1000;
  mode = IDLE;
  wall_side = W_FRONT;
  pinMode(ledPIN , OUTPUT);  //definir pin como salida
}


void loop() {
  // Check remote control orders
  check_control();

  // State machine
  switch(state) {
  case MANUAL:
    break;
  case SEARCH_WALL:
    detect_wall();
    break;
  case AVOIDING:
    avoid_obstacle(wall_side);
    break;
  case FOLLOW_WALL: {

    if (is_obstacle()) {
      if (mode == CASE_2) { 
        spider.stop();
        if (confirm_obstacle()) { // obstaculo
          spider.stop();
          state = AVOIDING;
        } else { // pared
          digitalWrite(ledPIN , HIGH);
          delay(1000);
          digitalWrite(ledPIN , LOW);
          state = TURN;
        }
      }
      break;
    }
    follow_wall(wall_side);
    break;
  }
  case TURN:
    turn(wall_side);
    break;

  default:
    delay(100);
  }
}
