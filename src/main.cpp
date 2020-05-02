
#include <Arduino.h>

#include "JoystickLib.h"
#include "OneButton.h"
#include "Servo.h"

#define PIN_X A0
#define PIN_Y A1

Joystick stick(PIN_X, PIN_Y);
Servo servo_x;
Servo servo_y;
OneButton button(A2, true);

int pos_x;
int pos_y;
int pos_x_return = 90;
int pos_y_return = 90;

void singleClick() {
  pos_x = pos_x_return;
  pos_y = pos_y_return;
  servo_x.write(pos_x);
  servo_y.write(pos_y);
}

void doubleClick() {
  pos_x_return = pos_x;
  pos_y_return = pos_y;
}

void longPressed() {
  pos_x_return = 90;
  pos_y_return = 90;
  singleClick();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  stick.calibrate();

  servo_x.attach(6);
  servo_y.attach(5);

  singleClick();

  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
  button.attachLongPressStop(longPressed);
  Serial.println(F("Ready."));
}

void printPos() {
  Serial.print(pos_x);
  Serial.print(" ");
  Serial.println(pos_y);
}

void doDelay(int position) {
  if (position < 0) {
    position = -position;
  }
  delay((100 - position) * 2);
}

void moveLeft() {
  if (pos_x > 0) {
    pos_x--;
    servo_x.write(pos_x);
    doDelay(stick.getX());
  }
}

void moveRight() {
  if (pos_x < 180) {
    pos_x++;
    servo_x.write(pos_x);
    doDelay(stick.getX());
  }
}

void moveUp() {
  if (pos_y > 0) {
    pos_y--;
    servo_y.write(pos_y);
    doDelay(stick.getY());
  }
}

void moveDown() {
  if (pos_y < 180) {
    pos_y++;
    servo_y.write(pos_y);
    doDelay(stick.getY());
  }
}

void loop() {
  stick.loop();
  button.tick();

  // delay(5);

  if (stick.isUp()) {
    Serial.print(F("Up "));
    moveUp();
    printPos();
  }

  if (stick.isDown()) {
    Serial.print(F("Down "));
    moveDown();
    printPos();
  }

  if (stick.isRight()) {
    Serial.print(F("Right "));
    moveRight();
    printPos();
  }

  if (stick.isLeft()) {
    Serial.print(F("Left "));
    moveLeft();
    printPos();
  }
  if (stick.isLeftUp()) {
    Serial.print(F("Left Up"));
    moveLeft();
    moveUp();
    printPos();
  }

  if (stick.isLeftDown()) {
    Serial.print(F("Left Down "));
    moveLeft();
    moveDown();
    printPos();
  }

  if (stick.isRightUp()) {
    Serial.print(F("Right Up "));
    moveRight();
    moveUp();
    printPos();
  }

  if (stick.isRightDown()) {
    Serial.print(F("Right Down "));
    moveRight();
    moveDown();
    printPos();
  }
}
