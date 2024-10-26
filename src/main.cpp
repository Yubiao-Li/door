#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1, servo2;
int state = false;
int maxUs = 2500;
int minUs = 500;
int servo1pin = 14;
int servo2pin = 12;
int soundPin = 35;

void PinEvent()
{
  state = true;
}

void openDoor()
{
  if (state == true)
  {
    servo1.write(0);
    delay(1000);
    servo2.write(180);
    delay(500);
    servo2.write(0);
    delay(1000);
    servo1.write(90);
    delay(1000);
    state = false;
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(soundPin, INPUT);
  attachInterrupt(0, PinEvent, FALLING);

  ESP32PWM::allocateTimer(1);
  servo1.setPeriodHertz(50);
  servo2.setPeriodHertz(50);

  servo1.attach(servo1pin, minUs, maxUs);
  servo2.attach(servo2pin, minUs, maxUs);
}

void loop()
{
  Serial.println(digitalRead(soundPin));
  if (digitalRead(soundPin) == 0) {
    state = true;
  }
  openDoor();
  delay(100);
}