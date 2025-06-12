#include<stdio.h>
#include<string.h>
#include<winsock.h>
int main(){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    int sd, cd; // server and client socket descriptor

    struct sockaddr_in sad, cad; // sad and cad are instances of sockaddr_in. They store client and server socket info
  
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET - IPv4; SOCK_STREAM - two way, connection based; IPPROTO_TCP - TCP connection
  
    sad.sin_family = AF_INET; // IPv4
    sad.sin_port = htons(9995); // convert integer from host byte order
    sad.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost IP
  
    bind(sd, (struct sockaddr*)&sad, sizeof(sad));
    listen(sd, 10);
  
    int cadl = sizeof(cad); // size of cad
    cd = accept(sd, (struct sockaddr*)&cad, &cadl);
    printf("Client connected.\n");
    char string[100],s1[10]={'0'},s2[10]={'1'},ch;
    int c = 0, count=0;
   
    recv(cd, string, sizeof(string), 0); // recieve
    printf("Received message: %s\n",string);
    while (string[c] != '\0') {
        if ((string[c] == '1')) {
        count++;
        }
        c++;
        }
        
        printf("Total no of 1s: %d",count);
        printf("\n Enter the mode of parity:'e' for Even and 'o' for Odd ");
        scanf("%c",&ch);
        switch(ch)
        {
        case 'e':
        if(count%2==0)
        {
        printf("No error");
        }
        else
        {
        printf("Error");
        }
        break;
        case 'o':
        if(count%2==0)
        {
        printf("Error");
        }
        else
        {
        printf("No Error");
        }
        
        break;
        }
        return 0;

}