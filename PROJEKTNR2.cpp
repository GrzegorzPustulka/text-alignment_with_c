#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "my_func.cpp"
#include "bledy.cpp"

extern char* ladny_tekst();
extern int* dlugosci_slow();
extern void wyrownanie_do_prawej();
extern int ilosci_slow();
extern void bladSzerokosci();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Polish");
	int szerokosc;
	printf("Podaj szerokosc linii: ");
	scanf("%d", &szerokosc);

	if (szerokosc > 0) 
	{
		char* text = ladny_tekst();
		int* dlugosci_wyrazow = dlugosci_slow(szerokosc, text);
		int ilosc_slow = ilosci_slow(text);
		wyrownanie_do_prawej(text, dlugosci_wyrazow, szerokosc, ilosc_slow);
	}
	else
		bladSzerokosci();

	return 0;
}

