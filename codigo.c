#include <stdio.h>
#include "pico/stdlib.h"
#include "include/iniciarPinos.c"
#include "include/cores.c"
#include "include/buzzers.c"
#include "include/KeyPad.c"
#include "C/perguntas.c"
#include "C/frases.c"

#define LED_R 13
#define LED_B 12
#define LED_G 11
#define BUZZER_B 10
#define BUZZER_A 21
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_J 22
#define TIME 300
char letra;
int contLinha;
int contColuna;
int botao;  

int main() {
    /*sleep_ms(3000);
    printf("Bem vindo gerado de Codigos\n");
    printf("Aperte o botao A, a quantidade de vezes referente a numero da linha.\n");
    printf("Aperte o botao B, a quantidade de vezes referente a letra da coluna.\n");
    printf("Aperte o botao J para imprimir o codigo.\n");
    printf("_____________________________\n");
    printf("| # | 1 | 2 | 3 | 4 | 5 | 6 |\n");
    printf("_____________________________\n");
    printf("| 1 | A | B | C | D | E | F |\n");
    printf("_____________________________\n");
    printf("| 2 | G | H | I | J | K | L |\n");
    printf("_____________________________\n");
    printf("| 3 | M | N | O | P | Q | R |\n");
    printf("_____________________________\n");
    printf("| 4 | S | T | U | V | W | X |\n");
    printf("_____________________________\n");
    printf("| 5 | Y | Z | 0 | 1 | 2 | 3 |\n");
    printf("_____________________________\n");
    printf("| 6 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
    printf("_____________________________\n");
    sleep_ms(3000);*/

    stdio_init_all();  // Inicializa a biblioteca stdio
    iniciarPinos(); 
    contLinha = 0;
    contColuna = 0;
    while (true) {
        if (gpio_get(BUTTON_A) == 0) {
            if(contLinha < 6){ 
                for(int i = 0; i < 2; i++){
                    azul(TIME);
                    apagado(0);                  
                }
                contLinha = contLinha + 1;
            }else{
                for(int i= 0; i < 4; i++){
                    vermelho(TIME);
                    apagado(0);
                }
                    contLinha = 6;
            }
        }
        if (gpio_get(BUTTON_B) == 0) {
            if(contColuna < 6){ 
                for(int i = 0; i < 2; i++){
                    amarelo(TIME);
                    apagado(0);
                }
                contColuna = contColuna + 1;
            }else{
                for(int i= 0; i < 4; i++){
                    vermelho(TIME);
                    apagado(0);
                }
                contColuna = 6;
            }
        }
        if (gpio_get(BUTTON_J) == 0) {
            for(int i = 0; i < 2; i++){
                verde(TIME);
                apagado(0);
            }

            letra = matriz[contLinha - 1][contColuna - 1];
            contLinha = 0;
            contColuna = 0;
            printf("%c", letra);
        }            
    }
}
