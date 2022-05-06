#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//#include <AFMotor.h>
#include <AFMotor_routed.h>
#include <Servo.h> 

USB Usb;
BTD Btd(&Usb);
//refer to ps3bt example on instructions on how to set this.
PS3BT PS3(&Btd, 0x00, 0x1B, 0x10, 0x00, 0x2A, 0xEC);

AF_DCMotor motor1(1,MOTOR12_1KHZ);
AF_DCMotor motor2(2,MOTOR12_64KHZ);

AF_DCMotor motor3(3,MOTOR34_1KHZ);
AF_DCMotor motor4(4,MOTOR34_64KHZ);

Servo servo1;
Servo servo2;

float hatToServoRatio = (float)180 / 256; //hat is between 0 / 255, so we do simple rule of three
bool printLogs = false;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  motor1.setSpeed(255);
  motor2.setSpeed(255);
  // motor3.setSpeed(200);
  // motor4.setSpeed(200);
  servo1.attach(A0); 
  servo2.attach(A1);
}

void loop()
{
	btloop();
}

void btloop()
{
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected)
  {
    updateServo(LeftHatX, servo1);
    updateServo(RightHatX, servo2);

    updateMotorFromHat(LeftHatY, motor3);
    updateMotorFromHat(RightHatY, motor4);
    updateMotorFromButtons(UP, DOWN, motor1);
    updateMotorFromButtons(LEFT, RIGHT, motor2);
    
    if (PS3.getButtonClick(CROSS))
    {
      printLogs = !printLogs;
      if (printLogs)
        Serial.println("logs enabled");
      else
        Serial.println("logs disabled");
    }
    if (printLogs)
    {
      printButtonsAndHats();
    }
  }
}

bool isHatCentered(AnalogHatEnum hat)
{
  return isHatCentered(PS3.getAnalogHat(hat));
}

bool isHatCentered(uint8_t hatValue)
{
  return hatValue > 117 && hatValue < 137;
}

void updateServo(AnalogHatEnum hat, Servo servo)
{
  int angle = hatToServo(PS3.getAnalogHat(hat));
  servo.write(angle);
}

int hatToServo(uint8_t hatValue)
{
  int angle = hatValue * hatToServoRatio;
  // Serial.print("hat value ");
  // Serial.print(hatValue);
  // Serial.print(" to servo is angle ");
  // Serial.println(angle);
  return angle;
}

void updateMotorFromHat(AnalogHatEnum hat, AF_DCMotor motor)
{
  uint8_t hatValue = PS3.getAnalogHat(hat);
  uint8_t direction;
  uint8_t speed;
  hatToMotor(hatValue, &speed, &direction);

  motor.setSpeed(speed);
  motor.run(direction);
}
void updateMotorFromButtons(ButtonEnum firstButton, ButtonEnum secondButton, AF_DCMotor motor)
{
  bool firstButtonPressed = PS3.getButtonPress(firstButton);
  bool secondButtonPressed = PS3.getButtonPress(secondButton);
  
  if (firstButtonPressed)
  {
    motor.run(FORWARD);
  }
  else if (secondButtonPressed)
  {
    motor.run(BACKWARD);
  }
  else
  {
    motor.run(RELEASE);
  }
}

void hatToMotor(uint8_t hatValue, uint8_t *speed, uint8_t *direction)
{
  //hat value goes from 0 to 255. speed does as well, so we mutiply by 2, subtract half and then use positive/negative to figure out direction.
  int converted = hatValue * 2 - 255;

  if (!isHatCentered(hatValue))
  {
    if (converted > 0)
      *direction = FORWARD;
    else
      *direction = BACKWARD;
  }
  else
    *direction = RELEASE;

  *speed = abs(converted);
}

void printButtonsAndHats()
{
  if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117)
  {
    Serial.print(F("\r\nLeftHatX: "));
    Serial.print(PS3.getAnalogHat(LeftHatX));
    Serial.print(F("\tLeftHatY: "));
    Serial.print(PS3.getAnalogHat(LeftHatY));
    if (PS3.PS3Connected)
    { // The Navigation controller only have one joystick
      Serial.print(F("\tRightHatX: "));
      Serial.print(PS3.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(PS3.getAnalogHat(RightHatY));
    }
  }

  // Analog button values can be read from almost all buttons
  if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2))
  {
    Serial.print(F("\r\nL2: "));
    Serial.print(PS3.getAnalogButton(L2));
    if (PS3.PS3Connected)
    {
      Serial.print(F("\tR2: "));
      Serial.print(PS3.getAnalogButton(R2));
    }
  }

  if (PS3.getButtonClick(PS))
  {
    Serial.print(F("\r\nPS"));
    PS3.disconnect();
  }
  else
  {
    if (PS3.getButtonClick(TRIANGLE))
    {
      Serial.print(F("\r\nTriangle"));
    }
    if (PS3.getButtonClick(CIRCLE))
    {
      Serial.print(F("\r\nCircle"));
      PS3.setRumbleOn(RumbleHigh);
    }
    if (PS3.getButtonClick(CROSS))
      Serial.print(F("\r\nCross"));
    if (PS3.getButtonClick(SQUARE))
      Serial.print(F("\r\nSquare"));

    if (PS3.getButtonClick(UP))
    {
      Serial.print(F("\r\nUp"));
      if (PS3.PS3Connected)
      {
        PS3.setLedOff();
        PS3.setLedOn(LED4);
      }
    }
    if (PS3.getButtonClick(RIGHT))
    {
      Serial.print(F("\r\nRight"));
      if (PS3.PS3Connected)
      {
        PS3.setLedOff();
        PS3.setLedOn(LED1);
      }
    }
    if (PS3.getButtonClick(DOWN))
    {
      Serial.print(F("\r\nDown"));
      if (PS3.PS3Connected)
      {
        PS3.setLedOff();
        PS3.setLedOn(LED2);
      }
    }
    if (PS3.getButtonClick(LEFT))
    {
      Serial.print(F("\r\nLeft"));
      if (PS3.PS3Connected)
      {
        PS3.setLedOff();
        PS3.setLedOn(LED3);
      }
    }

    if (PS3.getButtonClick(L1))
      Serial.print(F("\r\nL1"));
    if (PS3.getButtonClick(L3))
      Serial.print(F("\r\nL3"));
    if (PS3.getButtonClick(R1))
      Serial.print(F("\r\nR1"));
    if (PS3.getButtonClick(R3))
      Serial.print(F("\r\nR3"));

    if (PS3.getButtonClick(SELECT))
    {
      Serial.print(F("\r\nSelect - "));
      PS3.printStatusString();
    }
    if (PS3.getButtonClick(START))
    {
      Serial.print(F("\r\nStart"));
    }
  }
}
