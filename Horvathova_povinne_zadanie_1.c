#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


char nahodny_polynom(float *q,char rad,char k){
	char i,j;
	float min_rand,max_rand,range,koeficienty[255],K[255],sucin;
	int korene,pocet;
	
	min_rand=-5.0;
	max_rand=5.0;
	pocet=0;
	sucin=1.;
	range=max_rand-min_rand;
	printf("KORENE:\n");
	for (i='0';i<k;i++){
		K[i]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
		printf("%.1lf\n",K[i]);
		sucin=sucin*K[i];
		pocet++;
	}	
	
	pocet++;
	printf("%.2lf\n",sucin);
	koeficienty['0']=1.;
	printf("0.koeficient %.1lf\n",koeficienty['0']);
	for (i='1';i<=k;i++){
		koeficienty[i]=pow(-1,pocet-i);
		printf("%c koeficient%.1lf\n",i,koeficienty[i]);	
	}	
}


main(){
	char polynom,stupen,koren;
	float *smernik;
	int rad,pom;

	srand(time(NULL));
	printf("Zadaj najvacsi stupen polynoumu:");
	scanf(" %c",&stupen);
	printf("Zadaj pocet realnych korenov polynomu:");
	scanf(" %c",&koren);
	rad=(int)stupen;
	pom=(int)koren;
	printf("korene %d\n",pom);
	printf("stupen %d\n",rad);
	
	printf("PO DELENI %d\n",pom%2);

	if(stupen=='0'){
		while(koren!='0'&& koren!='1'){
				printf("Zadaj znovu:\n");
				scanf(" %c",&koren);	
		}	
	}	
	else if(stupen=='1'){
		while(koren!='1'){
			printf("Zadaj pocet realnych korenov polynomu:\n");
			scanf(" %c",&koren);	
		}
	}
	else if(rad%2==0){
		while((pom%2)!=0){
		 	printf("Zadaj pocet realnych korenov polynomu:\n");
		 	scanf(" %c",&koren);
			pom=(int)koren;
		}
		while(koren>stupen){
		 	printf("Zadaj pocet realnych korenov polynomu:\n");
		 	scanf(" %c",&koren);
		}
		while(koren=='0'){
			printf("Zadaj pocet realnych korenov polynomu:\n");
		 	scanf(" %c",&koren);
		}
	}		
	else if(rad%2==1){
		while((pom%2)!=1){
			printf("Zadaj pocet realnych korenov polynomu:\n");
		 	scanf(" %c",&koren);
			pom=(int)koren;	
		}
		while(koren>stupen){
		 	printf("Zadaj pocet realnych korenov polynomu:\n");
		 	scanf(" %c",&koren);
		}
	}				
	polynom=nahodny_polynom(&smernik,stupen,koren);
}
