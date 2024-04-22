#include "Header.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream in("alfabet.txt");
	citeste_alfabet(in);
	in.close();

	// pt Criptare afin? pe blocuri- Criptare

	int** a = new int* [2];
	int* b = new int[2];
	for (int i = 0; i < 2; i++)
		a[i] = new int[2];
	a[0][0] = 2;
	a[0][1] = 3;
	a[1][0] = 7;
	a[1][1] = 8;
	b[0] = 0;
	b[1] = 0;
	cheieAfina k;
	k.n = 2;
	k.a = calcul_matr_inv_Zn(a, k.n, N);
	k.b = b;
	ofstream out("destinatie.txt");
	ifstream in2("sursa.txt");//fisierul cu textul sursa
	criptareAfina(in, out, k);
	in2.close(); out.close();
}