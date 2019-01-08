#include<Servo.h>
String readString, store;
#define m1 3
#define m2 4
#define m3 7
#define m4 8
#define en1 5
#define en2 6

#define echo 12
#define trig 11
int distance,pos=0,d=3,i=70, x=0,flag=0,a=1;
Servo servo_D;
Servo servo_U;

void setup() {
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //servo_D.attach(9);
  servo_U.attach(10);
}

void loop() {
  while(a>0)
  {
    servo_U.write(60);
    a=0;
  }
    while (Serial.available())
  {
    delay(3);
    char c = Serial.read();
    if (c == ','){
      break;
    }
   readString += c;
    // put your main code here, to run repeatedly:
    }
if(readString.length() >0)
      {
        //Serial.println(readString);
        if (readString == "R")
        {
          Serial.println(store);
          right();
          flag=1;
          Serial.println("Right");
          store="R";
        }
        if (readString == "L")
        {     
          left();
          Serial.println("Left");
          flag=1;
          store="L";

        }  
        if (readString == "F")
        {
          flag=1;
          if(store == "S")
          {
            x=0;
          }
          forward();
          Serial.println("Forward");
          store="F";
          
        }
        if (readString == "S")
        {
          stopbot();
          Serial.println("Stop");
          store="S";
        }
        if (readString == "U")
        {
          servo_U.write(60);
          Serial.println("Upward");
          store="F";
          
        }
         if (readString == "D")
        {
           
          servo_U.write(10);
          Serial.println("Downward");
          store="F";
          
        }
        if (readString == "FLAT")
        {
          servo_U.write(90);
          Serial.println("Flat");
          store="F";
          
        }
        
        Serial.println(store);
     readString="";
     }
    
 //Distance();
/*
 if(Serial.available()>0)
{
  pos=Serial.parseInt();
}
    Serial.println(pos);
if(pos>0)

{ if(i <= 53 || i>=135)
{
  Serial.println(i);
  d=d*-1;
}
  
  servo_D.write(i);
  i += d;
  delay(30);
}
*/
}
void Distance()
{
 long duration;

digitalWrite(trig, LOW); 
delayMicroseconds(2); 
digitalWrite(trig, HIGH); 
delayMicroseconds(10); 
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH); 
distance = duration*0.034/2 ;
Serial.print("distance= ");
Serial.println(distance);
delay(100);
}
void forward()
{
  for(x;x<=255;x+=x+10)
  {
    analogWrite(en1, x);
    analogWrite(en2, x);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(50);
  }
  
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(40);
}
void stopbot()
{
    
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    delay(40);
  
}
void left()
{   while(flag==1)
{
    analogWrite(en1, 180);
    analogWrite(en2, 180);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    delay(1120);
    flag=0;
}
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    delay(40);
}
void right()
{
  while(flag==1)
  {
    analogWrite(en1, 180);
    analogWrite(en2, 180);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    delay(1120);
    flag=0;
}
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    delay(40);
}
