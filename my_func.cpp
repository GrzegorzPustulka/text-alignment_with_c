#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bledy.cpp"

extern void bledy();
extern void bladDlugosciSlowa();

char* ladny_tekst()
{
	char znak;
	int ilosc_znakow = 0;
	int i;
	FILE* plik = fopen("text.txt", "r");

	if (plik == NULL)
	{
		bledy();
		exit(1);
	}

	while ((znak = getc(plik)) != EOF)
		ilosc_znakow++;

	rewind(plik);

	char* pom = (char*)malloc((ilosc_znakow) * sizeof(char) + 2);
	if (!pom)
	{
		bledy();
		exit(2);
	}

	i = 0;
	while ((znak = getc(plik)) != EOF)
	{
		pom[i] = znak;
		i++;
	}
	pom[i] = ' ';
	pom[i + 1] = 0;

	char* text = (char*)malloc((ilosc_znakow) * sizeof(char) +2);

	if (!text)
	{
		bledy();
		exit(3);
	}

	i = 0;
	int j = 0;
	while (pom[i] != 0)
	{
		if ((pom[i] == '\n' && pom[i + 1] == ' ' ) || (pom[i] == '\n' && pom[i + 1] == '\n'))
			i++;
		else if (pom[i] == '\n' && pom[i + 1] != ' ')
		{
			text[j] = ' ';
			j++;
			i++;
		}
		else if (pom[i] == '\t')
		{
			text[j] = ' ';
			j++;
			i++;
		}
		else if (pom[i] == ' ' && pom[i + 1] == '\n ')
			i++;
		else if (pom[i] != ' ')
		{
			text[j] = pom[i];
			i++;
			j++;
		}
		else if (pom[i] == ' ' && pom[i + 1] != ' ')
		{
			text[j] = ' ';
			i++;
			j++;
		}
		else
			i++;
	}

	text[j] = 0;

	if (pom)
		free(pom);
	pom = NULL;

	i = 0;
	int ilosc_znakow_finalnie = 0;
	while (text[i] != 0)
	{
		ilosc_znakow_finalnie++;
		i++;
	}

	char* koncowy_tekst = (char*)malloc((ilosc_znakow_finalnie) * sizeof(char) + 2);
	if (!koncowy_tekst)
	{
		bledy();
		exit(3);
	}

	i = 0;
	j = 0;

	while (text[i] != 0)
	{
		if (text[i] != ' ')
		{
			koncowy_tekst[j] = text[i];
			j++;
			i++;
		}
		else if (text[i] == ' ' && text[i + 1] == ' ')
			i++;
		else
		{
			koncowy_tekst[j] = text[i];
			j++;
			i++;
		}
	}
	koncowy_tekst[j] = 0;

	if (text)
		free(text);
	text = NULL;

	fclose(plik);
	return koncowy_tekst;
}

int ilosci_slow(char* text)
{
	int ilosc_slow = 0;
	int i = 0;
	while (text[i] != 0)
	{
		if (text[i] == ' ')
			ilosc_slow++;
		i++;
	}
	return ilosc_slow;
}

int* dlugosci_slow(int szerokosc, char* tab)
{
	int ilosc_slow = 0;
	int i = 0;
	int max = 0;
	while (tab[i] != 0)
	{
		if (tab[i] == ' ')
			ilosc_slow++;
		i++;
	}

	int* tab_pom = (int*)malloc(ilosc_slow * sizeof(int));
	if (!tab_pom)
	{
		bledy();
		exit(3);
	}

	i = 0;
	int j = 0;
	while (tab[i] != NULL)
	{
		if (tab[i] != ' ')
			max++;
		else
		{
			tab_pom[j] = max;
			j++;
			max = 0;
		}
		i++;
	}

	max = 0;
	for (i = 0; i < ilosc_slow; i++)
		if (tab_pom[i] > max)
			max = tab_pom[i];

	if (max > szerokosc)
		bladDlugosciSlowa(max);
	
	return tab_pom;
}

