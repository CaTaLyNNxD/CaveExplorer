#include "dht.h"
dht DHT;

char t;
int led = 0;
int pressed1 = 0;
int pressed2 = 0;
int pressed3 = 0;
int pressed4 = 0;
int pressed9 = 0;
int pressed10 = 0;
const int gas_pin = A5;
const int dht_apin = A4;
const int trigPin = 8;
const int echoPin = 2;
const int fr = A1;
int distance;
int gas_value;
long duration;
int lightfr;
int sensoron=1;

void setup() {
pinMode(9,OUTPUT);    //left motors forward
pinMode(10,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(12,OUTPUT);   //right motors reverse
pinMode(3,OUTPUT);    //lights
pinMode(7,OUTPUT);    //NIGHT MODE LIGHTS
pinMode(6,OUTPUT);    //reverse light
pinMode(5,OUTPUT);    //yellow led
pinMode(4,OUTPUT);    //buzzer
pinMode(fr,INPUT);    //photoresistor
pinMode(trigPin, OUTPUT); // trigPin
pinMode(echoPin, INPUT);  // echoPin
pinMode(gas_pin, INPUT); // gas sensor
pinMode(dht_apin, INPUT); // t&h sensor
Serial.begin(9600);
}
 
void loop() {
  gas_value = analogRead(gas_pin);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  lightfr=analogRead(fr);

if(Serial.available()){
  t = Serial.read();
}

if (sensoron==1){
if (distance<=25){
  analogWrite(5, 20);
  
  if (distance <=15){
    analogWrite(5, 80);
    
    if (distance<=8){
      digitalWrite(5, HIGH);
      tone(4, 4000, 20);
    }
  }
}

else 
  digitalWrite(5, LOW);
  
}

else 
  digitalWrite(5, LOW);

if (led!=2) {
  if ((lightfr<=30)&&(led==0)) analogWrite(3, 80);
    else if ((lightfr<=30)&&(led==1)) {digitalWrite(3, HIGH);}
      else if ((lightfr>30)&&(led==1)) {analogWrite(3, 200);}
        else if ((lightfr>30)&&(led==0)) {digitalWrite(3, LOW);}
}
  
if(t == '1'){            //move forward(all motors rotate in forward direction)
  if (distance>7){
  if (pressed1==0){
    if (pressed2==1){   //hard anti wheelie
        analogWrite(9,90);
        digitalWrite(10,LOW);
        analogWrite(11,90);
        digitalWrite(12,LOW);
        delay(125); 
    }
  analogWrite(9,140); //normal anti wheelie
  analogWrite(11,140);
  delay(125);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  pressed1=1;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
}
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  }
}
 
else if(t == '2'){      //move reverse (all motors rotate in reverse direction)
  if (pressed2==0){
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  pressed2 = 1;
  pressed1 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
}
 
else if(t == '3'){      //turn left
  if (distance>5){
  if (pressed3==0){
  analogWrite(9,80);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  pressed3 = 1;
  pressed1 = 0;
  pressed2 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  }
}
 
else if(t == '4'){      //turn right
  if (distance>5){
  if (pressed4==0){
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  analogWrite(11,80);
  digitalWrite(12,LOW);
  pressed4 = 1;
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
  }
}
 
else if(t == '5'){      //STOP (all motors stop)
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(6, LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  led=0;
  Serial.println("Everthing was stopped!");
}

else if(t == '6'){      //fast left
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  delay(500);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
}

else if(t == '7'){      //fast right
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
}

else if(t == '9'){      //turn back-left (left side motors rotate in backward direction)
  if (pressed9==0){
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed9 = 1;
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed10 = 0;
  }
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
}

else if(t == '0'){      //turn back-right (right side motors rotate in backward direction)
  if (pressed10==0){
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  pressed10=1;
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  }
  else {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }
}

else if(t=='8'){      //turn lights on/off
  loopled:
  if (led<0) {led=0; Serial.println("Bright mode.");}
  else if (led==0) {led=1; Serial.println("Normal light mode.");}
    else if (led==1) {led=2; Serial.println("Night mode.");}
      else if (led==2) {led=0; Serial.println("Bright mode.");}
}

else if(t=='f'){      //flash
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    delay(50);
    led-=1;
    goto loopled;
  }

  else if(t=='s'){      //turn distance sensor on/off
    if (sensoron==1) {sensoron=0; Serial.println("Distance sensor turned OFF.");}
      else {sensoron=1; Serial.println("Distance sensor is now activated.");}
  }
  
  else if(t=='t'){
    DHT.read11(dht_apin);
    Serial.print("Temperature: "); Serial.print(DHT.temperature); Serial.println(" *C");
    Serial.print("Humidity: "); Serial.print(DHT.humidity); Serial.println(" %");
  }

  else if(t=='g'){
    Serial.print("The gas concentration is ");Serial.println(gas_value);
      if (gas_value<400) Serial.print("It is in normal values.");
        else Serial.print("It is OVER the normal limits! Be careful!");
  }

   if ((pressed1==1) && (distance <=15)){
    analogWrite(9,120);
    analogWrite(11,120);
   }

  if (((pressed1==1) || (pressed3==1) || (pressed4==1)) && (distance <=7)) {
    if (pressed1==1){
      digitalWrite(10, HIGH);
      digitalWrite(12, HIGH);
      delay(75);
    }
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  pressed1 = 0;
  pressed2 = 0;
  pressed3 = 0;
  pressed4 = 0;
  pressed9 = 0;
  pressed10 = 0;
  }

  if (led==2) {
    digitalWrite (3, HIGH);
    digitalWrite (7, HIGH);
  } else digitalWrite(7, LOW);

  if (led==2) {
    digitalWrite(6, HIGH);
  }
    else if (pressed2==1){
      analogWrite(6, 60);
    }

      else if ((pressed10==1) || (pressed9==1)) {
        analogWrite(6, 20);
      }
        else if ((led!=2) && (pressed10!=1) && (pressed9!=1) && (pressed2!=1)) digitalWrite(6, LOW);
  
  delay(1);
}
