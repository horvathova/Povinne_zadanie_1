#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 255

char nahodny_polynom(float *q,char rad,char k){
	char return_value;
	float min_rand,max_rand,range,koeficienty[MAX],K[MAX],A[MAX],B[MAX];
	int i,j,korene,stupen,pom;
	
	min_rand=-5.0;
	max_rand=5.0;
	range=max_rand-min_rand;
	stupen=(int)rad;
	pom=(int)k;
	
	if(k>stupen){
		return return_value='0';
	}
	
	else if(stupen==0){
		if(pom==0){
			q[0]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
			return return_value='1';
		}
	}
		
	else if(stupen==1){
		if(pom==0){
			return return_value='0';	
		}
		else{
			q[0]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
			return return_value='1';
		}
	}
	
	else if(stupen%2==0){
		if(pom%2==1){
			 return return_value='0';
		}
		if(pom==0 && stupen>2){
			return return_value='0';
		}
	}
			
	else if(stupen%2==1){
		if(pom%2==0){
			return return_value='0';
		}
		if(pom==1){
			q[0]=range*((((float)rand())/(float)RAND_MAX))+0.;
			return return_value='1';
		}
	}

	for(i=0;i<pom;i++){
		K[i]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
	}
	
	for(i=0;i<255;i++){
		A[i]=0.;
		B[i]=0.;
		q[i]=0.;
	}
			
	A[0]=1.;
	A[1]=K[0];
	
	for(j=1;j<pom;j++){
		for(i=0;i<pom+1;i++){
			B[0]=0.;
			B[i]=K[j]*A[i-1];
			q[i]=A[i]+B[i];	
		}
		for(i=0;i<pom+1;i++){
			A[i]=q[i];
		}
	}
	return return_value='1';
}

main(){
	char rad,k,polynom;
	int stupen,koren;
	float koeficienty[MAX];

	srand(time(NULL));
	printf("Zadaj najvacsi stupen polynoumu:");
	scanf("%d",&stupen);
	while(stupen<0 || stupen>255){
		printf("Znovu zadaj najvacsi stupen polynoumu:");
		scanf("%d",&stupen);
	}
	printf("Zadaj pocet realnych korenov polynomu:");
	scanf("%d",&koren);
	while(koren<0 || stupen>255){
		printf("Znovu zadaj pocet realnych korenov polynomu:");
		scanf("%d",&koren);
	}
	
	rad=(char)stupen;
	k=(char)koren;
	polynom=nahodny_polynom(koeficienty,rad,k);
	printf("%c",polynom);
	return(0);
}

