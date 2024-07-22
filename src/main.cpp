#include <Arduino.h>
// no MotorC port for this project
void pwm_rgb(int a0, int a1, int a2);
void set_rgb(int rgbarr[]);
int rgbarr[] = {0, 0, 0};
int rgbidx = 0;
HardwareSerial hs = HardwareSerial(PB7, PB6);
int a0 = 0;
int a1 = 0;
int a2 = 0;
int a5 = 0;

void move_ma(int dir, int pwr)
{
  switch (dir)
  {
  case 1:
    digitalWrite(PA9, 0);
    digitalWrite(PA8, 1);
    break;
  case -1:
    digitalWrite(PA8, 0);
    digitalWrite(PA9, 1);
    break;
  case 0:
  default:
    digitalWrite(PA8, 1);
    digitalWrite(PA9, 1);
    break;
  }
}

void move_mb(int dir, int pwr)
{
  switch (dir)
  {
  case 1:
    digitalWrite(PB3, 0);
    digitalWrite(PA15, 1);
    break;
  case -1:
    digitalWrite(PA15, 0);
    digitalWrite(PB3, 1);
    break;
  case 0:
  default:
    digitalWrite(PA15, 1);
    digitalWrite(PB3, 1);
    break;
  }
}

void apwm_ma(int dir, int pwr){
unsigned long ct = millis();

}

void apwm_mb(int dir, int pwr){
unsigned long ct = millis();

}

void setup()
{
  pinMode(PA8, OUTPUT); // MA
  pinMode(PA9, OUTPUT);
  pinMode(PA15, OUTPUT); // MB
  pinMode(PB3, OUTPUT);
  move_ma(0, 0);
  move_mb(0, 0);
  pinMode(PB13, OUTPUT_OPEN_DRAIN);
  pinMode(PB14, OUTPUT_OPEN_DRAIN);
  pinMode(PB15, OUTPUT_OPEN_DRAIN);
  pinMode(PB2, OUTPUT);       // turn on IR leds
  pinMode(PA0, INPUT_ANALOG); // ir x3
  pinMode(PA1, INPUT_ANALOG);
  pinMode(PA2, INPUT_ANALOG);
  pinMode(PA5, INPUT_ANALOG); // SEN1

  digitalWrite(PB2, 1); // on ir led
  pwm_rgb(0xFF, 0xFE, 0xFFFF);
  hs.begin(115200);
  delay(2000);
}

void loop()
{
  // rgbidx++;
  // if(rgbidx>100)rgbidx=0;
  // rgbarr[0]=1;
  // rgbarr[1]=1;
  // rgbarr[2]=1;
  // if(rgbidx%3==1)    rgbarr[0] = 0;
  // if((rgbidx+1)%4==1)rgbarr[1] = 0;
  // if((rgbidx+2)%5==1)rgbarr[2] = 0;
  // set_rgb(rgbarr);
  // delay(30);

  a0 = analogRead(PA0);
  a1 = analogRead(PA1);
  a2 = analogRead(PA2);
  a5 = analogRead(PA5);
  if (a5 > 256)
    a5 = 256;

  hs.printf("%d\t%d\t%d\t%d\r\n", a0, a1, a2, a5);
  pwm_rgb(a5, 0xff, 0xff);
  int a = 0x2F;

}

void set_rgb(int rgbarr[])
{
  digitalWrite(PB13, rgbarr[0]);
  digitalWrite(PB14, rgbarr[1]);
  digitalWrite(PB15, rgbarr[2]);
}

void pwm_rgb(int x, int y, int z)
{
  analogWrite(PB13, x);
  analogWrite(PB14, y);
  analogWrite(PB15, z);
}
