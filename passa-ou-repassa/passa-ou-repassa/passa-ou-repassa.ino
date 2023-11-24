#include <Pushbutton.h>

#define NOTE_C4  262

const int blueButtonPin = 11;
const int redButtonPin = 9;
const int blueLedPin = 5;
const int redLedPin = 3;
const int buzzerPin = 10;

int buttonState = 0;
Pushbutton blueButton(blueButtonPin);
Pushbutton redButton(redButtonPin);

void setup() {
  Serial.begin(9600);
  Serial.println("Definindo saidas dos leds");
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.println("Saidas de leds definidas.");
  Serial.println("Definindo saida do buzzer");
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Saida do buzzer definida definida");
  delay(1500);
  Serial.println("Fim do setup");
}

void loop() {
  if(blueButton.getSingleDebouncedPress() && !redButton.getSingleDebouncedPress()){
    Serial.println("Botão azul pressionado");
    soaAlarme2(blueLedPin);
  } else if(redButton.getSingleDebouncedPress() && !blueButton.getSingleDebouncedPress()){
    Serial.println("Botão vermelho pressionado");
    soaAlarme2(redLedPin);
  }
  delay(10);
}

void soaAlarme(){
  Serial.println("1 nota");
  tone(buzzerPin,293);    
  delay(400);
  noTone(buzzerPin);
  delay(100);
  Serial.println("2 nota");
  tone(buzzerPin,293);    
  delay(400);
  noTone(buzzerPin);
  delay(100);
  Serial.println("3 nota");
  tone(buzzerPin,293);    
  delay(400);
  noTone(buzzerPin);
  delay(100);
  Serial.println("4 nota");
  tone(buzzerPin,293);    
  delay(400);
  noTone(buzzerPin);
  delay(100);
  Serial.println("5 nota");
  tone(buzzerPin,293);    
  delay(400);
  noTone(buzzerPin);
}

void soaAlarme2(int pinLed){
  tone(buzzerPin, NOTE_C4);
  digitalWrite(pinLed, LOW);
  delay(400);
  noTone(buzzerPin);
  digitalWrite(pinLed, HIGH);
  delay(100);
  tone(buzzerPin, NOTE_C4);
  digitalWrite(pinLed, LOW);
  delay(400);
  noTone(buzzerPin);
  digitalWrite(pinLed, HIGH);
  delay(100);
  tone(buzzerPin, NOTE_C4);
  digitalWrite(pinLed, LOW);
  delay(400);
  noTone(buzzerPin);
  digitalWrite(pinLed, HIGH);
  delay(100);
  tone(buzzerPin, NOTE_C4);
  digitalWrite(pinLed, LOW);
  delay(400);
  noTone(buzzerPin);
  digitalWrite(pinLed, HIGH);
  delay(100);
  tone(buzzerPin, NOTE_C4);
  digitalWrite(pinLed, LOW);
  delay(400);
  noTone(buzzerPin);
  digitalWrite(pinLed, HIGH);
}
