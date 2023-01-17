//Felipe Cancella - 2210487
#include <stdio.h>

int substitui(char* v, char letraSai, char letraEntra) {
	if (*v) {
		if (*v == letraSai) {
			*v = letraEntra;
			return 1 + substitui((v + 1), letraSai, letraEntra);
		}
		return substitui((v + 1), letraSai, letraEntra);
	}
	return;
}

int conta(char* v) {
	if (*v) {
		if (*v >= 'A' && *v <= 'Z' || *v >= 'a' && *v <= 'z')
			return conta((v + 1));
		return 1 + conta((v + 1));
	}
	return;
}