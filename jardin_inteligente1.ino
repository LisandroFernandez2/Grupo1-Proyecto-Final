
#include <Adafruit_LiquidCrystal.h>

#define SensorDeHumedadPin A4
#define SensorDeTemperaturaPin A5
#define PinMotorDeRiego 3 
#define PinVentilador 5 
#define PinBuzzer 12 
#define PinLuz A3 
#define PinBombilla 6 
#define PinLed 2 

// PARA EL BUZZER 
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0])) 
#define NOTA_A2 110 
#define NOTA_C3 131 

// NUEVA INICIALIZACIÓN PARA ADAFRUIT LCD I2C (Dirección 0x27)
Adafruit_LiquidCrystal lcd(0);  
//========================= VARIABLES ========================= 
int Humedad, Temperatura, Luz; 
const int midi1[4][3] = { 
  {NOTA_A2, 136, 0}, 
  {NOTA_C3, 136, 0}, 
  {NOTA_A2, 136, 0}, 
  {NOTA_C3, 136, 0}, 
}; 

void playMidi(int pin, const int notes[][3], size_t len) { 
  for (int i = 0; i < len; i++) { 
    tone(pin, notes[i][0]); 
    delay(notes[i][1]); 
    noTone(pin); 
    delay(notes[i][2]); 
  } 
} 

void setup() { 
  Serial.begin(9600); 
  pinMode(PinMotorDeRiego, OUTPUT); 
  pinMode(PinBuzzer, OUTPUT); 
  pinMode(PinVentilador, OUTPUT); 
  pinMode(PinBombilla, OUTPUT); 
  pinMode(PinLed, OUTPUT); 
  lcd.begin(16, 2); 
  lcd.setBacklight(HIGH); 
} 

void LeerSensores() { 
  Humedad = analogRead(SensorDeHumedadPin); 
  Humedad = map(Humedad, 696, 885, 0, 100); 
  
  Temperatura = analogRead(SensorDeTemperaturaPin); 
Temperatura = map(Temperatura, 982, 996, -40, 125); 
  
  Luz = analogRead(PinLuz); 
  Luz = map(Luz, 1021, 642, 0, 100); 
} 

void Regar() { 
  digitalWrite(PinMotorDeRiego, HIGH); 
} 

void ControlarElRiego() { 
  if (Humedad < 30) { 
    Regar(); 
  } else { 
    digitalWrite(PinMotorDeRiego, LOW); 
  } 
} 

void ControlarLaTemperatura() { 
  if (Temperatura <= 0) { 
    digitalWrite(PinVentilador, LOW); 
    digitalWrite(PinBombilla, HIGH);
  } else if (Temperatura > 40) { 
    playMidi(PinBuzzer, midi1, ARRAY_LEN(midi1)); 
    digitalWrite(PinVentilador, HIGH); 
    digitalWrite(PinBombilla, LOW); 
  } else { 
    noTone(PinBuzzer); 
    digitalWrite(PinVentilador, LOW); 
    digitalWrite(PinBombilla, LOW); 
  } 
} 

void ControlarLaIluminacion() { 
  if (Luz < 40) { 
    digitalWrite(PinLed, HIGH); 
  } else { 
    digitalWrite(PinLed, LOW); 
  } 
} 

void MostrarEnLCD() { 
  lcd.setCursor(0, 0); 
  lcd.print("Hum:"); 
  lcd.print(Humedad); 
  lcd.print("% Luz:"); 
  lcd.print(Luz);
  lcd.print("% ");
  lcd.setCursor(0, 1); 
  lcd.print("Tem:"); 
  lcd.print(Temperatura); 
  lcd.print("C ");
  if (Temperatura <= 0){
    lcd.print("FRIO   ");
  }
  else if (Temperatura > 40){
    lcd.print("CALOR   ");
  }
  else{
    lcd.print("TEMPLADO");
  }
} 

void loop() { 
  LeerSensores(); 
  ControlarElRiego(); 
  ControlarLaTemperatura(); 
  ControlarLaIluminacion(); 
  MostrarEnLCD(); 
  delay(500); 
}
