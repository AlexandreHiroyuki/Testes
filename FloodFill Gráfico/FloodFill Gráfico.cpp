/*************************************/
/* FloodFill Grafico		     */
/* Created by Alexandre Hiroyuki     */
/*************************************/
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

struct coord {
	int linha;
	int coluna;
};

coord coordIni;
char  figura[52][52] = { {},{} };
int   linha = 0, coluna = 0;
bool  aleatorio = false;
double repeat = 0.0;

void grafico(int espera) {
	system("cls");
	cout << "Gerando Figura: " << endl;
	for (int i = 0; i < linha + 2; i++) {
		for (int j = 0; j < coluna + 2; j++) {
			cout << figura[i][j];
		}
		cout << endl;
	}
	Sleep(espera);
}

void inicializar() {
	char aleatorioPergunta = 'a';
	system("cls");
	cout << "Brincando com Flood Fill!" << endl
		 << "Declare o tamanho da Tabela! Minimo de 3x3 Maximo de 50x50" << endl;
	cout << "Digite a quantidade de linhas: ";
	cin	 >> linha;
	cout << "Digite a quantidade de colunas: ";
	cin  >> coluna;
	cout << "Digite as coordenadas de inicio: " << endl
		 << "Exemplo: <linha> <coluna> " << endl
		 << "A coordenada deve estar dentro da area da Tabela" << endl;
FAIL:
	cin  >> coordIni.linha >> coordIni.coluna;
	if (coordIni.linha > linha || coordIni.linha < 1 || coordIni.coluna < 1 || coordIni.coluna > coluna) {
		cout << "A coordenada nao existe!" << endl;
		goto FAIL;
	}
	
	cout << "O preenchimento sera aleatorio?" << endl
		 << "Digite 's' para sim e 'n' para nao" << endl;
INVALIDA:
	cin  >> aleatorioPergunta;
	if (aleatorioPergunta == 's') {
		aleatorio = true;
	}
	else if (aleatorioPergunta == 'n') {
		aleatorio = false;
	}
	else {
		cout << "Resposta invalida!" << endl;
		goto INVALIDA;
	}
	for (int i = 0; i < linha + 2; i++)
		for (int j = 0; j < coluna + 2; j++)
			figura[i][j] = '_';
	grafico(1000);
	for (int i2 = 0; i2 <= coluna; i2++) {
		figura[linha + 1][i2] = '#';
		figura[0][i2] = '#';
		grafico(10);
	}
	for (int i3 = 0; i3 <= linha + 1; i3++) {
		figura[i3][coluna + 1] = '#';
		figura[i3][0] = '#';
		grafico(10);
	}

	grafico(1000);
};

void floodFill(int x, int y) {
	if (figura[x][y] == '_') {
		figura[x][y] = '%';
		grafico(100);
		floodFill(x + 1, y + 1);
		floodFill(x + 1, y);
		floodFill(x + 1, y - 1);
		floodFill(x, y + 1);
		floodFill(x, y - 1);
		floodFill(x - 1, y + 1);
		floodFill(x - 1, y);
		floodFill(x - 1, y - 1);
	}
};

void randFill(int x2, int y2) {
	if (figura[x2][y2] == '_') {
		figura[x2][y2] = '%';
		
		grafico(100);
		int sorteio = rand() % 7;;
		//for (int i = 0; i < 2 ; i++) {
		DENOVO:
			sorteio = rand() % 7;
			switch (sorteio) {
			case 0:
				if (figura[x2 + 1][y2 + 1] != '_')
					goto DENOVO;
				randFill(x2 + 1, y2 + 1);
				break;
			case 1:
				if (figura[x2 + 1][y2] != '_')
					goto DENOVO;
				randFill(x2 + 1, y2);
				break;
			case 2:
				if (figura[x2 + 1][y2 - 1] != '_')
					goto DENOVO;
				randFill(x2 + 1, y2 - 1);
				break;
			case 3:
				if (figura[x2][y2 + 1] != '_')
					goto DENOVO;
				randFill(x2, y2 + 1);
				break;
			case 4:
				if (figura[x2][y2 - 1] != '_')
					goto DENOVO;
				randFill(x2, y2 - 1);
				break;
			case 5:
				if (figura[x2 - 1][y2 + 1] != '_')
					goto DENOVO;
				randFill(x2 - 1, y2 + 1);
				break;
			case 6:
				if (figura[x2 - 1][y2] != '_')
					goto DENOVO;
				randFill(x2 - 1, y2);
				break;
			case 7:
				if (figura[x2 - 1][y2 - 1] != '_')
					goto DENOVO;
				randFill(x2 - 1, y2 - 1);
			default:
				break;
			}
		//}
	}
};

int main(){
	srand(time(NULL));
	char  resposta = 'a';
//	Loop
	while (true) {
		inicializar();
		if (aleatorio)
			randFill(coordIni.linha, coordIni.coluna);
		else
			floodFill(coordIni.linha, coordIni.coluna);
//		Final
		cout << "Deseja fazer mais uma vez?" << endl
			<< "Digite 's' para sim e 'n' para nao" << endl;
		cin >> resposta;
	REPEAT:
		if (resposta == 's') {
			continue;
		}
		else if (resposta == 'n') {
			break;
		}
		else {
			cout << "Resposta invalida!" << endl;
			goto REPEAT;
		}
	}
    return 0;
}

