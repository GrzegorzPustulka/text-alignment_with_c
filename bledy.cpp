#pragma once
#include <string.h>

void bledy()
{
	int errnum;
	errnum = errno;
	fprintf(stderr, "numer b��du: %d\n", errno);
	fprintf(stderr, "numer b��du: %s\n", strerror(errnum));
}
void bladSzerokosci()
{
	fprintf(stderr, "Szerokosc musi byc dodatnia\n");
	exit(2);
}
void bladDlugosciSlowa(int max)
{
	fprintf(stderr, "najdluzsze slowo ma %d znakow\n", max);
	fprintf(stderr, "wiec podana szerokosc nie zmiesci najdluzszego slowa");
	exit(3);
}