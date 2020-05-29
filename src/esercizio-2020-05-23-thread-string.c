/*
prendere la stringa di caratteri:

char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";

il processo crea tre threads; passa la stringa di caratteri content come parametro a ciascuno dei tre threads.

- il primo thread conta il numero di vocali nella stringa e restituisce questo valore.
- il secondo thread conta il numero di consonanti nella stringa e restituisce questo valore.
- il terzo thread conta il numero di spazi e newline nella stringa e restituisce questo valore.

il thread principale aspetta il risultato dei tre threads e poi scrive su stdout i risultati.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


void * thread_function_1(void *arg);
void * thread_function_2(void *arg);
void * thread_function_3(void *arg);

int main() {
	char * content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Mattis rhoncus urna neque viverra justo nec ultrices. Pretium quam vulputate dignissim suspendisse in est ante. Vitae congue mauris rhoncus aenean. Blandit cursus risus at ultrices mi. Ut lectus arcu bibendum at varius vel pharetra vel. Etiam non quam lacus suspendisse faucibus interdum posuere. Eget sit amet tellus cras adipiscing enim eu turpis egestas. Lectus magna fringilla urna porttitor rhoncus dolor purus non. Sit amet consectetur adipiscing elit duis tristique sollicitudin nibh. Nec tincidunt praesent semper feugiat nibh. Sapien pellentesque habitant morbi tristique senectus et netus et malesuada.";
	pthread_t threads[3];

	if(pthread_create(&threads[0], NULL, thread_function_1, content) != 0){
		perror("pthread_create()\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&threads[1], NULL, thread_function_2, content) != 0){
		perror("pthread_create()\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&threads[2], NULL, thread_function_3, content) != 0){
		perror("pthread_create()\n");
		exit(EXIT_FAILURE);
	}


	void * res1;
	if(pthread_join(threads[0], &res1) != 0){
		perror("pthread_join()\n");
		exit(EXIT_FAILURE);
	}
	int * vowels = (int *) res1;
	printf("[Thread 1] Numero di vocali: %d\n", *vowels);


	void * res2;
	if(pthread_join(threads[1], &res2) != 0){
		perror("pthread_join()\n");
		exit(EXIT_FAILURE);
	}
	int * consonants = (int *) res2;
	printf("[Thread 2] Numero di consonanti: %d\n", *consonants);

	void * res3;
	if(pthread_join(threads[2], &res3) != 0){
		perror("pthread_join()\n");
		exit(EXIT_FAILURE);
	}
	int * others = (int *) res3;
	printf("[Thread 3] Numero di spazi e 'new line': %d\n", *others);


	exit(EXIT_SUCCESS);
}

void * thread_function_1(void *arg){
	char *str = (char *) arg;
	int * vowels = calloc(1, sizeof(int));
	if(vowels == NULL){
		perror("calloc()\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i<strlen(str) ; i++){
		if(str[i] == 'a' || str[i] == 'A'){
			vowels[0]++;
		}
		if(str[i] == 'e' || str[i] == 'E'){
			vowels[0]++;
		}
		if(str[i] == 'i' || str[i] == 'I'){
			vowels[0]++;
		}
		if(str[i] == 'o' || str[i] == 'O'){
			vowels[0]++;
		}
		if(str[i] == 'u' || str[i] == 'U'){
			vowels[0]++;
		}
	}

	return (void *) vowels;
}



void * thread_function_2(void *arg){
	char *str = (char *) arg;
	int * consonants = calloc(1, sizeof(int));
	if(consonants == NULL){
		perror("calloc()\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i< strlen(str) ; i++){
		if((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)){
	        if(str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && str[i] != 'A' && str[i] != 'E' && str[i] != 'I' && str[i] != 'O' && str[i] != 'U')
	        	consonants[0]++;
	    }
	}

	return (void *) consonants;
}

void * thread_function_3(void *arg){
	char *str = (char *) arg;
	int * spaces = calloc(1, sizeof(int));
	if(spaces == NULL){
		perror("calloc()\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i< strlen(str) ; i++){
		if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'){
			spaces[0]++;
	    }
	}

	return (void *) spaces;
}
