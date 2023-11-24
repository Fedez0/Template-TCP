#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024
/*
//send
if (send(client_socket, message, strlen(message), 0) == -1) {
        perror("Errore nell'invio dei dati al server");
        exit(EXIT_FAILURE);
}
//recv
if (recv(client_socket, buffer, sizeof(buffer), 0) == -1) {
        perror("Errore nella recv dal server");
        exit(EXIT_FAILURE);
}
*/ 
int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Creazione del socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione della struttura del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // Connessione al server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Errore nella connessione al server");
        exit(EXIT_FAILURE);
    }
//////////////////////////////////////////////////////////////////////////////////////////
//                  inizio programma
    printf("Connesso al server %s:%d\n", SERVER_IP, PORT);

    // Invio dei dati al server
    const char *message = "Hello, server!";
    if (send(client_socket, message, strlen(message), 0) == -1) {
        perror("Errore nell'invio dei dati al server");
        exit(EXIT_FAILURE);
    }

    // Ricezione dei dati dal server
    memset(buffer, 0, sizeof(buffer));
    if (recv(client_socket, buffer, sizeof(buffer), 0) == -1) {
        perror("Errore nella recv dal server");
        exit(EXIT_FAILURE);
    }

    printf("Dati ricevuti dal server: %s\n", buffer);
    // Ricezione dei dati dal server
    memset(buffer, 0, sizeof(buffer));
    if (recv(client_socket, buffer, sizeof(buffer), 0) == -1) {
        perror("Errore nella recv dal server");
        exit(EXIT_FAILURE);
    }

    // Chiusura della connessione
    close(client_socket);

    return 0;
}
