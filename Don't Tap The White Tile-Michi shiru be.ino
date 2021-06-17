#define c4 554
#define e4 659
#define a3 440
#define b3 494
#define g4 831
#define a4 880

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int melody[]={a3,a3,a3,b3,a3,b3,c4,e4,c4,b3,a3,a3,
              a3,a3,a3,b3,a3,b3,a3,a4,g4,
              e4,c4,b3,b3,c4,b3,a3,b3,a3
             };
int duration[]={2,5,5,2,4,4,1,2,2,1,4,1,
                2,5,5,2,4,4,2,2,1,
                4,3,2,5,4,2,5,4
               };

int thisNote = -1,noteDuration = 0;
long previousTime = 0,
     presentTime = 0,
     pauseBetweenNotes = 0;

bool ButtonState_c4=0;
bool ButtonState_e4=0;
bool ButtonState_a3=0;
bool ButtonState_b3=0;
bool ButtonState_g4=0;
bool ButtonState_a4=0;
bool BUTTON_State_start=0;
bool flag=1;

const int BUTTON_PIN_a3=2;
const int BUTTON_PIN_b3=3;
const int BUTTON_PIN_c4=4;
const int BUTTON_PIN_e4=5;
const int BUTTON_PIN_g4=6;
const int BUTTON_PIN_a4=7;
const int BUTTON_PIN_start=10;

int ButtonState_restart=0;


void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(BUTTON_PIN_a3,INPUT_PULLUP);
  pinMode(BUTTON_PIN_b3,INPUT_PULLUP);
  pinMode(BUTTON_PIN_c4,INPUT_PULLUP);
  pinMode(BUTTON_PIN_e4,INPUT_PULLUP);
  pinMode(BUTTON_PIN_g4,INPUT_PULLUP);
  pinMode(BUTTON_PIN_a4,INPUT_PULLUP);
  pinMode(BUTTON_PIN_start,INPUT_PULLUP);
  flag=0;
}


byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描

byte row1DataMatrix[30] = {
   B10000000,
   B01000000,
   B10000000,
   B01000000,
   B00100000,
   B01000000,
   B01000000,
   B00100000,
   B00010000,
   B00001000,
   B00000100,
   B10000000,
   B01000000,
   B10000000,
   B01000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B01000000,
   B00100000,
   B00010000,
   B00100000,
   B01000000,
   B10000000,
   B01000000,
   B10000000,
   B10000000,
   B10000000
}; //圖案5
  
 byte row6DataMatrix[8]={ 
   B00100000,
   B01000000,
   B10000000,
   B01000000,
   B10000000,
   B10000000,
   B10000000,
   B00000000
}; 
 byte row7DataMatrix[8]={ 
   B01000010,
   B00100100,
   B00011000,
   B00011000,
   B00100100,
   B01000010,
   B10000001,
   B00000000
}; 


int j=22;

void playstart(){
  for(int w=7;w>0;w--){
  row6DataMatrix[w]=row6DataMatrix[w-1];}
  row6DataMatrix[0]=row1DataMatrix[j];
  j--;
}

void cross(){
  for(int m=0;m<=10;m++){
    for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin, MSBFIRST, colDataMatrix[i]);
   	shiftOut(dataPin,clockPin, MSBFIRST, row7DataMatrix[i]);
   	digitalWrite(latchPin,HIGH);
    delay(1); 
    }
  }
}

byte previous_buttonState=1,present_buttonState=1;

void loop() {
  
  BUTTON_State_start=digitalRead(BUTTON_PIN_start);
  if(BUTTON_State_start==LOW){
  flag=1;
  }
  
  if(flag==1){  
  ButtonState_c4=digitalRead(BUTTON_PIN_c4);
  ButtonState_e4=digitalRead(BUTTON_PIN_e4);
  ButtonState_a3=digitalRead(BUTTON_PIN_a3);
  ButtonState_b3=digitalRead(BUTTON_PIN_b3);
  ButtonState_g4=digitalRead(BUTTON_PIN_g4);
  ButtonState_a4=digitalRead(BUTTON_PIN_a4);
  
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin, MSBFIRST, colDataMatrix[i]);
   	shiftOut(dataPin,clockPin, MSBFIRST, row6DataMatrix[i]);
   	digitalWrite(latchPin,HIGH);
    delay(1); 
  }
   	 
  if (j==-1)j=29;
  
  if(ButtonState_a3==LOW){
    if(row6DataMatrix[6]==128){
      playstart();
      tone(9,a3);
      delay(100);
      noTone(9);}
    else{flag=0;
        cross();}
  } 
  else if(ButtonState_b3==LOW){
    if(row6DataMatrix[6]==64){
    playstart();
    tone(9,b3);
    delay(100);
      noTone(9);}
    else{flag=0;
        cross();}
  }
  else if(ButtonState_c4==LOW){
    if(row6DataMatrix[6]==32){
    playstart();
    tone(9,c4);
    delay(100);
    noTone(9); }
    else{flag=0;
    cross();}
  }
  else if(ButtonState_e4==LOW){
    if(row6DataMatrix[6]==16){
    playstart();
    tone(9,e4);
    delay(100);
      noTone(9);}
    else{flag=0;
        cross();}
  } 
   else if(ButtonState_g4==LOW){
    if(row6DataMatrix[6]==8){
    playstart();  
    tone(9,g4);
    delay(100);
    noTone(9);
    }
    else{flag=0;
    cross();}
  } 
   else if(ButtonState_a4==LOW){
     if(row6DataMatrix[6]==4){
     playstart();
     tone(9,a4);
     delay(100);
     noTone(9);
  } 
 else{flag=0;
    cross();}
  } 
 }
}
