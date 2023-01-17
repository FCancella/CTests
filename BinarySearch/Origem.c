//Felipe Cancella - 2210487 - 33B

#define tot 9
#include "stdio.h"

struct bioD
{
	float altura;
	float peso;
};
typedef struct bioD bioData;

struct paciente
{
	char nome[51];
	bioData medidas;
};
typedef struct paciente Patient;

int compara(float altura, Patient * b) {
	if (altura < b->medidas.altura)
		return -1;
	else if (altura > b->medidas.altura)
		return 1;
	else
		return 0;
}

//int buscaBin(Patient** v, int n, float alt) {
//	int meio, resp;
//	int ini = 0;
//	int fim = n - 1;
//	while (ini <= fim) {
//		meio = (ini + fim) / 2;
//		resp = compara(alt, v[meio]);
//
//		if (resp > 0)
//			ini = meio + 1;
//		else if (resp < 0)
//			fim = meio - 1;
//		else {
//			int ind = meio;
//			while (ind>=0 && v[ind]->medidas.altura == alt) {
//					ind--;
//			}
//			return ++ind;
//		}
//	}
//	return -1;
//}


int buscaBin(Patient** v, int t, float alt) {
	int meio, resp;
	int ini = 0;
	int fim = t - 1;
	while (ini <= fim) {
		meio = (ini + fim) / 2;
		resp = compara(alt, v[meio]);
		if (resp < 0)
			fim = meio - 1;
		else if (resp > 0)
			ini = meio + 1;
		else {
			int ind = meio;
			while (ind >= 0 && v[ind]->medidas.altura == alt) {
				ind--;
			}
			return ++ind;
		}
	}
	return -1;
}


void imprimeVetor(int n, Patient** v) {
	for (int i = 0; i < n; i++) {
		printf("%-10s %.2f  %.1f\n", v[i]->nome, v[i]->medidas.altura, v[i]->medidas.peso);
	}
}

//void buscaAltura(Patient** v, int n, float alt) {
//	int ind = buscaBin(v, n, alt);
//
//	if (ind < 0)
//		printf("BUSCA NAO SUCEDIDA:  Nao existe pacientes com a altura %.2f\n", alt);
//	else {
//		printf("Menor peso com altura %.2f:  %s \t %.2f  %.1f\n", v[ind]->medidas.altura, v[ind]->nome, v[ind]->medidas.altura, v[ind]->medidas.peso);
//	}
//}


void buscaAltura(Patient** v, int t, float alt) {
	int ind = buscaBin(v, t, alt);
	if (ind < 0) {
		printf("BUSCA NAO SUCEDIDA:  Nao existe pacientes com a altura %.2f\n", alt);
	}
	else {
		printf("Menor peso com altura %.2f:  %s \t %.2f  %.1f\n", v[ind]->medidas.altura, v[ind]->nome, v[ind]->medidas.altura, v[ind]->medidas.peso);
	}
}

int main(void) {
	Patient d[] =
	{{"Lucas",{1.60,50}}, {"Alberto",{1.60,65}}, {"Joao",{1.60,72}}, {"Antonio",{1.70,60}},
	{"Pedro",{1.70,70}},{"Luiz",{1.90,80}}, {"Pietro",{1.90,95}}, {"Julia",{2.0,75}}, {"Bruna",{2.0,90}}};

	Patient* v[] = { d, d + 1, d + 2, d + 3, d + 4, d + 5, d + 6, d + 7, d + 8 };

	printf("Pacientes:\n");
	imprimeVetor(tot, v);
	printf("-\n");

	buscaAltura(v, tot, 1.70);
	buscaAltura(v, tot, 1.60);
	buscaAltura(v, tot, 1.90);
	buscaAltura(v, tot, 2.00);
	buscaAltura(v, tot, 1.20);
	buscaAltura(v, tot, 1.80);

	return 0;
}