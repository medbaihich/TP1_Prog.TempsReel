#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Structure pour stocker les informations sur les tâches périodiques
typedef struct {
	int id;        // Identifiant de la tâche
	int period;    // Période de la tâche
} PeriodicTask;

// Fonction exécutée par chaque thread représentant une tâche périodique
void* taskFunction(void *arg) {
	PeriodicTask *var;
	var = (PeriodicTask *)arg;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // Autoriser l'annulation du thread
	for (;;) {
		printf("Tâche %d a été exécutée\n", var->id); // Affichage de l'exécution de la tâche
		sleep(var->period); // Attente de la période de la tâche
		pthread_testcancel(); // Test si le thread doit être annulé
	}	
}

int main(int argc, char *argv[]) {
	PeriodicTask task1, task2;
	task1.id = 1; task1.period = 2; // Initialisation de la tâche 1
	task2.id = 2; task2.period = 2; // Initialisation de la tâche 2
	
	pthread_t thread1;
	pthread_t thread2;
	
	// Création du premier thread pour la tâche 1
	if(pthread_create(&thread1, NULL, taskFunction, (void *)&task1) != 0) {
		perror("Erreur de création du thread 1");
		return EXIT_FAILURE;
	}
	
	sleep(6); // Attente de 6 secondes
	
	// Annulation du premier thread
	if(pthread_cancel(thread1) != 0) {
		perror("Erreur d'annulation du thread 1");
		return EXIT_FAILURE;
	}
	
	// Attente de la fin du premier thread
	if(pthread_join(thread1, NULL) != 0) {
		perror("Erreur lors de l'attente de la fin du thread 1");
		return EXIT_FAILURE;
	}
	
	// Création du deuxième thread pour la tâche 2
	if(pthread_create(&thread2, NULL, taskFunction, (void *)&task2) != 0) {
		perror("Erreur de création du thread 2");
		return EXIT_FAILURE;
	}
	
	usleep(1000); // Attente de 1000 microsecondes
	
	// Annulation du deuxième thread
	if(pthread_cancel(thread2) != 0) {
		perror("Erreur d'annulation du thread 2");
		return EXIT_FAILURE;
	}
	
	// Attente de la fin du deuxième thread
	if(pthread_join(thread2, NULL) != 0) {
		perror("Erreur lors de l'attente de la fin du thread 2");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
