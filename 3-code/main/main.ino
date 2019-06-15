#include <stdlib.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

//pin 
int sensor = A5 ;
int peopel_pin = 2; 
int fan_pin = 3;

float temprature;
float tmp; 
bool has_people = false ; 
unsigned long last_time = 0 ;

void setup()
{
  //pinMode(peopel_pin, INPUT); 
  attachInterrupt(0,toggle_people,RISING);
  pinMode(fan_pin,OUTPUT);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  
  lcd.home();
  lcd.clear();

  lcd.print("init complete");
  delay(2000);
  lcd.clear();
  //lcd.clear();
}

void loop()
{
  tmp = analogRead(sensor) ; 
  temprature = tmp/2;
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("temp:");
  lcd.print(temprature);

  lcd.setCursor(0,1);
  if(has_people)
  {
    lcd.print("has people"); 
    if(temprature > 30)
    {
      analogWrite(fan_pin,255);
    }
    else
    {
      analogWrite(fan_pin,180);
    }
  }
  else 
  {
    lcd.print("no people");

    analogWrite(fan_pin,0);
  }

  delay(1000);
}

void toggle_people()
{
  if(millis()-last_time> 500)
  {
    has_people = !has_people ; 
  }

  last_time = millis();
}