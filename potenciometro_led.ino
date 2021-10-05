// Projeto : Controle de luminosidade de led com potenciometro
// Data: 05/10/2021
 
int pinoLed = 10;  //Pino ligado ao anodo do led
int pinoPotenciometro = 5;   //Pino ligado ao pino central do potenciometro
int valorPotenciometro = 0;
int luminosidade = 0;

void setup()
{
}
 
void loop()
{
  valorPotenciometro = analogRead(pinoPotenciometro);
  
  luminosidade = map(valorPotenciometro, 0, 1023, 0, 255);
 
  //Converte e atribui para a variavel "luminosidade" o
  // valor lido do potenciometro
  //map(valor, de_menor_valor, de_maior_valor, para_menor_valor, para_maior_valor)
  luminosidade = map(valorPotenciometro, 0, 1023, 0, 255);  
 
  Serial.print("Valor lido do potenciometro : "); 
  Serial.print(valorPotenciometro);   
  Serial.print(" = Luminosidade : ");
  Serial.println(luminosidade);  
  
 
  //Envia sinal analogico para a saída do led, com luminosidade variavel
  analogWrite(pinoLed, luminosidade);  
}
