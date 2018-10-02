#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//Programa Principal
int main(){
    int i          = 0;
    int nmax       = 0;
    int quantidade = 0;
    int num        = 0;
    ofstream myfile;
    myfile.open ("RandNum.txt");

	cout << "Digite quantos numeros serao gerados: ";
	cin  >> quantidade;
	cout << endl << "Digite o numero maximo que sera possivel gerar: ";
	cin  >> nmax;
	cout << endl << "Gerando " << quantidade << " valores aleatorios:" << endl << endl;

	srand(time(NULL));
	for (i=0; i < quantidade; i++){
    num = rand() % nmax;
    cout   << num << endl;
    myfile << num << endl;
	}
	myfile.close();

	system("pause");

	return 0;
}
