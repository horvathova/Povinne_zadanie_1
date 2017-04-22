#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include  <fcntl.h>


// vygeneruje random float v intervale <min, max> (skopirovane z http://stackoverflow.com/a/2509699/2576489)

void generator(char *file, int n){
	int fd,i,length,j;
	float value,min_rand,max_rand,range;
	
	min_rand=-5.0;
	max_rand=5.0;
	range=max_rand-min_rand;
	value=range*((((float)rand())/(float)RAND_MAX))+min_rand;
	length=10+rand()%10;
	fd=open(file,O_WRONLY|O_CREAT);
	
	for(i=0;i<length;i++){
		length=10+rand()%10;
			for(j=0;j<length;j++){
				value=range*((((float)rand())/(float)RAND_MAX))+min_rand;
				write(fd,value,sizeof(n*length*value));
			}
	}

	close(0);
}

int main(int argc, char **argv){
	char *file = argv[1];
	int n = atoi(argv[2]);
	
	srand(time(NULL));
	
	if (argc < 3){
		printf("Malo argumentov");
		return 1;
	}
	generator(file, n);
	return 0;
}
