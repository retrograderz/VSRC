#include "main.h"

BluetoothSerial SerialBT;
DCMotor VSRC_Motor;
Servo_Motor VSRC_Servo;

TimerHandle_t xTimers[4];
unsigned long count = 0;
char cmd;

void timerCallBack(TimerHandle_t xTimer){
    configASSERT(xTimer);
    int ulCount = (uint32_t) pvTimerGetTimerID(xTimer);

    // read data thru bluetooth
    if(ulCount==0){
      if (SerialBT.available()) {
        cmd = SerialBT.read();
        // Serial.print(cmd);
        // Serial.print(" ");
        }
      
    }

    //timer 2 acceleration pwm for motors
    if(ulCount == 1){
        if(running == 1){
            if(applied_pwm < MAX_PWM){
                applied_pwm += 200;
            }
            else{
                applied_pwm = MAX_PWM;
            }
        }
        else{
            applied_pwm = 0;
        }
    }
}

void setup() {
  Serial.begin(9600); Serial.println("Successfully initiated.");
  SerialBT.begin("VSRC23");
  VSRC_Motor.Init();
  // VSRC_Servo.Init(); 

  // Create Timer
  xTimers[ 0 ] = xTimerCreate("Timer BLE",pdMS_TO_TICKS(50),pdTRUE,( void * ) 0, timerCallBack);
  xTimerStart(xTimers[0],0);

  xTimers[ 1 ] = xTimerCreate("Timer acceleration",pdMS_TO_TICKS(500),pdTRUE,( void * ) 1, timerCallBack);
  xTimerStart(xTimers[1],0);
}

void loop() {
  switch (cmd) {
    case BTforward: forward();
      Serial.print("moving forward (left, right): "); Serial.print(pwm_left, DEC); Serial.print(","); Serial.println(pwm_right, DEC);
      delay(50);
      break;
    case BTback: backward();
      Serial.print("moving backward (left, right): "); Serial.print(pwm_left, DEC); Serial.print(","); Serial.println(pwm_right, DEC);
      delay(50);
      break;
    case BTleft: left();
      Serial.print("turning left (-left, right): "); Serial.print(pwm_left, DEC); Serial.print(","); Serial.println(pwm_right, DEC);
      delay(50);
      break;
    case BTright: right();
      Serial.print("turning right (left, -right): "); Serial.print(pwm_left, DEC); Serial.print(","); Serial.println(pwm_right, DEC);
      delay(50);
      break;
    default: case BTstop: idle();
      Serial.println("idling..");
      delay(50);
      break;
  }
  
  VSRC_Motor.Run(RIGHT_MOTOR, pwm_right, dir_right);
  VSRC_Motor.Run(LEFT_MOTOR, pwm_left, dir_left);
}

void forward() {
    running = 1;
    pwm_left  = (int16_t) applied_pwm;
    pwm_right = (int16_t) applied_pwm;
    dir_left  = 0; // cw
    dir_right = 0; // cw
}

void backward() {
    running = 1;
    pwm_left  = (int16_t) applied_pwm;
    pwm_right = (int16_t) applied_pwm;
    dir_left  = 1; // ccw
    dir_right = 1; // ccw
}

void left() {
    running = 1;
    pwm_left  = (int16_t) applied_pwm;
    pwm_right = (int16_t) applied_pwm;
    dir_left  = 1; // ccw
    dir_right = 0; // cw
}

void right() {
    running = 1;
    pwm_left  = (int16_t) applied_pwm;
    pwm_right = (int16_t) applied_pwm;
    dir_left  = 0; // cw
    dir_right = 1; // ccw
}

void idle() {
    running = 0;
    pwm_left = (int16_t) 0;
    pwm_right = (int16_t) 0;
    dir_left = 0;
    dir_right = 0;
}