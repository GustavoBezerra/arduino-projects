// Projeto de Sensor Ultrassonico com Display

#include <LiquidCrystal.h> // biblioteca Liquid Crystal

#define PinTrigger 2 // pino usado para disparar os pulsos do sensor
#define PinEcho 3    // pino usado para ler a saída do sensor

// Sensor de temperatura
#define Vin 5.0 // define constante igual a 5.0
#define T0 298.15 // define constante igual a 298.15 Kelvin
#define Rt 10000 // Resistor do divisor de tensao
#define R0 10000 // Valor da resistencia inicial do NTC
#define T1 273.15 // [K] in datasheet 0º C
#define T2 373.15 // [K] in datasheet 100° C
#define RT1 35563 // [ohms] resistencia in T1
#define RT2 549 // [ohms] resistencia in T2
float beta = 0.0; // parametros iniciais [K]
float Rinf = 0.0; // parametros iniciais [ohm]
float TempCelsius = 0.0; // variable output
float Vout = 0.0; // Vout in A0
float Rout = 0.0; // Rout in A0


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

  // Sensor de temperatura
  beta = (log(RT1 / RT2)) / ((1 / T1) - (1 / T2)); // calculo de beta
  Rinf = R0 * exp(-beta / T0); // calculo de Rinf

  
  Serial.begin(9600);  
  delay(500); // atraso de 0,5 segundos
}
void loop()
{
  lcd.clear(); // limpa tela do LCD
  
  disparaPulsoUltrassonico();           // dispara pulso ultrassonico
  tempoEcho = pulseIn(PinEcho, HIGH);   // mede duração do pulso HIGH de eco em microsegundos

  Vout = Vin * ((float)(analogRead(0)) / 1024.0); // calculo de V0 e leitura de A0
  Rout = (Rt * Vout / (Vin - Vout)); // calculo de Rout
  TempCelsius = (beta / log(Rout / Rinf)) - 273.15; // calculo da temp. em Celsius

  lcd.setCursor(0, 0); // selecionando coluna 0 e linha 0
  lcd.print(" MT |");
  lcd.print(" CM |");
  lcd.print(" TEMP");

  lcd.setCursor(0, 1); // selecionando coluna 0 e linha 0
  lcd.print(calculaDistancia(tempoEcho), 1);
  lcd.setCursor(4, 1); // selecionando coluna 0 e linha 0
  lcd.print("|");

  lcd.print(calculaDistancia(tempoEcho) * 100, 1);
  lcd.setCursor(9, 1); // selecionando coluna 0 e linha 0
  lcd.print("| ");

  lcd.print(TempCelsius, 1);
  
 
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
