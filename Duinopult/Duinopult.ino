#include "Servo.h";

int POT_PIN = 1;
int AIM_SERVO_PIN = 3;
int TENSION_SERVO_PIN = 4;
int TRIGGER_SERVO_PIN = 5;
int LAUNCH_BUTTON_PIN = 10;

double POT_SCALE_FACTOR = 1024/180;

Servo _aimServo;
Servo _tensionServo;
Servo _triggerServo;
bool _buttonState = false;
bool _isFiring = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  _aimServo.attach(AIM_SERVO_PIN);
  _tensionServo.attach(TENSION_SERVO_PIN);
  _triggerServo.attach(TRIGGER_SERVO_PIN);  
  _tensionServo.write(180);
  delay(500);
  _triggerServo.write(180);  
  _aimServo.write(0);
  pinMode(LAUNCH_BUTTON_PIN, INPUT);
  //doFingerMode();
}

void loop() {
    if(!_isFiring){
      _buttonState = digitalRead(LAUNCH_BUTTON_PIN);
      _isFiring = _buttonState;

      if(_isFiring){
        doLaunch();
      }else{
      int potValue = analogRead(POT_PIN);
      //Serial.println(potValue);
      int servoAngle = potValue / POT_SCALE_FACTOR;
      _aimServo.write(servoAngle);
      //Serial.println(servoAngle);  
    }
        
    delay(20);  
  }
  
}

void doLaunch(){  
  _tensionServo.write(0);
  delay(1000);
  _triggerServo.write(0);
  delay(1000);
  _tensionServo.write(180);
  delay(1000);
  _triggerServo.write(180);
  delay(1000);
  _isFiring = false;  
}

void doFingerMode(){
  _triggerServo.write(0);
  _tensionServo.write(180);
  
  for(int i = 180; i >= 0; i--){
    _tensionServo.write(i);
    delay(50);
  }
}
