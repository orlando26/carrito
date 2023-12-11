
#include <SoftwareSerial.h>   // librería  SoftwareSerial  
SoftwareSerial BT(3,2);    // pines RX y TX del Arduino conectados al Bluetooth

const int pinPWMA = 6;
const int pinAIN2 = 7;
const int pinAIN1 = 8;
const int pinBIN1 = 9;
const int pinBIN2 = 10;
const int pinPWMB = 11;
const int pinSTBY = 12;

const int speed = 200;    //velocidad de giro

const int pinMotorA[3] = { pinPWMA, pinAIN2, pinAIN1 };
const int pinMotorB[3] = { pinPWMB, pinBIN1, pinBIN2 };

char bt = 0;

enum moveDirection {
  forward,
  backward
};

enum turnDirection {
  clockwise,
  counterClockwise
};

void setup()
{
  BT.begin(9600);       // Inicializar el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializar  el puerto serie  
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
}

void loop()
{
  if(BT.available())  
  {
    bt = BT.read();
    Serial.write(bt);
    switch (bt) {
      case 'F' : 
        enableMotors();
        move(forward, speed);
        break;
      case 'G' :  
        enableMotors();
        move(backward, speed);
        break;
      case 'L' :  
        enableMotors();
        turn(counterClockwise, speed);
        break;
      case 'R' :  
        enableMotors();
        turn(clockwise, speed);
        break;
      case 'S' :  
        fullStop();
        break;
    }

  }
  //enableMotors();

  //fullStop();
}

//Funciones que controlan el vehiculo
void move(int direction, int speed)
{
  if (direction == forward)
  {
    moveMotorForward(pinMotorA, speed);
    moveMotorForward(pinMotorB, speed);
  }
  else
  {
    moveMotorBackward(pinMotorA, speed);
    moveMotorBackward(pinMotorB, speed);
  }
}

void turn(int direction, int speed)
{
  if (direction == forward)
  {
    moveMotorForward(pinMotorA, speed);
    moveMotorBackward(pinMotorB, speed);
  }
  else
  {
    moveMotorBackward(pinMotorA, speed);
    moveMotorForward(pinMotorB, speed);
  }
}

void fullStop()
{
  disableMotors();
  stopMotor(pinMotorA);
  stopMotor(pinMotorB);
}

//Funciones que controlan los motores
void moveMotorForward(const int pinMotor[3], int speed)
{
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);

  analogWrite(pinMotor[0], speed);
}

void moveMotorBackward(const int pinMotor[3], int speed)
{
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);

  analogWrite(pinMotor[0], speed);
}

void stopMotor(const int pinMotor[3])
{
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);

  analogWrite(pinMotor[0], 0);
}

void enableMotors()
{
  digitalWrite(pinSTBY, HIGH);
}

void disableMotors()
{
  digitalWrite(pinSTBY, LOW);
}