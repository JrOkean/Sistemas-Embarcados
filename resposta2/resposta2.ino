#include <Wire.h>
#include "rgb_lcd.h"
#include <SPI.h>
#include <FlashStorage.h>
#include <PCF85063TP.h>

rgb_lcd lcd;
PCF85063TP clock;

//Array de números para o jogo
int ordered_array[] = {0,1,2,3,4,5,6,7,8,9};

//Variáveis globais para guardar informações do jogo e manipulação
int sequence[10];
int num_inOrder = 0;
int num_swaps = 0;

FlashStorage(best_swaps, int);
FlashStorage(best_time, int);


void random_numbers(){
  
}

void setup() {
  SerialUSB.begin(9600);

  lcd.begin(16, 2); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
