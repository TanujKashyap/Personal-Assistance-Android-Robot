
#include<Servo.h>

byte AInput = 6;
byte BInput = 7;
//int arr[10]={};
int incount = 0;
int b1=0;

int i =1;
long duration;
int distance;

Servo motorPin;

String readString;
int path[15]={};
int a1=0, j=0;
int precell=0;
 
byte lastState = 0;
int steps = 0, cell, n2=45;
int  cw = 0;
byte AState = 0;
byte BState = 0;
byte State = 0;

const int en1=11;
const int ml1=A1;
const int ml2=A2;
const int mr2=A3;
const int mr1=A4;
const int en2=3;

int x=0, dir=0;

const int trig = 5;
const int echo = 4;
int ab=0;

 
void setup() {
  Serial.begin(9600);
  pinMode(AInput, INPUT);
  pinMode(BInput, INPUT);
  
  pinMode(en1, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(mr1, OUTPUT);
  pinMode(en2, OUTPUT);
  
motorPin.attach(9);
  
  pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
motorPin.write(90);
  
}
 
void loop() {
  while(1){
 
  while (Serial.available())
  {
    delay(3);
    char c =  Serial.read();
    if (c == ' '){
      break;
    }
    if(c=='['){
      continue;
    }
    
   readString += c;
    
    }

if(readString.length() >0){
    ab=readString.toInt();

 delay(300);

 
  if(ab!=0){
    path[a1]=ab;
  }
  a1++;
  if(ab==500){
    readString="";
    break;
  } 
 
}

readString="";
}
i=0;
while(1){

  x=path[i];
  Serial.println(x);
  dir=x/100;
  x=x%100;
  if(dir==1){
    cell=0;
    precell=0;
    steps=0;
    lastState=0;
    //Serial.println("Straight");  
    straight(); 
    b1=0; 
    while(x>cell)
    {
     // scan();
     //distanceCal();
     readwheel();
     if((cell-precell)==1){
    Serial.println('1');
    precell=cell;
  }
    }
    stopBot();;
    //Serial.println("Stop");
  
  }
  else if(dir==2){
    
    cell=0;
    steps=0;
    lastState=0;
    Serial.println("right");
    right();

    stopBot();
  //  Serial.println("stopbot");
  }
  else if(dir==3){
    
    cell=0;
    steps=0;
    lastState=0;
    Serial.println("left");
    left();
 
    stopBot();
 //   Serial.println("stopbot");
  }
  else if(dir==4){
    cell=0;
    steps=0;
    lastState=0;
    back();
//    Serial.println("back");
    
    stopBot();
    Serial.println("stopbot");

  }
  else if(dir==5){
    cell=0;
    steps=0;
    lastState=0;
        
    stopBot();
   Serial.println("stopbot");
   Serial.println("breaking");
   a1=0;
    break;

  }
  
  i++;
}
}
void readwheel()
{
  // read the input pin:
  AState = digitalRead(AInput);
  BState = digitalRead(BInput) << 1;
  State = AState | BState;
 
  if (lastState != State){
    switch (State) {
      case 0:
        if (lastState == 2){
          steps++;
          cw = 1;
        }
        else if(lastState == 1){
          steps--;
          cw = -1;
        }
        break;
      case 1:
        if (lastState == 0){
          steps++;
          cw = 1;
        }
        else if(lastState == 3){
          steps--;
          cw = -1;
        }
        break;
      case 2:
        if (lastState == 3){
          steps++;
          cw = 1;
        }
        else if(lastState == 0){
          steps--;
          cw = -1;
        }
        break;
      case 3:
        if (lastState == 1){
          steps++;
          cw = 1;
        }
        else if(lastState == 2){
          steps--;
          cw = -1;
        }
        break;
    }
  }
 
  lastState = State;
//  Serial.print(State);
//  Serial.print("\t");
//  Serial.print(cw);
//  Serial.print("\t");
  //Serial.println(steps);
  cell=steps/n2;
  
//Serial.println(cell);
  delay(1);
}

void straight(){
  analogWrite(en1, 135);
  analogWrite(en2, 150);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  delay(10);
}
void right(){
  analogWrite(en1, 85);
  analogWrite(en2, 85);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  delay(1690);
}
void left(){
  analogWrite(en1, 85);
  analogWrite(en2, 85);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  delay(1690);
}void back(){
  analogWrite(en1, 80);
  analogWrite(en2, 80);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  
  delay(3400);
}
void stopBot(){
  analogWrite(en1,0 );
  analogWrite(en2, 0);
  digitalWrite(ml1, 0);
  digitalWrite(ml2, LOW);
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, 0);
  
}
void distanceCal()
{
  digitalWrite(trig, LOW);
delayMicroseconds(2);

digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance= duration*0.034/2;
}

void scan()
{
  for(int b=40; b<145; b=b+25)
  {
    motorPin.write(abs(b-b1));
    delay(10);
    distanceCal();
    if(distance<35)
    {
      while(distance<35){
        stopBot();
        Serial.println("stop");
        distanceCal();
      }          
    }
    else{
        straight();
        readwheel();
        Serial.println("straight");
    }
  }
  b1=180-b1;
}
