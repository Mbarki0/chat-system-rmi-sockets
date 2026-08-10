#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // Pour sleep(), simule un délai de réception

#define MAX_MESSAGE_LENGTH 1024

// Simuler la fonction de réception de message pour le démonstration
void* receiveMessages(void* arg) {
    char receivedMsg[MAX_MESSAGE_LENGTH];

    while (1) {
        // Attendre fictivement la réception d'un message
        sleep(5); // Simuler l'attente de réception
        strcpy(receivedMsg, "Message simulé reçu du réseau.");
        printf("\nReçu: %s\n", receivedMsg);
        printf("Tapez votre message: "); // Prompt à re-afficher après affichage d'un message reçu
        fflush(stdout); // Assurez-vous que le prompt est affiché immédiatement
    }

    return NULL;
}

// Fonction principale qui gère l'envoi des messages
int main() {
    char message[MAX_MESSAGE_LENGTH];
    pthread_t thread_id;

    // Lancer le thread qui gère la réception des messages
    pthread_create(&thread_id, NULL, receiveMessages, NULL);

    printf("Bienvenue dans le chat !\n");
    printf("Tapez vos messages ci-dessous. Tapez 'exit' pour quitter.\n");

    while (1) {
        printf("Tapez votre message: ");
        fgets(message, MAX_MESSAGE_LENGTH, stdin);
        message[strcspn(message, "\n")] = 0; // Enlever le caractère de nouvelle ligne

        if (strcmp(message, "exit") == 0) {
            break;
        }

        // Envoyer le message
        printf("Vous avez envoyé: %s\n", message);
    }

    pthread_cancel(thread_id); // Arrêter le thread de réception au cas où
    printf("Vous avez quitté le chat.\n");
    return 0;
}
