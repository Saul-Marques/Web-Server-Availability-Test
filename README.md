# Web-Server-Availability
This code allows us to communicate to a WS as a client, get it's state, either UP or DOWN. Outputs it's status when it changes to the console and notifies us on telegram.

Feel free to edit the code's necessary params to your needs
## Instalation and compilation
Clone the repository

Compile the files either using the makefile file

or
```bash
gcc Availability_Eval.c -o Availability_Eval
```
```bash
gcc WS_Client.c -o WS_Client
```
## Before Compiling
Change the line 24 on the 'Availability_Eval.c' file to meet your telegram bot's and profile ChatID params
```C
// Send a notif to a telegram bot. Change this URL to your use case.                           Change the chat ID to your own personnal chatID
            system("curl -s -X POST https://api.telegram.org/bot123456789101112123/sendMessage -d chat_id=12345678 -d text=\"Server is Down!\"");
```

You should also change the server's IP on the file WS_Client.c to meet your needs
```C
serverAddress.sin_port = htons(80); // Define the port
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //This is the server's IP address
```

## Usage
On the Linux terminal
```bash
./WS_Client | ./Availability_Eval
```
## License

[MIT](https://choosealicense.com/licenses/mit/)

