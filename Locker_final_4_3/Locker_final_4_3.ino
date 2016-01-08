#include <Servo.h>
#include <Keypad.h>
int but=0;
Servo locker;
int state=0;
int k[9];
int pos=0;
int opos=180;
int i=0;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
        };
byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

boolean blink = false;

void setup(){
  attachInterrupt(but,open,RISING);
  locker.attach(10);
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){
        case '#':
        i=0; 
        if (k[0]=='1' && k[1]=='2' && k[2]=='3' && k[3]=='4'){
        open();
        i=0;
        k[0]=k[1]=k[2]=k[3]=k[4]=0;
        };
      break;
     case '*': 
          i--;
        break;
     default:
           k[i]=key;
           i++;
           if(i>5){
            i=0;
           }
      }
  }
}
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
