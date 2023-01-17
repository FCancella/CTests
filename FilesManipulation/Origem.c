//Felipe Cancella - 2210487 - 33B
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define TAM 81

FILE* openFile(const char* file, const char* mode) {
	FILE* arq = fopen(file, mode);
	if (arq == NULL) {
		printf("erro na abertura do arquivo");
		exit(1);
	}
	return arq;
}

char* underline(char* nome) {
	if (*nome == '\0') {
		return nome;
	}
	else if (*nome == ' ') {
		*nome = '_';
	}
	return underline(nome + 1);
}

int maiorvalor(int* vet, float* media, int qnt) {
	int maior = 0, soma = 0;

	for (int i = 0; i < qnt; i++) {
		soma += *(vet + i);
		if (*(vet + i) > maior) {
			maior = *(vet + i);
		}
	}
	*media = (float)soma / qnt;
	return maior;
}

int main(void) {
	FILE* arqleitura = openFile("arq1.txt", "r");
	char cidade[TAM], nomearq[TAM];

	fscanf(arqleitura, " %[^:]: ", &cidade);
	underline(cidade);

	strcpy(nomearq, "data_");
	strcat(nomearq, cidade);
	strcat(nomearq, ".dat");

	FILE* datescrita = openFile(nomearq, "wb");
	char* sensor[TAM];
	int qntleituras;

	while (!feof(arqleitura)) {
		fscanf(arqleitura, " %[^,], %d leituras: ", &sensor, &qntleituras);
		fwrite(&qntleituras, sizeof(int), 1, datescrita);
		int leitura[100];
		for (int i = 0; i < qntleituras; i++) {
			fscanf(arqleitura, " %d ", leitura + i);
		}
		fwrite(leitura, sizeof(int), qntleituras, datescrita);
		printf("\t%s: gravado com sucesso em %s\n", &sensor, nomearq);
	}
	fclose(arqleitura);
	fclose(datescrita);

	FILE* datleitura = openFile(nomearq, "rb");
	int qnt, valores[100], tot;
	float media;

	printf("\nTESTE DE LEITURA DE ARQUIVO BINARIO:\n");
	while (fread(&qnt, sizeof(int), 1, datleitura) == 1) {
		printf("%d leituras: ", qnt);
		fread(valores, sizeof(int), qnt, datleitura);

		for (int i = 0; i < qnt; i++) {
			printf("%d ", *(valores + i));
		}

		tot = maiorvalor(valores, &media, qnt);
		printf("\n\tMax: %d | MEDIA: %.2f\n\n", tot, media);
	}
	fclose(datleitura);
	return 0;
}