#define led_pin 5
#define isObstaclePin 6
char data;

int j=0;
int isObstacle = 1;

void setup() {
Serial.begin (9600);
j=0;
pinMode(isObstaclePin,INPUT);
pinMode(led_pin,OUTPUT);
digitalWrite(led_pin,LOW);

}

void loop() {

 isObstacle=digitalRead(isObstaclePin);
 
 if (isObstacle==0)
 {
   j++;
  Serial.print(j);
  delay(1000);
  
 }
 
if (Serial.available()) {

  data=Serial.read();
  if (data=='7'){
  digitalWrite(led_pin,HIGH);
  delay(1000);
  digitalWrite(led_pin,LOW);
  delay(1000);
  digitalWrite(led_pin,HIGH);
  delay(1000);
  digitalWrite(led_pin,LOW);
  

  

  }

}
 }













 
