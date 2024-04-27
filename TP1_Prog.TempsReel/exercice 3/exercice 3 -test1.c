#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // N'oubliez pas d'inclure la bibliothèque <unistd.h> pour utiliser la fonction sleep()

// Fonction exécutée par le premier thread (Tache1)
void *Tache1(void *arg) {
    int i = 0;
    while (i < 5) {
        printf("Execution de Tache 1\n");
        sleep(1); // Attente de 1 seconde
        i++;
    }
    return NULL;
}

// Fonction exécutée par le deuxième thread (Tache2)
void *Tache2(void *arg) {
    int j = 0;
    while (j < 3) {
        printf("Execution de Tache 2\n");
        sleep(2); // Attente de 2 secondes
        j++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration des identifiants de thread

    // Création des threads
    pthread_create(&thread1, NULL, Tache1, NULL);
    pthread_create(&thread2, NULL, Tache2, NULL);

    // Attente de la fin des threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}
