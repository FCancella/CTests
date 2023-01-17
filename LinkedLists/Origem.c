//Felipe Cancella - 2210487 - 33B
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define HASHSIZE 10

struct nlist
{
	char* name;
	char* defn;
	struct nlist* next;
};


unsigned int hash(char* s)
{
	unsigned int hashval;
	for (hashval = 0; *s; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

char* copiaString(char* string) {
	char* vet = (char*)malloc(sizeof(char) * (strlen(string) + 1));
	if (vet == NULL) return NULL;
	strcpy(vet, string);
	return vet;
}

struct nlist* lookup(char* nome, struct nlist** hashtab) {
	unsigned int indice = hash(nome);
	struct nlist* p;
	
	for (p = hashtab[indice]; p != NULL && strcmp(p->name, nome) != 0; p = p->next) {
	}

	return p;
}

struct nlist* install(char* nome, char* def, struct nlist** hashtab) {
	struct nlist* enderecoExistente = lookup(nome, hashtab);

	if (enderecoExistente != NULL) {

		free(enderecoExistente->defn);

		char* defv2 = copiaString(def);
		enderecoExistente->defn = defv2;

		return enderecoExistente;
	}
	else {
		unsigned int indice = hash(nome);

		struct nlist* nova = (struct nlist*)malloc(sizeof(struct nlist));
		if (nova == NULL) return NULL;

		char* defv = copiaString(def);
		char* nomev = copiaString(nome);

		nova->name = nomev;
		nova->defn = defv;
		nova->next = hashtab[indice];

		hashtab[indice] = nova;
		return nova;
	}
}


void buscaDef(char* nome, struct nlist* hashtab) {
	struct nlist* encontrado = lookup(nome, hashtab);
	if (encontrado == NULL) {
		printf("Uma definicao para %s nao foi encontrada\n", nome);
	}
	else {
		printf("O teste de procura de %s encontrou: %s\n", nome, encontrado->defn);
	}
	return;
}

int main(void) {
	struct nlist* hashtab[HASHSIZE];
	char* symbols[] = { "PI", "TRUE", "FALSE" , "MAXSIZE", "G", "EPS", "MSG1", "PI"};
	char* defs[] = {"3.14", "1", "0", "81", "9.81", "0.001", "...yes ok", "3.14159"};

	for (int i = 0; i < HASHSIZE; i++) {
		hashtab[i] = NULL;
	}

	for (int i = 0; i < 8; i++) {
		struct nlist* endereco = install(symbols[i], defs[i], hashtab);
		if (endereco == NULL) {
			printf("Erro de memoria");
			return NULL;
		}
	}

	//print the hashtab pointers vector withou changing it
	for (int i = 0; i < HASHSIZE; i++) {
		struct nlist* copy = hashtab[i];
		printf("%d -", i);
		while (copy)
		{
			while (copy->next) {
				printf(" %s -", copy->name);
				copy = copy->next;
			}
			printf(" %s -", copy->name);
			copy = copy->next;

		}
		printf(" NULL");
		printf("\n");
	}


	printf("\n\n-------- Teste de busca --------\n\n");

	buscaDef("TRUE", hashtab);
	buscaDef("PI", hashtab);
	buscaDef("MAXSIZE", hashtab);
	buscaDef("MSG1", hashtab);
	buscaDef("G", hashtab);
	buscaDef("PI", hashtab);
	buscaDef("BETA", hashtab);

	for (int i = 0; i < HASHSIZE; i++) {
		if (hashtab[i] != NULL) {
			while (hashtab[i] != NULL)
			{
				free(hashtab[i]->name);
				free(hashtab[i]->defn);

				struct nlist* endereco = hashtab[i]->next;
				free(hashtab[i]);

				hashtab[i] = endereco;
			}
		}
	}

	return;
}
	