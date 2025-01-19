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
int contLinha = 0;
int contColuna = 0;
int botao;
bool tela;
bool escrever = true;
char palavra[50];
int x = 0;

int main()
{
    stdio_init_all(); // Inicializa a biblioteca stdio
    iniciarPinos();
    printf("%d\n", contLinha);
    printf("%d\n", contColuna);
    sleep_ms(1000);
    contLinha = 0;
    contColuna = 0;
    int posicaoPalavra = 0;

    while (true) // Loop principal
    {
        tela = 1;
        sleep_ms(3000);
        while (tela == 1)
        {
            printf("+=====================================+\n");
            printf("|            Matrix Writer            |\n");
            printf("|  Controle a matriz, crie palavras   |\n");
            printf("+=====================================+\n\n");

            printf("Aperte o botao A, a quantidade de vezes referente a numero da linha.\n");
            printf("Aperte o botao B, a quantidade de vezes referente a letra da coluna.\n");
            printf("Aperte o botao J para imprimir a letra.\n\n");
            printf("Para espaço aperte  A 6x(led vermelho).\n");
            printf("Para enter aperte  B 6x(led rosa).\n\n");
            printf(" # | 0 | 1 | 2 | 3 | 4 | 5 |\n");
            printf("---|-V-+-V-+-V-+-V-+-V-+-V-|\n");
            for (int i = 0; i < 6; i++)
            {
                printf(" %d >", i);
                for (int j = 0; j < 6; j++)
                {
                    printf(" %c |", matriz[i][j]);
                }
                printf("\n");
                printf("---|---+---+---+---+---+---|\n");
            }
            tela = 0;
        }
        printf("\n\n\n");

        // printf("\033[2J"); // Limpa a tela (ANSI escape code)
        // printf("\033[H");  // Move o cursor para o canto superior esquerdo

        while (escrever)
        {
            if (gpio_get(BUTTON_A) == 0)
            {
                sleep_ms(50);
                if (contLinha < 6)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        azul(100);
                        apagado(0);
                    }
                    contLinha = contLinha + 1;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        vermelho(100);
                        apagado(0);
                    }
                    contLinha = 6;
                }
            }
            if (gpio_get(BUTTON_B) == 0)
            {
                sleep_ms(50);
                if (contColuna < 6)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        amarelo(100);
                        apagado(0);
                    }
                    contColuna = contColuna + 1;
                }
                else
                {
                    for (int i = 0; i < 4; i++)
                    {
                        rosa(100);
                        apagado(0);
                    }
                    contColuna = 6;
                }
            }
            if (gpio_get(BUTTON_J) == 0)
            {
                sleep_ms(50);
                for (int i = 0; i < 2; i++)
                {
                    verde(100);
                    apagado(0);
                }
                if (contLinha < 6 && contColuna < 6)
                {
                    letra = matriz[contLinha][contColuna];
                }
                if (contColuna == 6)
                {
                    letra = ' ';
                }
                if (contLinha == 6)
                {
                    letra = '\n';
                }

                contLinha = 0;
                contColuna = 0;
                printf("%c", letra);
            }
        }
    }
}
