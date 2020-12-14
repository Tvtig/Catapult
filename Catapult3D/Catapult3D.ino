#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor _motorRight(3, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
//AF_DCMotor _motorLeft(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

int TRIGGER_SERVO_PIN = 9;
int ROTATION_SERVO_PIN = 10;
int MOTOR_SPEED = 200;

Servo _rotationServo;
Servo _triggerServo;
int _limitSwitchValue;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  _rotationServo.attach(ROTATION_SERVO_PIN);
  _triggerServo.attach(TRIGGER_SERVO_PIN);
  _rotationServo.write(0);
  _triggerServo.write(0);

  //_motorLeft.setSpeed(MOTOR_SPEED);    
  _motorRight.setSpeed(MOTOR_SPEED);   
  
  _rotationServo.write(90);

  delay(2000);

  doAimRoutine();
  startFiring();
}

void loop() {
  // put your main code here, to run repeatedly:

 _limitSwitchValue = digitalRead(2);
 Serial.println(_limitSwitchValue);
  
  if(Serial.available() > 0){
    int rotationValue = Serial.parseInt();
    
    if(rotationValue){
      Serial.println(rotationValue);
      //_rotationServo.write(rotationValue);  
    }  
  }

  //Once the catapult arm is pulled back far enough the limit switch value will be 1
  if(_limitSwitchValue == 1){      
      runMotors(RELEASE);
      _triggerServo.write(180);
      delay(2000);
      runMotors(BACKWARD);
      delay(400);
      runMotors(RELEASE);
      delay(1000);
      _triggerServo.write(0);
      delay(2000);      

      doAimRoutine();
      startFiring();
      
  }
}

void runMotors(int direction){
 //_motorLeft.run(direction);
 _motorRight.run(direction);
}

void doAimRoutine(){
  int aimIndex = 0;
  
  while(aimIndex < 180){
    _rotationServo.write(aimIndex + 90);
    aimIndex++;
    delay(15);
  }

  aimIndex = 0;

  while(_rotationServo.read() >= 1){
    _rotationServo.write(180 - aimIndex);
    aimIndex++;
    delay(15);
  }

  _rotationServo.write(90);

  delay(1000);
}

void startFiring(){
  runMotors(FORWARD);
}
