// Projeto Botão com LED (interruptor)
#define PinButton 8 // define pino digital D8
#define ledPin 7 // define pino digital D7
int interruptor = false;
int statusBotao;

void setup()
{
  pinMode(PinButton, INPUT); // configura D8 como entrada digital
  pinMode(ledPin, OUTPUT); // configura D7 como saída digital
  Serial.begin(9600); // monitor serial - velocidade 9600 Bps
  delay(100); // atraso de 100 milisegundos
}

void loop()
{
  statusBotao = digitalRead(PinButton);  
  
  if(statusBotao == HIGH){
    Serial.println("Botao foi pressionado!");
    interruptor = true;
  }
  
  if(statusBotao == LOW && interruptor == true){
    Serial.println("Botao foi solto!");
    digitalWrite(ledPin, !digitalRead(ledPin));
    interruptor = false;
  }
  
  delay(100); // atraso de 100 milisegundos
}