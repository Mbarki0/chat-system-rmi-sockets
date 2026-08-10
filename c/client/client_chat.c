#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345

void *receiveMessages(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char server_reply[2000];
    int read_size;
    
    while((read_size = recv(sock, server_reply, sizeof(server_reply) - 1, 0)) > 0) {
        server_reply[read_size] = '\0';
        printf("\nServeur rep: %s\nEntrez un message : ", server_reply);
        fflush(stdout);
    }

    if(read_size == 0) {
        puts("\nServeur deconnecte");
    } else if(read_size == -1) {
        perror("recv failed");
    }

    free(socket_desc);
    exit(0);
    return NULL;
}

int main() {
    int sock;
    struct sockaddr_in server;
    char message[1000];
    pthread_t recv_thread;
    int *new_sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Impossible de creer un socket");
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connexion echouee");
        return 1;
    }

    new_sock = malloc(sizeof(int));
    *new_sock = sock;
    if(pthread_create(&recv_thread, NULL, receiveMessages, (void*) new_sock) < 0) {
        perror("Impossible de creer le thread de reception");
        return 1;
    }

    while(1) {
        printf("Entrez un message : ");
        if (fgets(message, sizeof(message), stdin) != NULL) {
            message[strcspn(message, "\n")] = 0;
            
            if (strlen(message) > 0) {
                if(send(sock, message, strlen(message), 0) < 0) {
                    perror("Echec de l'envoi");
                    return 1;
                }
            }
        }
    }

    close(sock);
    return 0;
}