#include<stdio.h>
#include<string.h>
#include<winsock.h>

int main(){
    int sd,cad1;
    struct sockaddr_in sad,cad;
    char str[50];

    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");


    connect(sd,(struct sockaddr*)&sad,sizeof(sad));

    printf("Enter your message:");
    scanf("%s[^\n]s",str);
    send(sd,str,sizeof(str),0);
    closesocket(sd);
    return 0;

}