#define button_avancar1 14
#define button_avancar2 13
#define button_aceitar 1
#define button_top 17
#define button_bottom 2
#define button_right 39
#define button_left 21
#define motor_servo 4
#define led_vermelho
#define led_verde 
#define pinoTrigger 5
#define echo 18
#define SCLK 11
#define pinoMISO 12
#define pinoMOSI 10
#define DISPCS 9
#define DC 16
#define RESET 15
#include <Arduino.h>

void setup() {
  
  pinMode(button_aceitar,INPUT);
  pinMode(button_avancar1,INPUT);
  pinMode(button_avancar2,INPUT);
  pinMode(button_top,INPUT);
  pinMode(button_bottom,INPUT);
  pinMode(button_left,INPUT);
  pinMode(button_right,INPUT);
  pinMode(motor_servo,OUTPUT);
  ledcAttach(4, 50, 14);



}

void loop() {
    ledcWrite(4, 1229);
}
