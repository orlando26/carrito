#include <ps5Controller.h>

#define ENA_PIN 14         // The ESP32 pin GPIO14 connected to the ENA pin L298N
#define IN1_PIN 27         // The ESP32 pin GPIO27 connected to the IN1 pin L298N
#define IN2_PIN 26         // The ESP32 pin GPIO26 connected to the IN2 pin L298N
#define IN3_PIN 25         // The ESP32 pin GPIO25 connected to the IN3 pin L298N
#define IN4_PIN 33         // The ESP32 pin GPIO33 connected to the IN4 pin L298N
#define ENB_PIN 32         // The ESP32 pin GPIO32 connected to the ENB pin L298N

void setup() {
  Serial.begin(921600);
  ps5.begin("24:A6:FA:FA:57:FB"); //replace with MAC address of your controller
  Serial.println("PS5 Controller Ready.");
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  digitalWrite(ENA_PIN, HIGH);  // set full speed
  digitalWrite(ENB_PIN, HIGH);  // set full speed
}

void loop() {
//  while (ps5.isConnected() == false) { // commented out as ps5 controller seems to connect quicker when microcontroller is doing nothing
//    Serial.println("PS5 controller not found");
//    delay(300);
//  }

  while (ps5.isConnected() == true) {

    if (!ps5.Right() && !ps5.Down() && !ps5.Up() && !ps5.Left()) {
      CAR_stop();
    } else {
      if (ps5.Right()) CAR_turnRight();
      if (ps5.Down()) CAR_moveBackward();
      if (ps5.Up()) CAR_moveForward();
      if (ps5.Left()) CAR_turnLeft();
    }

    //CAR_stop();
  }
}

void CAR_moveForward() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moveBackward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnLeft() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnRight() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}