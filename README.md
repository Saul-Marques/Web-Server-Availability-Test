# Web-Server-Availability
This code allows us to communicate to a WS as a client, get it's state, UP or DOWN. Outputs it's status when it changes to the console and notifies us on telegram.
## Instalation and compilation
Clone the repository
Compile the files either using the makefile file(lol) 

or

gcc Availability_Eval.c -o Availability_Eval

gcc WS_Client.c -o WS_Client
## Before Compiling
Change the line 24 on the 'Availability_Eval.c' file to meet your telegram bot's and profile ChatID params
```C
// Send a notif to a telegram bot. Change this URL to your use case.                           Change the chat ID to your own personnal chatID
            system("curl -s -X POST https://api.telegram.org/bot123456789101112123/sendMessage -d chat_id=12345678 -d text=\"Server is Down!\"");
```


## License

[MIT](https://choosealicense.com/licenses/mit/)
