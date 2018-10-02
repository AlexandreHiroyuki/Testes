//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
//Variáveis
int i;
int nmax;
int quantidade;
//Programa Principal
int main(){
	printf("Digite quantos numeros serao gerados:");
	scanf("%i",&quantidade);
	printf("Digite o numero maximo que sera possivel gerar:");
	scanf("%i",&nmax);
	printf("Gerando %i valores aleatorios:\n\n",quantidade);
	srand(time(NULL));
	for (i=0; i < quantidade; i++){
	printf("%d ", rand() % nmax);
	}
	getch();

	return 0;
}
