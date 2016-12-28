#include <QTRSensors.h>
#include <DRV8835MotorShield.h>

//Set some constants
#define S 9600
#define LED_PIN 13
#define END 25000
#define MAX_SPEED 100
#define BASE_SPEED 50
#define Kp .01
#define Kd .2

//Global IO variables
DRV8835MotorShield motors;
QTRSensorsRC qtr((unsigned char[]) {
  2, 3, 4, 5, 11, 12
}, 6) ;
unsigned int sensors[6];

//Global data variables
unsigned int position;
int lastError = 0;
boolean on = true;

void setup() {
  Serial.begin(S);
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < 100; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(20);
    qtr.calibrate();
    digitalWrite(LED_PIN, LOW);
    delay(20);
  }
  digitalWrite(LED_PIN, LOW);
  delay(2000);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  motors.setM1Speed(BASE_SPEED);
  motors.setM2Speed(BASE_SPEED);
}

void loop() {
  unsigned long time = millis();
  if (time >= END ) {
    if (on) {
      stop();
      on = false;
      Serial.print("Stop");
    }
  } else {
    if (on) {
      update();
    }
  }
}

void stop() {
  motors.setM1Speed(0);
  motors.setM2Speed(0);
}

void update() {
  position = qtr.readLine(sensors);
  Serial.print("Position: ");
  Serial.println(position);
  int error = position - 2500;
  Serial.print("Error: ");
  Serial.println(error);
  int motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;
  Serial.print("Calculated motor speed: ");
  Serial.println(motorSpeed);
  int m1Speed = BASE_SPEED + motorSpeed;
  int m2Speed = BASE_SPEED - motorSpeed;
  if (m1Speed < 0) {
    m1Speed = 0;
  }
  if (m2Speed < 0) {
    m2Speed = 0;
  }
  if (m1Speed > MAX_SPEED) {
    m1Speed = MAX_SPEED;
  }
  if (m2Speed > MAX_SPEED) {
    m2Speed = MAX_SPEED;
  }
  Serial.print("M1 speed: ");
  Serial.println(m1Speed);
  Serial.print("M2 speed: ");
  Serial.println(m2Speed);
  motors.setM1Speed(m1Speed);
  motors.setM2Speed(m2Speed);
  Serial.println("End update");
}

