#include <Servo.h>
int but=0;
Servo locker;
int state=0;
int pos=0;
int opos=180;

void setup(){
  attachInterrupt(but,open,RISING);
  locker.attach(10);
}

void loop(){
    
}

//take care of some special events
void open(){
  if(state==0){
    locker.write(pos);
    state=1;
  }
  else if(state==1){
    locker.write(opos);
    state=0;
  }
}
