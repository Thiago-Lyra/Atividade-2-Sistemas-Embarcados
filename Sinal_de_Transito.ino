
///////////////////////////////////////////////////////////////////////////////////////////
//Pinos dos Botões de ligar e desligar o semáforo
const int liga = 9;
const int desliga = 10;
///////////////////////////////////////////////////////////////////////////////////////////
//Variáveis para saber se o botão foi pressionado ou informar qual parte do código deve ser feita e variável tempo
int etapa;
int botaoLiga;
int botaoDesliga;
long tempoGravado;
///////////////////////////////////////////////////////////////////////////////////////////
//Pinos dos LEDs que irão funcionar como sinais de trânsitos 
const int LEDvermelho1 = 3;
const int LEDamarelo1 = 4;
const int LEDverde1 = 5;
const int LEDvermelho2 = 6;
const int LEDamarelo2 = 7;
const int LEDverde2 = 8;
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {

Serial.begin(9600);
etapa = 0;
Serial.println("Iniciando Sinal...");
Serial.println("Sinal iniciado");

}

void loop() {
///////////////////////////////////////////////////////////////////////////////////////////
//Armazena o tempo atual
unsigned long tempoAtual = millis();
///////////////////////////////////////////////////////////////////////////////////////////
//Armazena a informação se o botão foi pressionado ou não nas variáveis
botaoLiga = digitalRead(liga);
botaoDesliga = digitalRead(desliga);
///////////////////////////////////////////////////////////////////////////////////////////
//Se o botão de ligar for pressionado e o programa não estiver funcionando, vai para a etapa 1 e acende LEDs, o vermelho do primeiro sinal e verde do segundo
if (botaoLiga == 1 && etapa == 0){
  etapa = 1;
  digitalWrite(LEDvermelho1, HIGH);
  digitalWrite(LEDverde2, HIGH);
  tempoGravado = tempoAtual;
  }
///////////////////////////////////////////////////////////////////////////////////////////
//Se o botão de desligar for pressionado, desliga todos os LEDs
if (botaoDesliga == 1) {
  etapa = 0;
  digitalWrite(LEDvermelho1, LOW);
  digitalWrite(LEDamarelo1, LOW);
  digitalWrite(LEDverde1, LOW);  
  digitalWrite(LEDvermelho2, LOW);
  digitalWrite(LEDamarelo2, LOW);
  digitalWrite(LEDverde2, LOW);
  }
///////////////////////////////////////////////////////////////////////////////////////////
//etapas na qual o sinal irá seguir de acordo com o tempo cronometrado. 
if (etapa == 1) {
    if (tempoAtual-tempoGravado > 6000){
      digitalWrite(LEDverde2, LOW);
      digitalWrite(LEDamarelo2, HIGH);
      etapa = 2;
      tempoGravado = tempoAtual;
    }
  }
if (etapa == 2) {
    if (tempoAtual-tempoGravado > 2000){
      digitalWrite(LEDamarelo2, LOW);
      digitalWrite(LEDvermelho2, HIGH);
      digitalWrite(LEDvermelho1, LOW);
      digitalWrite(LEDverde1, HIGH);
      etapa = 3;
      tempoGravado = tempoAtual;
    }
  }
if (etapa == 3) {
    if (tempoAtual-tempoGravado > 10000){
      digitalWrite(LEDverde1, LOW);
      digitalWrite(LEDamarelo1, HIGH);
      etapa = 4;
      tempoGravado = tempoAtual;
    }
  }
if (etapa == 4) {
    if (tempoAtual-tempoGravado > 2000){
      digitalWrite(LEDamarelo1, LOW);
      digitalWrite(LEDvermelho1, HIGH);
      digitalWrite(LEDvermelho2, LOW);
      digitalWrite(LEDverde2, HIGH);
      etapa = 1;
      tempoGravado = tempoAtual;
    }
  }
}
