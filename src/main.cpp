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
#define PWM_MANUAL 6000
void move_ma(int dir)
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
    digitalWrite(PA8, 0);
    digitalWrite(PA9, 0);
  case 3:
  default:
    digitalWrite(PA8, 1);
    digitalWrite(PA9, 1);
    break;
  }
}

void move_mb(int dir)
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
    digitalWrite(PA15, 0);
    digitalWrite(PB3, 0);
  case 3:
  default:
    digitalWrite(PA15, 1);
    digitalWrite(PB3, 1);
    break;
  }
}

void apwm_ma(int dir, int pwr){
  if(pwr>PWM_MANUAL)return;
  long at = micros();
  while ((micros() - at) < pwr) move_ma(dir);
  move_ma(0);
  delayMicroseconds(PWM_MANUAL-pwr);
}
void apwm_mb(int dir, int pwr){
  if(pwr>PWM_MANUAL)return;
  long at = micros();
  while ((micros() - at) < pwr) move_mb(dir);
  move_mb(0);
  delayMicroseconds(PWM_MANUAL-pwr);
}

void setup()
{
  
  pinMode(PA8, OUTPUT); // MA
  pinMode(PA9, OUTPUT);
  pinMode(PA15, OUTPUT); // MB
  pinMode(PB3, OUTPUT);
  move_ma(0);
  move_mb(0);
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
  delay(100);
}

void loop()
{
  int step = 100;
  for(int i=0;i<PWM_MANUAL;i+=step){
    apwm_ma(1,i);
    apwm_mb(1,i);
  }
  for(int i=PWM_MANUAL;i>0;i-=step){
    apwm_ma(1,i);
    apwm_mb(1,i);
  }
  for(int i=0;i<PWM_MANUAL;i+=step){
    apwm_ma(-1,i);
    apwm_mb(-1,i);
  }
  for(int i=PWM_MANUAL;i>0;i-=step){
    apwm_ma(-1,i);
    apwm_mb(-1,i);
  }
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

  // a0 = analogRead(PA0);
  // a1 = analogRead(PA1);
  // a2 = analogRead(PA2);
  // a5 = analogRead(PA5);

  // hs.printf("%d\t%d\t%d\t%d\r\n", a0, a1, a2, a5);
  // pwm_rgb(a5, 0xff, 0xff);
  
  // int prange = 1024;
  // for (int i = 0; i < prange; i++)
  // {
  //    move_ma(1);
  //    move_mb(1);
  //    delayMicroseconds(prange-i);
  //    move_ma(0);
  //    move_mb(0);
  //    delayMicroseconds(i);
  // }

  // for (int i = 255; i > 0; i--)
  // {
  //    move_ma(1);
  //    move_mb(1);
  //   delay(5);
  // }
  // for (int i = 0; i < 255; i++)
  // {
  //   // digitalWrite(PA15,0);
  //   // analogWrite(PB3, i);
  //   digitalWrite(PA_8,0);
  //   analogWrite(PA_9, i);
  //   delay(10);
  // }
  // for (int i = 0; i < 254; i++){
  //     pwm_rgb(0xff,i,0xff);
  //     delay(1);
  // } 
  
  

  // This worked with direction
  //  move_ma(1);
  //  move_mb(-1);
  //  delay(1000);
  //  move_ma(0);
  //  move_mb(0);
  //  delay(1000);
  //  move_ma(-1);
  //  move_mb(1);
  //  delay(1000);
  //  move_mb(0);
  //  move_ma(0);
  //  delay(1000);

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
