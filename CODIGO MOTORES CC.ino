int  IN1 = 2;
int  IN2 = 3;
int  IN3 = 6;
int  IN4 = 7;
int ENA =  5;
int ENB = 8;
void setup(){
  pinMode(IN1 , OUTPUT);
  pinMode(IN2 , OUTPUT);
  
  pinMode(IN3 , OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA , OUTPUT);
  pinMode(ENB , OUTPUT);
}

void loop(){
   digitalWrite(ENA,HIGH);
   digitalWrite(ENB,HIGH);
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   delay(3000);

   digitalWrite(ENA,LOW);
   digitalWrite(ENB,LOW);
  delay(2000);

  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   delay(3000);

   digitalWrite(ENA,LOW);
   digitalWrite(ENB,LOW);
  delay(2000);
}
