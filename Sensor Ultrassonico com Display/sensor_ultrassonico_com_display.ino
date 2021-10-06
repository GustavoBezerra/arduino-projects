// Projeto de Sensor Ultrassonico com Display

#include <LiquidCrystal.h> // biblioteca Liquid Crystal

#define PinTrigger 2 // pino usado para disparar os pulsos do sensor
#define PinEcho 3    // pino usado para ler a saída do sensor

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // pinos do LCD - RS E D4 D5 D6 D7

float tempoEcho = 0;    // variável tempo do eco
const float velocidadeSom_mps = 340;        // em metros por segundo
const float velocidadeSom_mpus = 0.000340;  // em metros por microsegundo

void setup()
{
  lcd.begin(16, 2); // inicializa LCD 16x2

  pinMode(PinTrigger, OUTPUT);
  digitalWrite(PinTrigger, LOW);
  pinMode(PinEcho, INPUT);
  
  Serial.begin(9600);  
  delay(500); // atraso de 0,5 segundos
}
void loop()
{
  lcd.clear(); // limpa tela do LCD
  
  disparaPulsoUltrassonico();           // dispara pulso ultrassonico
  tempoEcho = pulseIn(PinEcho, HIGH);   // mede duração do pulso HIGH de eco em microsegundos
  
  lcd.setCursor(0, 0); // selecionando coluna 0 e linha 0
  lcd.print("Metros: "); // mostra no LCD
  lcd.print(calculaDistancia(tempoEcho));
  
  lcd.setCursor(0, 1); // selecionando coluna 1 e linha 1
  lcd.print("CM: "); // mostra no LCD
  lcd.print(calculaDistancia(tempoEcho) * 100);
  
  delay(1000); // atraso de 1 segundo
}


void disparaPulsoUltrassonico(){
  digitalWrite(PinTrigger, HIGH); // pulso alto
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW); // pulso baixo
}

float calculaDistancia(float tempo_us){
  return ((tempo_us * velocidadeSom_mpus) / 2); // calcula distancia em metros
}
