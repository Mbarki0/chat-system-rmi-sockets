#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern void start_server();  // Fonction du serveur_chat.c
extern void start_client();  // Fonction du client_chat.c

int main() {
    pthread_t server_thread, client_thread;

    // Démarrer le serveur dans un nouveau thread
    if (pthread_create(&server_thread, NULL, (void *) start_server, NULL) != 0) {
        perror("Failed to create server thread");
        return EXIT_FAILURE;
    }

    // Démarrer le client dans un autre thread
    if (pthread_create(&client_thread, NULL, (void *) start_client, NULL) != 0) {
        perror("Failed to create client thread");
        return EXIT_FAILURE;
    }

    // Attendre que les threads se terminent
    pthread_join(server_thread, NULL);
    pthread_join(client_thread, NULL);

    return EXIT_SUCCESS;
}
