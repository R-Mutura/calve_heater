#include <Arduino.h>
#include <OneButton.h>
#include "LowPower.h"

//initialize the 2 buttons
#define TEMP_LVL_BTN 3  //PD3
   OneButton btn = OneButton(
        TEMP_LVL_BTN,  // Input pin for the button
        true,        // Button is active LOW
        true         // Enable internal pull-up resistor 
      );
 #define ON_OFF_BTN 2  //PD2
   OneButton btn_A = OneButton(
        ON_OFF_BTN,  // Input pin for the button
        true,        // Button is active LOW
        true         // Enable internal pull-up resistor 
      );
 //temperature constants
 const int SensorValueLow = 463; 
const int SensorValueDiff = 36; // differance between high and low sensor value
const int TempValueDiff = 42; // differance between high and low Temp value
const int TempValueLow = 9;

 //defined constants
 int sleep_flag=0;
 int temp_level=0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_value = 0;
long currentMillis=0;
 int heater=5;
 int rtd   =A0;
 int red   =8;
 int green =9;
 int blue =10;
 //PID variables
//PID constants
int kp = 90;   int ki = 30;   int kd = 80;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;

long my_Delay= 50;//50ms refresh rate
int toggle_delay=1000;
long current_toggle=0;
void setup() {
  // put your setup code here, to run once:
  //initialize button parameters
   btn.setDebounceTicks(30);//deboumce time
   btn.setClickTicks(250);//click period to register double press
   btn. setPressTicks(800);//period to register long press
   //button press handles
   btn.attachClick(handleClick);
   
   btn_A.attachLongPressStart(handleLongpress);

    //handle input/output setup
   pinMode(heater, OUTPUT);
   pinMode(red, OUTPUT);
   pinMode(green, OUTPUT);
   pinMode(blue, OUTPUT);
   pinMode(rtd, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(sleep_flag==1){
    attachInterrupt(1, wakeUp, LOW);//attach interrupt pin 1 of the atmeaga
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    }
    
   detachInterrupt(0);
   btn.tick();
     
   //get temperature level
   float temperature=set_temperature(temp_level);//set temperature
   float temperature_read =read_rtd();
   if(millis()-currentMillis>= my_Delay){
   temp_control(temperature,temperature_read);
   }
  //monitor battery level
  int bat_level = analogRead(A1);
  if(bat_level<543){
    //toggle the red led on off every cycle to alert the user
    if(millis()-current_toggle>= toggle_delay){
      digitalWrite(red, !digitalRead(red));
      }
    }
}

void handleClick(){
  if(temp_level<3){
    temp_level++;
    }
    else{
      temp_level=0;
      }
  }
  
void wakeUp()
{
  sleep_flag=0;
    // Just a handler for the pin interrupt.
}
void handleLongpress(){
  sleep_flag=1;
  }  
  int set_temperature(int level){
    if(level==0){
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      return 40; //return that the temperature is 40 degrees
      }
    else if(level==1){
      digitalWrite(blue, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      return 44;
      }
     else{
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
      return 48;
      }
    } 
 void temp_control(float temperature, float temperature_actual){
    PID_error = temperature - (temperature_actual + 3);
    PID_p = 0.01*kp * PID_error;
  //Calculate the I value in a range on +-3
  PID_i = 0.01*PID_i + (ki * PID_error);
   timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = 0.01*kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)  
  {    PID_value = 255;  }
  //Now we can write the PWM signal to the mosfet on digital heater pin 
  //Since we activate the MOSFET with a 1 to the gate, we write PID value directly
  analogWrite(heater,PID_value);
  previous_error = PID_error;     //Remember to store the previous error for next loop.
    currentMillis = millis();//to be used to set refresh rate of the loop
    }
    
float read_rtd(){
  int sensorValue = analogRead(rtd);
  int Temp = sensorValue-SensorValueLow;
  Temp = Temp/SensorValueDiff;
  Temp = Temp*TempValueDiff;
  Temp = Temp+TempValueLow; 
  return Temp;   
      }
