// INSTALAR LAS LIBRERIAS LiquidCrystal I2C Y DHT sensor library
#include "DHT.h"
#define SensorDeHumedadPin A2
#define PinMotorDeRiego 3 
#define PinVentilador 5 
#define PinBuzzer 12 
#define PinLuz A3 
#define PinBombilla 6 
#define PinLed 2 
#define DHTPIN 4     
#include <LiquidCrystal_I2C.h>
// Definimos el tipo de sensor (en este caso, DHT11)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// PARA EL BUZZER 
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0])) 
#define NOTA_A2 110 
#define NOTA_C3 131 

LiquidCrystal_I2C lcd(0x27,16,2); 
//========================= VARIABLES ========================= 
int Humedad, Temperatura, Luz, HumedadSuelo; 
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
  dht.begin();
  lcd.init(); 
  lcd.backlight();
} 

void LeerSensores() { 
    // Esperamos 2 segundos entre mediciones (el DHT11 es lento)
  delay(2000);

  // Leemos la humedad relativa
  Humedad = dht.readHumidity();
  // Leemos la temperatura en grados Celsius
  Temperatura = dht.readTemperature();
  HumedadSuelo = analogRead(SensorDeHumedadPin);
  //Humedad = map(Humedad,)
  Serial.print("Humedad: ");
  Serial.print(Humedad);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(Temperatura);
  Serial.println(" *C");
  Serial.print("Humedad del suelo: ");
  Serial.print(HumedadSuelo);
  // maximo 666
  Luz = analogRead(PinLuz); 
  Luz = map(Luz, 194, 1, 0, 100); 
  
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
  lcd.print(HumedadSuelo); 
  lcd.print("Luz:"); 
  lcd.print(Luz);
  lcd.print("% ");
  lcd.setCursor(0, 1); 
  lcd.print("Tem:"); 
  lcd.print(Temperatura); 
  lcd.print("C ");
  if (Temperatura <= 0){
    lcd.print("MUYFRIO");
  }
  else if (Temperatura < 15){
    lcd.print("FRIO     ");
  }
  else if (Temperatura > 25){
    lcd.print("CALOR   ");
  }
  else if (Temperatura >= 40){
    lcd.print("INFIERNO");
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
