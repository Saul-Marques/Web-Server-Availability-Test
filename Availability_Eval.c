#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
int main() {
    const char *pipe1 = "pipe1";
    int pipefd = open(pipe1, O_RDONLY);
    char buffer[100];

    //Calculations
    time_t start_time, end_time;
    double down_time = 0.0;
    int server_down = 0;
    //
    do {
        //Read from the pipe's buffer and check if it's up or down
        read(pipefd, buffer, sizeof(buffer));
        if(strncmp(buffer, "nok", 3) == 0 && server_down == 0) {
            time(&start_time);
            server_down = 1;
            // Send a notif to a telegram bot. Change this URL to your use case.                           Change the chat ID to your own personnal chatID
            system("curl -s -X POST https://api.telegram.org/bot123456789101112123/sendMessage -d chat_id=12345678 -d text=\"Server is Down!\"");

        } else if(strncmp(buffer, "ok", 2) == 0 && server_down == 1) {
            time(&end_time);
            down_time += difftime(end_time, start_time);
            server_down = 0;
        }
        sleep(1); // Wait for 1 sec
        printf("Server was down for a total of: %.2f seconds.\n", down_time);
    } while(1);
    //
    printf("Server was down for a total of: %.2f seconds.\n", down_time);

    close(pipefd);
    return 0;
}
