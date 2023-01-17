//Felipe Cancella - 2210487
#include <stdio.h>
#include "auxiliares.h"

int main(void) {
	char frase[] = "rapadura";
	int diferentes, trocados;

	printf("Original: %s\n-\n", frase);

	trocados = substitui(&frase, 'a', '_');
	printf("Depois da substituicao: %s\n", frase);
	printf("\nCaracteres trocados: %d\n", trocados);

	diferentes = conta(&frase);
	printf("Caracteres diferentes de letras: %d\n\n ", diferentes);

	return 0;
}