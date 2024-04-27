#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure pour stocker les informations sur la partie du tableau que chaque thread doit traiter
typedef struct {
    int *tab;       // Pointeur vers le tableau
    int debut;      // Indice de début de la partie du tableau
    int fin;        // Indice de fin de la partie du tableau
    int sum_partiel;// Somme partielle calculée par chaque thread
} partiel;

pthread_mutex_t lock; // Déclaration du verrou

// Fonction exécutée par chaque thread pour calculer la somme partielle de sa partie du tableau
void* sum_partial(void* arg) {
    partiel* var = (partiel *)arg;
    int star = var->debut;
    int end = var->fin;
    int i;
    var->sum_partiel = 0;
    for (i = star; i <= end; i++) {
        pthread_mutex_lock(&lock);  // Verrouillage pour éviter les accès concurrents à sum_partiel
        var->sum_partiel += var->tab[i]; // Calcul de la somme partielle
        pthread_mutex_unlock(&lock);    // Déverrouillage
    }
    pthread_exit(NULL); // Terminaison du thread
}

int main(int argc, char *argv[]) {
    const long taill = 50;  // Taille du tableau
    const int nb_thread = 5; // Nombre de threads
    pthread_mutex_init(&lock, NULL); // Initialisation du verrou

    int array[taill];
    int j;
    // Initialisation du tableau
    for (j = 0; j < taill; j++) array[j] = j;

    int x = taill / nb_thread; // Taille de chaque partie du tableau
    pthread_t thread[nb_thread]; // Tableau de threads
    partiel tableau[nb_thread]; // Tableau de structures partielles
    int n;
    // Création des threads
    for (n = 0; n < nb_thread; n++) {
        tableau[n].tab = array; // Initialisation du pointeur vers le tableau
        tableau[n].debut = n * x; // Calcul du début de la partie du tableau
        if (tableau[n].fin == taill) tableau[n].fin = taill - 1; // Vérification de la fin du tableau
        else tableau[n].fin = tableau[n].debut + x - 1; // Calcul de la fin de la partie du tableau
        // Création du thread en passant la fonction sum_partial et la structure comme arguments
        if (pthread_create(&thread[n], NULL, sum_partial, (void *)&tableau[n]) != 0) {
            perror("Erreur lors de la création du thread");
            return EXIT_FAILURE;
        }
    }
    int w;
    // Attente de la fin de chaque thread
    for (w = 0; w < nb_thread; w++) {
        if (pthread_join(thread[w], NULL) != 0) {
            perror("Erreur lors de l'attente du thread");
            return EXIT_FAILURE;
        }
    }

    int sum = 0;
    int k;
    // Calcul de la somme totale
    for (k = 0; k < nb_thread; k++) {
        sum += tableau[k].sum_partiel;
    }

    printf("Somme totale = %d \n", sum); // Affichage de la somme totale

    pthread_mutex_destroy(&lock); // Destruction du verrou

    return 0;
}
