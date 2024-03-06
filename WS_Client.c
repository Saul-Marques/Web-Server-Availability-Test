#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
int checkServerStatus();

int main() {
    const char *pipe1 = "pipe1";
    mkfifo(pipe1, 0666);
    int pipefd = open(pipe1, O_WRONLY);
    do{
        int result = checkServerStatus();
        //Calculations
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char timestamp[64];
        sprintf(timestamp, "%02d-%02d-%04d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        //
        //Write to pipe the status and timestamps
        if(result == 1) {
            write(pipefd, "nok ", 5);
            fflush(NULL);
            write(pipefd, timestamp, sizeof(timestamp));
            fflush(NULL);
        } else {
            write(pipefd, "ok ", 4);
            fflush(NULL);
            write(pipefd, timestamp, sizeof(timestamp));
            fflush(NULL);
        }
        sleep(1); // Wait 1 second !Not the most efficient way!
    } while(1);

    close(pipefd);
    return 0;
}

int checkServerStatus() {
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //Debugging the socket
    if (sockfd == -1) {
        perror("Failed to create a socket: ");
        exit(EXIT_FAILURE);
    }

    // Restructure server's address
    struct sockaddr_in endereco_do_servidor;
    endereco_do_servidor.sin_family = AF_INET;
    endereco_do_servidor.sin_port = htons(80); // Define the port
    endereco_do_servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); //This is the server's IP address

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&endereco_do_servidor, sizeof(endereco_do_servidor)) == -1) {
        perror("Failed to connect to the server");

        close(sockfd);
        return 1;
    } else {
        // Debbuging the connection to the server
        printf("Connected to the server\n");

        // Close the socket
        close(sockfd);

        return 2;
    }
}
