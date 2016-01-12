#include <Servo.h>
#include <Keypad.h>
int but=0;
Servo locker;
int state=0;  //Variable indicating the status of the lock
int k[9];     // Declaring an array
int pos=0;   //servo close position
int opos=180;//Position to open servo
int i=0;     //Position of variable in key
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

void setup(){
  attachInterrupt(but,open,RISING); // declaring an interrupt
  locker.attach(10);                //attahing a servo
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop(){
  char key = keypad.getKey(); //Obtainig the valuse from input

  if (key) {
    Serial.println(key);    //Printing the key pressed in serial monitor
    
  }
}

//take care of some special events
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      switch (key){
        case '#':   // This is our enter key verifying all the values and clearing them later
        i=0; 
        if (k[0]=='1' && k[1]=='2' && k[2]=='3' && k[3]=='4'){
        open();
        i=0;
        k[0]=k[1]=k[2]=k[3]=k[4]=0;
        };
      break;
     case '*':       //*is like a backspace removing the previously pressed key
          i--;
        break;
     default:       //This part enters inputs into our k array
           k[i]=key;
           i++;
           if(i>5){
            i=0;
           }
      }
  }
}
void open(){              //Function to open a servo if it is locked and vice versa
  if(state==0){
    locker.write(pos);
    state=1;
  }
  else if(state==1){
    locker.write(opos);
    state=0;
  }
}