void wyrownanie_do_prawej(char* text, int* dlugosci_wyrazow, int szerokosc, int ilosc_slow)
{
	//printf("%s\n\n\n", text);
	
	int i;
	int ilosc_znakow_w_wierszu = 0;
	int ilosc_wyrazow_w_wierszu = 0;
	float ilosc_spacji_w_wierszu = 0;
	for (i = 1; i <= szerokosc; i++)
	{
		printf("%d", i % 10);
	}
	printf("\n");

	int j = 0;
	i = 0;
	int c;
	int x = 0;
	int var = 1;
	while (1)
	{
		if (j == ilosc_slow)
			break;

		ilosc_znakow_w_wierszu += dlugosci_wyrazow[j];
		j++;
		ilosc_wyrazow_w_wierszu++;

		if (j == ilosc_slow)
		{

			while (text[i] != NULL)
			{
				printf("%c", text[i]);
				i++;
			}
			break;
		}
			
		if (ilosc_znakow_w_wierszu == szerokosc && ilosc_wyrazow_w_wierszu == 1)
		{
			while (text[i] != ' ')
			{
				printf("%c", text[i]);
				i++;
			}

			i++;
			ilosc_wyrazow_w_wierszu = 0;
			ilosc_znakow_w_wierszu = 0;
			printf("\n");

		}
		else
		{
			while (ilosc_znakow_w_wierszu < szerokosc)
			{
				if (j == ilosc_slow)
				{
					var = 0;
					break;
				}

				ilosc_znakow_w_wierszu += dlugosci_wyrazow[j];
				j++;
				ilosc_wyrazow_w_wierszu++;

 			}
			if (var)
			{
				j--;
				ilosc_znakow_w_wierszu -= dlugosci_wyrazow[j];
				ilosc_wyrazow_w_wierszu--;
			}
			if (ilosc_znakow_w_wierszu + ilosc_wyrazow_w_wierszu - 1 == szerokosc)
			{
				for (c = 0; c < szerokosc; c++)
				{
					printf("%c", text[i]);
					i++;
				}

				printf("\n");
				i++;
				ilosc_wyrazow_w_wierszu = 0;
				ilosc_znakow_w_wierszu = 0;

			}
			else
			{
				while (1)
				{
					if (ilosc_wyrazow_w_wierszu == 1)
					{
						while (text[i] != ' ')
						{
							printf("%c", text[i]);
							x++;
							i++;
						}

						for (c = x; c < szerokosc; c++)
							printf(" ");

						printf("\n");
						i++;
						ilosc_znakow_w_wierszu = 0;
						ilosc_wyrazow_w_wierszu = 0;
						ilosc_spacji_w_wierszu = 0;
						x = 0;
						break;
					}
					else
					{
						ilosc_spacji_w_wierszu = float((szerokosc - ilosc_znakow_w_wierszu)) / (ilosc_wyrazow_w_wierszu - 1);

						if (ilosc_spacji_w_wierszu - int(ilosc_spacji_w_wierszu) == 0)
						{
							while (x != szerokosc)
							{
								if (text[i] != ' ')
								{
									printf("%c", text[i]);
									i++;
									x++;
								}
								else
								{
									for (c = 0; c < ilosc_spacji_w_wierszu; c++)
									{
										printf(" ");
										x++;
									}

									i++;
								}
							}

							i++;
							x = 0;
							printf("\n");
							ilosc_znakow_w_wierszu = 0;
							ilosc_spacji_w_wierszu = 0;
							ilosc_wyrazow_w_wierszu = 0;
							break;
						}
						else
						{
							j--;
							ilosc_znakow_w_wierszu -= dlugosci_wyrazow[j];
							ilosc_wyrazow_w_wierszu--;
						}
					}
				}
			}
		}

	}

	if(text)
		free(text);
	text = NULL;

	if(dlugosci_wyrazow)
		free(dlugosci_wyrazow);
	dlugosci_wyrazow = NULL;
}
