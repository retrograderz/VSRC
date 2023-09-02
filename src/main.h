#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <EEB.h>

// OLD - 2022
#define PS2_DAT 12 // MISO
#define PS2_CMD 13 // MOSI
#define PS2_SEL 15 // SS
#define PS2_CLK 14 // SLK

// NEW - 2023
// #define PS2_DAT 25 //MISO  
// #define PS2_CMD 0 //MOSI  
// #define PS2_SEL 15 //SS    
// #define PS2_CLK 14 //SLK  

// MOTOR NO.
#define LEFT_MOTOR 1
#define RIGHT_MOTOR 2

// BLUETOOTH RECEIVED DATA
#define BTforward 'F'
#define BTback    'B'
#define BTleft    'L'
#define BTright   'R'
#define BTforwl   'G'
#define BTforwr   'I'
#define BTbackl   'H'
#define BTbackr   'J'
#define BTstop    'S'

// PWM VALUES  
#define MAX_PWM 1100
// #define MIN_PWM 0

int16_t pwm_left, pwm_right, applied_pwm = 0;
bool running = 0;
bool dir_left, dir_right;

void forward();
void backward();
void left();
void right();
void idle();

#endif