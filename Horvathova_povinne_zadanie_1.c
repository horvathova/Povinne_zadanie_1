#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FAIL '0'
#define OK '1'

double min_rand = -5.0;
double max_rand = 5.0;

double* generuj_korene_vsucine(char k) {
	int i;

	double *korene = malloc(k * sizeof(double));
	double range = max_rand - min_rand;

	for (i = 0; i<(int)k; i++) {
		korene[i] = range*((((double)rand()) / (double)RAND_MAX)) + min_rand;
	}
	return korene;
}

double* generuj_korenovy_polynom(char rad, char k, double *korene){
	int i,j;
	double *A, *B, *POLY;

	A = calloc(k, sizeof(double));
	B = calloc(k + 1, sizeof(double));
	POLY = calloc(k + 1, sizeof(double));

	A[0] = 1;
	A[1] = korene[0];
	for (j = 1; j<(int)k; j++) {
		for (i = 0; i<(int)k + 1; i++) {
			B[0] = 0;
			B[i + 1] = korene[j] * A[i];
			POLY[i] = A[i] + B[i];
		}

		for (i = 0; i<(int)k + 1; i++) {
			A[i] = POLY[i];
		}
	}

	return POLY;
}

double* generuj_zvysny_polynom(char rad, char k){
	int pocet = rad - k;
	double *KVADR = calloc(pocet, sizeof(double));
	double range = max_rand - min_rand;

	KVADR[0] = 1;
	KVADR[pocet] = range*((double)rand()) / ((double)RAND_MAX) + 0.;
	return KVADR;
}

double* vynasob_polynomy(double *prvy, double *druhy, char rad, char k){
	double *final=malloc(rad);
	int i, j;

	for(i=0; i<(char)rad+k;i++){
		final[i] = 0;
	}

	for (i = 0; i<=(int)k; i++) {
		for (j = 0; j<=(int)rad-k; j++) {
			final[i + j] += prvy[i] * druhy[j];
		}
	}
	return final;
}

char nahodny_polynom(double *q, char rad, char k) {
	double *korene, *korenovy_polynom, *zvysny_polynom;
	int i;
	unsigned char pocet;
	double range = max_rand - min_rand;

	if (rad == 0) {
		q[0] = range*((((double)rand()) / (double)RAND_MAX)) + min_rand;
		return OK;
	}

	q[0] = 1;
	if (rad == 1) {
		if (k == 0) {
			return FAIL;
		}

		else {
			q[1] = range*((((double)rand()) / (double)RAND_MAX)) + min_rand;
			return OK;
		}
	}

	if ((int)rad % 2 == 0) {
		if ((int)k % 2 == 1) {
			return FAIL;
		}

		else if (k == 0) {
			q[rad] = range*((double)rand()) / ((double)RAND_MAX) + 0.;
			return OK;
		}
	}

	if ((int)rad % 2 == 1) {
		if ((int)k % 2 == 0) {
			return FAIL;
		}

		if (k == 1) {
			q[rad] = range*((((double)rand()) / (double)RAND_MAX)) + min_rand;
			return OK;
		}
	}

	korene = generuj_korene_vsucine(k);
	korenovy_polynom = generuj_korenovy_polynom(rad, k, korene);

	if (k<rad) {
		zvysny_polynom = generuj_zvysny_polynom(rad, k);
		q=vynasob_polynomy(korenovy_polynom, zvysny_polynom, rad, k);
		return OK;
	}

	return OK;
}

int main() {
	char rad, k, polynom;
	int stupen, koren;
	double *koeficienty;

	srand(time(NULL));
	printf("Zadaj najvacsi stupen polynoumu:");
	scanf("%d", &stupen);
	while (stupen<0 || stupen>255) {
		printf("Znovu zadaj najvacsi stupen polynoumu:");
		scanf("%d", &stupen);
	}

	printf("Zadaj pocet realnych korenov polynomu:");
	scanf("%d", &koren);
	while (koren<0 || stupen>255 || koren>stupen) {
		printf("Znovu zadaj pocet realnych korenov polynomu:");
		scanf("%d", &koren);
	}

	if ((koeficienty = calloc(stupen + 1, sizeof(double))) == NULL) {
		return FAIL;
	}

	rad = (char)stupen;
	k = (char)koren;
	polynom = nahodny_polynom(koeficienty, rad, k);
	printf("hodnota: %c\n", polynom);
	getchar();
	getchar();
	//free(koeficienty);
}
