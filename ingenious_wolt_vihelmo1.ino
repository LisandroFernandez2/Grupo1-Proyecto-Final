int pinSensorPIR = 2; 
int pinMotor = 3;     

void setup() {
  pinMode(pinSensorPIR, INPUT); 
  pinMode(pinMotor, OUTPUT);    
}

void loop() {

  if (digitalRead(pinSensorPIR) == HIGH) {
    digitalWrite(pinMotor, HIGH);
    delay(3000);                  
  } 
  else {
    digitalWrite(pinMotor, LOW);  
  }
}