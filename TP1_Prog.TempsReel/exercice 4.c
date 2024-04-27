#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le premier thread (Thread 1)
void *thread_func1(void *arg) {
	printf("Thread 1: Bonjour !\n"); // Affiche un message
	return NULL;
}

// Fonction exécutée par le deuxième thread (Thread 2)
void *thread_func2(void *arg) {
	printf("Thread 2: Salut !\n"); // Affiche un message
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t1; // Identifiant du premier thread
	pthread_t t2; // Identifiant du deuxième thread
	
	// Création du premier thread
	if (pthread_create(&t1, NULL, thread_func1, NULL) != 0) {
		perror("Erreur de création du thread 1");
		return EXIT_FAILURE;
	}
	
	// Attente de la fin du premier thread
	if(pthread_join(t1, NULL) != 0) {
        perror("Erreur lors de l'attente de la fin du thread 1");
        return EXIT_FAILURE;
    }
	
	// Création du deuxième thread
	if (pthread_create(&t2, NULL, thread_func2, NULL) != 0) {
		perror("Erreur de création du thread 2");
		return EXIT_FAILURE;
	}
	
	// Attente de la fin du deuxième thread
    if(pthread_join(t2, NULL) != 0){
        perror("Erreur lors de l'attente de la fin du thread 2");
        return EXIT_FAILURE;
    }
	
	return EXIT_SUCCESS;
}
