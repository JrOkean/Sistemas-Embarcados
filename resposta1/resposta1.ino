#include <Wire.h>
#include "rgb_lcd.h"
#include <SPI.h>
#include <FlashStorage.h>
#include <DS1307.h>


// ----------------------------------------------------------- CABEÇALHO E GLOBAIS:

//Foi definido a porta 4 por convenção com relação a aula
const int pushButton = 4;
int stateButton = 0;

//Usando como solução para o estado da porta:
const int pushSwitch = 3;
int stateSwitch = 0;

//Para poder usar o display:
rgb_lcd lcd;

int initial_value_people = 0;
int previous_value_people = 0;
int difference_value = 0;

//Para usar o relógio RTC
DS1307 clock;


//Preparando os valores para serem guardados na FLASH:
FlashStorage(actual_value_people, int); 

const int power = 15; // Pino de alimentação


// ----------------------------------------------------------- MÉTODOS:
//Função para o papel de contador
int increment(int number){
  return number++;
}

/*
Para a relação de desligar a alimentação quando a porta estiver fechada, vou usar a peça Groove - Switch (P) [referência: https://wiki.seeedstudio.com/Grove_Starter_Kit_Plus/] e os 
estados guardados na variável "power" que está conectado ao pino de alimentação 15
*/
//Função para o papel de desligar a alimentação
void set_on(){
  digitalWrite(power, HIGH);
}

void set_off(){
  digitalWrite(power, LOW);
}

//Métodos para ler e escrever na memória
void store_flash(int valor){
  actual_value_people.write(valor);
}

int read_flash(){
  return actual_value_people.read();
}

/*
Considerando o uso do clocker RTC que funciona com bateria, a função a seguir são os passos para a comparação dos passageiros de um dia para o outro
passando pelos passos de Armazenar os valores -> calcular a diferença -> limpar o display -> printar no display a diferença
*/

void reset_system(){
  int initial_value_people = 0;

  int previous_value_people = read_flash();

  int difference_value = initial_value_people - previous_value_people;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Diferença de passageiros");
  
  lcd.setCursor(0, 1);
  lcd.print(difference_value);
}


void setup() {
  Serial.begin(9600);
  SerialUSB.begin(9600);

  //Começo da resolução se dá com setar o botão que será pressionado quando as pessoas entrarem no ônibus
  pinMode(pushButton, INPUT);
  
  //Para regulação de abrir e fechar a porta
  pinMode(pushSwitch, INPUT);

  //Inicializando o tempo e ajustando para a data corrente dessa implementação:
  clock.begin();
  clock.fillByHMS(15,28,30);

  //Set do uso do display lcd:
  lcd.begin(16, 2); 
  lcd.setCursor(0, 0);
  lcd.print("Pessoas Embarcadas:"); //mensagem para notificar do que se tratará o número logo em seguida
}

void set_cursor_numbers(int var){
  lcd.setCursor(0,1);
  lcd.print(var);
}

void loop() {

  //Leitura do estado do PushButton, lembrando que ele começa como 0, então o contrário será utilizado como "gatilho" para a contagem
  stateButton = digitalRead(pushButton);
  stateSwitch = digitalRead(pushSwitch);

  //Selecionando a data atual corrente, dado o fato da data acionada no relógio do setup
  clock.getTime();
  if (clock.hour == 23 && clock.minute == 59) {
    delay(60000); 
    clock.getTime();
    // checa se passou da meia-noite
    reset_system();
    actual_value_people.write(0);
  }

  //Se o switch estiver na posição high, então a contagem de passageiros é aberta, em outro caso, a placa não recebrá alimentação
  if (stateSwitch == HIGH){
    set_on();
    int var = read_flash();
    set_cursor_numbers(var);
    if (stateButton == HIGH) {
      increment(var);
      store_flash(var);
    }
  } else {
      set_off();
  }
  
  clock.getTime();
}
