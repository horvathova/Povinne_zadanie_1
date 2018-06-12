#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FAIL '0'
#define OK   '1'

double min_rand = -3.0;
double max_rand = 3.0;

double* generuj_korene_vsucine(char k) {
	int i;
	double *korene = malloc(k * sizeof(double));
	double range = max_rand - min_rand;

	for (i = 0; i<(int)k; i++) {
		korene[i] = range*((double)rand() / (double)RAND_MAX) + min_rand;
	}

	return korene;
}

double* vynasob_polynomy(double *prvy, double *druhy, char const stupen1, char const stupen2) {
	int i, j;
	double *final = calloc((stupen1 + stupen2 + 1), sizeof(double));

	for (i = 0; i <= (int)stupen1; i++) {
		for (j = 0; j <= (int)stupen2; j++) {
			final[i + j] += prvy[i] * druhy[j];
		}
	}

	return final;
}

double* generuj_korenovy_polynom(char k, double *korene) {
	double *A = malloc(k * sizeof(double));
	double B[2];
	double *vysledny = malloc((k + 1) * sizeof(double));
	int i, j;

	A[0] = 1.;
	A[1] = korene[0];

	if (k == 1) {
		return A;
	}
	else {
		B[0] = 1.;

		for (i = 1; i < k; i++) {
			B[1] = korene[i];
			vysledny = vynasob_polynomy(A, B, i, 1);

			if (i != k) {
				A = vysledny;
			}
			else {
				free(A);
			}
		}
	}
	
	return vysledny;
}

double* generuj_komplex_polynom() {
	double a, b, c;
	double *kvadraticky = malloc(3 * sizeof(double));

	a = (max_rand*((double)rand() / (double)RAND_MAX)) + max_rand;		//  3 az 6
	c = (max_rand*((double)rand() / (double)RAND_MAX)) + max_rand;		//  3 az 6
	b = (max_rand + 1)*((double)rand() / (double)RAND_MAX);             // 0 az 4

	kvadraticky[0] = a;
	kvadraticky[1] = b;
	kvadraticky[2] = c;

	return kvadraticky;
}

double* generuj_zvysny_polynom(const char rad, const char k) {
	int pocet = rad - k;
	int kvadr = pocet / 2;
	int j = 4;
	int i;
	bool prva_iter = true;
	double *pom;
	double *pom2 = malloc(pocet * sizeof(double));
	double *kvadraticky = malloc(3 * sizeof(double));
	double *zvysny = malloc(pocet * sizeof(double));

	if (pocet == 2) {
		return zvysny = generuj_komplex_polynom();
	}

	kvadraticky = generuj_komplex_polynom();
	pom2 = vynasob_polynomy(kvadraticky, kvadraticky, 2, 2);
	
	if (kvadr / 2 != 1) {
		pom = pom2;
	}

	else if (pocet == 4) {
		return pom2;
	}

	else {	//ak je potrebny zvysny polynom stupna 4
		zvysny = pom2;
		pom = zvysny;
	}

	for (i = 1; i < kvadr / 2; i++) {
		kvadraticky = generuj_komplex_polynom();
		pom2 = vynasob_polynomy(kvadraticky, kvadraticky, 2, 2);
		zvysny = vynasob_polynomy(pom2, pom, 4, j);
		pom = zvysny;
		j += 4;
	}

	//ak potrebujeme neparny pocet kvadratickych polynomov
	if (kvadr % 2 != 0) {
		kvadraticky = generuj_komplex_polynom();
		pom = zvysny;
		zvysny = vynasob_polynomy(kvadraticky, pom, 2, pocet - 2);
	}

	free(kvadraticky);
	free(pom2);

	return zvysny;
}

char nahodny_polynom(double *q, char rad, char k) {
	double *korene, *korenovy_polynom, *zvysny_polynom;
	int i, pocet;
	double range = max_rand - min_rand;

	if (rad == 0) {
		q[0] = range*((((double)rand()) / (double)RAND_MAX)) + min_rand;
		printf("Vysledny polynom\n%.3lfx^%d", q[0], rad);
		return OK;
	}

	if ((int)rad % 2 == 0) {
		if ((int)k % 2 == 1) {
			return FAIL;
		}
		else if (k == 0) {
			q[0] = 1.;
			q[rad] = range*((double)rand()) / ((double)RAND_MAX) + 0.;
			printf("Vysledny polynom\n%.3lfx^%d %.3lfx^%d", q[0], rad, q[rad], k);
			return OK;
		}
	}

	if ((int)rad % 2 == 1) {
		if ((int)k % 2 == 0) {
			return FAIL;
		}
	}

	korene = generuj_korene_vsucine(k);
	printf("Vygenerovane korene: ");

	for (i = 0; i < k; i++) {
		printf("%f ", korene[i]);
	}

	printf("\n");
	korenovy_polynom = generuj_korenovy_polynom(k, korene);
	printf("\nVYGENEROVANY POLYNOM %d STUPNA\n", k);

	for (i = 0; i <= (int)k; i++) {
		printf("%.3lf ", korenovy_polynom[i]);
	}

	if (k < rad) {
		zvysny_polynom = generuj_zvysny_polynom(rad, k);
		printf("\nZVYSNY POLYNOM %d STUPNA\n", rad - k);

		for (i = 0; i <= (int)rad - k; i++) {
			printf("%.3lf ", zvysny_polynom[i]);
		}

		pocet = (int)rad;
		printf("\nVYNASOBENE POLYNOMY STUPNA %d a %d\n", k, rad - k);
		q = vynasob_polynomy(korenovy_polynom, zvysny_polynom, k, rad - k);

		for (i = 0; i <= (int)rad; i++) {
			printf("%.3lfx^%d ", q[i], pocet);
			pocet--;
		}

		free(korene);
		free(korenovy_polynom);
		free(zvysny_polynom);
		
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
	printf("\nhodnota: %c\n", polynom);
	getchar();
	getchar();
	free(koeficienty);
}
