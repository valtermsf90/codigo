#include <stdio.h>
#include "pico/stdlib.h"
#include "include/iniciarPinos.c"
#include "include/cores.c"
#include "include/buzzers.c"
#include "include/KeyPad.c"
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

char palavra[50];
char letra[50];
char marcadorE;
char marcadorD;

int contLinha = 0;
int contColuna = 0;
int x = 0;
int y = 0;
int pos = 0;
bool tela;
bool escrever = true;

int main()
{
    stdio_init_all(); // Inicializa a biblioteca stdio
    iniciarPinos();
    printf("%d\n", contLinha);
    printf("%d\n", contColuna);
    sleep_ms(1000);

    while (true) // Loop principal
    {
        tela = 1;
       
        while (tela == 1) // Loop da tela
        {
            printf("+=====================================+\n");
            printf("|            Matrix Writer            |\n");
            printf("|  Controle a matriz, crie palavras   |\n");
            printf("+=====================================+\n\n");

            printf("Aperte o botao A, a quantidade de vezes referente a numero da linha.\n");
            printf("Aperte o botao B, a quantidade de vezes referente a letra da coluna.\n");
            printf("Aperte o botao J para imprimir a letra.\n\n");
            printf("Para pular linha aperte  A 7x(led vermelho).\n");
            printf("Para espaço aperte  B 7x(led rosa).\n\n");
            printf(" # | 0 | 1 | 2 | 3 | 4 | 5 | 6 |\n");
            printf("---|-V-+-V-+-V-+-V-+-V-+-V-+-V-|\n");
            for (int i = 0; i < 7; i++)
            {
                printf(" %d >", i);
                for (int j = 0; j < 7; j++)
                {
                    if (x == i && y == j)
                    {
                        marcadorE = '[';
                        marcadorD = ']';
                    }
                    else
                    {
                        marcadorE = ' ';
                        marcadorD = ' ';
                    }
                    printf("%c%c%c|", marcadorE, matriz[i][j], marcadorD);
                }
                printf("\n");
                printf("---|---+---+---+---+---+---+---|\n");
            }
            tela = 0;
        }
        printf("\n\n");
        for (int i = 0; i < pos; i++)
        {
            printf("%c", letra[i]);
        }

        while (escrever)
        {
            if (gpio_get(BUTTON_A) == 0)
            {
                sleep_ms(50);
                if (contLinha < 7)
                {
                    for (int i = 0; i < 2; i++) // piscar
                    {
                        azul(100);
                        apagado(0);
                    }
                    contLinha = contLinha + 1;
                    x = contLinha;
                    printf("\033[2J");
                printf("\033[H");
                escrever = false;
                }
                else
                {
                    for (int i = 0; i < 4; i++) // piscar
                    {
                        vermelho(100);
                        apagado(0);
                    }
                    contLinha = 7;
                }
            }
            if (gpio_get(BUTTON_B) == 0)
            {
                sleep_ms(50);
                if (contColuna < 7)
                {
                    for (int i = 0; i < 2; i++) // piscar
                    {
                        amarelo(100);
                        apagado(0);
                    }
                    contColuna = contColuna + 1;
                    y = contColuna;
                    printf("\033[2J");
                    printf("\033[H");
                    escrever = false;
                }
                else
                {
                    for (int i = 0; i < 4; i++) // piscar
                    {
                        rosa(100);
                        apagado(0);
                    }
                    contColuna = 7;
                }
            }
            if (gpio_get(BUTTON_J) == 0)
            {
                sleep_ms(50);
                for (int i = 0; i < 4; i++) // piscar
                {
                    verde(100);
                    apagado(0);
                }
                
                if (contLinha < 7 && contColuna < 7)
                {
                    letra[pos] = matriz[contLinha][contColuna];
                }
                if (contColuna == 7)
                {
                    letra[pos] = ' ';
                }
                if (contLinha == 7)
                {
                    letra[pos] = '\n';
                }
                if(contLinha == 6 && contColuna == 6){
                    pos--;                    
                    letra[pos] =  matriz[contLinha][contColuna];
                }
                pos++;
                contLinha = 0;
                x = contLinha;
                contColuna = 0;
                y = contColuna;
                printf("\033[2J");
                printf("\033[H");
                escrever = false;
            }
        }
    tela = 1;
    escrever = 1;
    }
}
