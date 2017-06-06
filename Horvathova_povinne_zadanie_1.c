#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 255
#define FAIL '0'
#define OK '1'

char nahodny_polynom(float *q, char rad, char k){
	float min_rand, max_rand, range, korene[MAX], A[MAX], B[MAX];
	int i,j;
	
	min_rand=-5.0;
	max_rand=5.0;
	range=max_rand-min_rand;
	
	if(k>rad){
		return FAIL;
	}
	
	if(rad==0){
		q[0]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
		return OK;
	}	
	
	if(rad==1){
		if(k==0){
			return FAIL;	
		}
		
		else if(k==1){
            q[0]=1.;
			q[1]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
        return OK; 
		}
	}
	
	if((int)rad%2==0){
		if((int)k%2==1){
			 return FAIL;
		}	
		else if(k==0){
			q[0]=1.;
			q[rad]=range*((float)rand())/((float)RAND_MAX)+0.;
			return OK;		
		}
	}
			
	if((int)rad%2==1){
		if((int)k%2==0){
			return FAIL;
		}
		
		if(k==1){
			q[0]=1.;
			q[1]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
			return OK;
		}
	}
	
    for(i=0;i<(int)k;i++){
        korene[i]=range*((((float)rand())/(float)RAND_MAX))+min_rand;
    }

	for(i=0;i<255;i++){
		A[i]=0.;
		B[i]=0.;
		q[i]=0.;
	}
			
	A[0]=1.;
	A[1]=korene[0];
	for(j=1;j<(int)k;j++){
		for(i=0;i<(int)k+1;i++){
			B[0]=0.;
			B[i+1]=korene[j]*A[i];
			q[i]=A[i]+B[i];
			
		}
		for(i=0;i<(int)k+1;i++){
			A[i]=q[i];
		}
	}
		
	printf("\n");
	return OK;
}

main(){
	char rad,k,polynom;
	int stupen,koren,i;
	float *koeficienty;

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
	if((koeficienty=malloc((stupen+1)*sizeof(float)))==NULL){
		return FAIL;
	}
	
	rad=(char)stupen;
	k=(char)koren;
	polynom=nahodny_polynom(koeficienty,rad,k);
	printf("hodnota: %c\n",polynom);
	
	if(polynom!='0'){
		for(i=0;i<stupen+1;i++){
		printf("%.2f ",koeficienty[i]);
		}
	}
	//free(koeficienty);
}

