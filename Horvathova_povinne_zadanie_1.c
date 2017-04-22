#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define MAX 255

char nahodny_polynom(float *q,char rad,char k){
	char i,j;
	float min_rand,max_rand,range,koeficienty[MAX],K[MAX],A[MAX],B[MAX];
	int korene,pocet_k,stupen,pom;
	
	min_rand=-5.0;
	max_rand=5.0;
	pocet_k=0;
	range=max_rand-min_rand;
	stupen=(int)rad;
	pom=(int)k;
	
	if(pom>stupen){
		return printf("FAILED");
	}
	
	else {
		if(rad=='0'){
			while(k!='0'&& k!='1'){
				return printf("FAILED");
			}	
		}	
	else if(rad=='1'){
		while(k!='1'){
			return printf("FAILED");	
		}
	}
	else if(stupen%2==0){
		while((pom%2)!=0){
		 	return printf("FAILED");
		}
		while(k=='0'){
			return printf("FAILED");
		}
	}		
	else if(stupen%2==1){
		while((pom%2)!=1){
			return printf("FAILED");
		}
	}
			
	printf("KORENE:\n");
	for(i='0';i<k;i++){
		K[i]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
		printf("%.3lf\n",K[i]);
		pocet_k++;
	}
	
	}	
	
	A['0']=1.;
	A['1']=K['0'];
	B['0']=0.;
	
	printf("\n");
	printf("%.1lf ",A['0']);
	printf("%.1lf\n",A['1']);
	
	printf("VYMENA\n");
	printf("%.3lf ",B['0']);
	for(i='1';i<k;i++){
		B[i]=A[i-1];
		printf("%.3lf ",B[i]);
	}	
	printf("\n");
	for(i='0';i<k;i++){
		B[i]=K['1']*B[i];
		printf("%.3lf ",B[i]);
	}
	printf("\nVysledok\n");
	for(i='0';i<k;i++){
		koeficienty[i]=A[i]+B[i];
		printf("%.3lf ",koeficienty[i]);
	}
}


main(){
	char stupen,koren,polynom;
	float *smernik;

	srand(time(NULL));
	printf("Zadaj najvacsi stupen polynoumu:");
	scanf(" %c",&stupen);
	printf("Zadaj pocet realnych korenov polynomu:");
	scanf(" %c",&koren);
	
	polynom=nahodny_polynom(&smernik,stupen,koren);
}
