// Projeto Sensor Ultrassonico
int PinTrigger = 2; // pino usado para disparar os pulsos do sensor
int PinEcho = 3; // pino usado para ler a saida do sensor
float TempoEcho = 0; // variável tempo do eco
const float velocidadeSom_mps = 340; // em metros por segundo
const float velocidadeSom_mpus = 0.000340; // em metros por microsegundo
void setup()
{
  pinMode(PinTrigger, OUTPUT); // configura pino Trigger como saída
  digitalWrite(PinTrigger, LOW); // pino trigger - nível baixo
  pinMode(PinEcho, INPUT); // configura pino ECHO como entrada
  Serial.begin(9600); // inicializa monitor serial 9600 Bps
  delay(100); // atraso de 100 milisegundos
}
void loop()
{
  DisparaPulsoUltrassonico(); // dispara pulso ultrassonico
  TempoEcho = pulseIn(PinEcho, HIGH); // mede duração do pulso HIGH de eco em microsegundos
  Serial.print("Distancia em metros: "); // mostra no monitor serial
  Serial.println(CalculaDistancia(TempoEcho)); // mostra o calculo de distancia em metros
  Serial.print("Distancia em centimentros: "); // mostra no monitor serial
  Serial.println(CalculaDistancia(TempoEcho) * 100); // mostra o calculo de distancia em cm
  delay(2000); // atraso de 2 segundos
}
void DisparaPulsoUltrassonico()
{
  digitalWrite(PinTrigger, HIGH); // pulso alto de Trigger
  delayMicroseconds(10); // atraso de 10 milisegundos
  digitalWrite(PinTrigger, LOW); // pulso baixo de Trigger
}
float CalculaDistancia(float tempo_us)
{
  return ((tempo_us * velocidadeSom_mpus) / 2 ); // calcula distancia em metros
}