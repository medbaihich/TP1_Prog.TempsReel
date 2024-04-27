#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction exécutée par le thread
void *print_message(void *ptr) {
    char *message = (char *)ptr;
    printf("%s\n", message); // Affiche le message
    pthread_exit(NULL); // Termine le thread
}

int main() {
    pthread_t thread; // Déclaration d'un identifiant de thread

    char *message = "Bonjour, je suis un thread !"; // Message à afficher

    // Création du thread
    if (pthread_create(&thread, NULL, print_message, (void *)message)) {
        fprintf(stderr, "Erreur lors de la création du thread\n"); // Affiche un message d'erreur en cas d'échec
        return 1;
    }

    // Attente de la fin du thread
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Erreur lors de l'attente du thread\n"); // Affiche un message d'erreur en cas d'échec
        return 2;
    }

    return 0;
}
