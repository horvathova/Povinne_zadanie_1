#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FAIL '0'
#define OK '1'

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

double* generuj_korenovy_polynom(char k, double *korene) {
	int i, j;
	double *A, *B, *POLY;

	A = calloc(k+1, sizeof(double));
	B = calloc(k + 1, sizeof(double));
	POLY = calloc(k + 1, sizeof(double));

	A[0] = 1;
	A[1] = korene[0];

	if (k == 1) {
		return A;
	}

	else {
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
	}

	/*free(A);
	free(B);*/
	return POLY;
}

double* vynasob_polynomy(double *prvy, double *druhy, char const stupen1, char const stupen2) {
	int i, j;
	double *final = calloc((stupen1 + stupen2+1), sizeof(double));

	for (i = 0; i <= (int)stupen1; i++) {
		for (j = 0; j <= (int)stupen2; j++) {
			final[i + j] += prvy[i] * druhy[j];
		}
	}
	return final;
}

double* generuj_komplex_polynom() {
	double a, b, c;
	int j;
	const double range = max_rand - min_rand;
	double *kvadraticky = malloc(3 * sizeof(double));

	a = range*((double)rand() / (double)RAND_MAX) + min_rand;
	if (a < 0) {
		c = -1 * (range + 5)*((double)rand() / (double)RAND_MAX) + min_rand;
	}
	else {
		c = (range + 5)*((double)rand() / (double)RAND_MAX) + 2*max_rand;
	}

	b = (range - 4)*((double)rand() / (double)RAND_MAX) + min_rand;
	while (b* b > 4 * a * c) {
		b = (range - 4)*((double)rand() / (double)RAND_MAX) + min_rand;
	}

	kvadraticky[0] = a;
	kvadraticky[1] = b;
	kvadraticky[2] = c;

	return kvadraticky;
}

double* generuj_zvysny_polynom(const char rad, const char k) {
	int pocet = rad - k;
	int kvadr = pocet / 2;
	int j = 4;
	bool prva_iter = true;

	double *pom = malloc(pocet * sizeof(double));
	double *pom2 = malloc(pocet * sizeof(double));
	double *kvadraticky = malloc(3 * sizeof(double));
	double *zvysny = malloc(pocet * sizeof(double));	
	
	if(pocet==2){
		return zvysny = generuj_komplex_polynom();
	}

	for (int i = 0; i < kvadr / 2; i++) {
		kvadraticky = generuj_komplex_polynom();
		pom2 = vynasob_polynomy(kvadraticky, kvadraticky, 2, 2);

		//toto zbehne len prvykrat, pretoze sa nic nenasobi, len sa nastavi zaciatocny polynom 
		if (prva_iter) {
			if(kvadr/2 !=1){
				pom = pom2;
			}

			//ak je potrebny zvysny polynom stupna 4
			else {
				zvysny = pom2;
			}

			prva_iter = false;
		}

		else {
			zvysny = vynasob_polynomy(pom2, pom, 4, j);
			pom = zvysny;
			j += 4;
		}
	}

	//ak potrebujeme neparny pocet kvadratickych polynomov
	if (kvadr % 2 != 0) {
		kvadraticky = generuj_komplex_polynom();
		pom = zvysny;

		zvysny = vynasob_polynomy(kvadraticky, pom, 2, pocet -2);
	}

	/*free(kvadraticky);
	free(pom);
	free(pom2);*/

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
	//free(koeficienty);
}
