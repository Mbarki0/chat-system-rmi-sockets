#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_CLIENTS 100
#define PORT 12345

int clients[MAX_CLIENTS] = {0};
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int sender_sock) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != 0 && clients[i] != sender_sock) {
            send(clients[i], message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *socket_desc) {
    int sock = *(int*)socket_desc;
    int read_size;
    char client_message[2000];

    while ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        client_message[read_size] = '\0';
        broadcast_message(client_message, sock);
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == sock) {
            clients[i] = 0;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    close(sock);
    free(socket_desc);
    return NULL;
}

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Impossible de creer le socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Erreur de bind");
        return 1;
    }

    listen(socket_desc, 3);
    c = sizeof(struct sockaddr_in);

    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        pthread_t sniffer_thread;
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == 0) {
                clients[i] = client_sock;
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);
        
        if(pthread_create(&sniffer_thread, NULL, handle_client, (void*) new_sock) < 0) {
            perror("Erreur creation thread");
            return 1;
        }
    }
    return 0;
}