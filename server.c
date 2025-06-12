#include<stdio.h>
#include<string.h>
#include<winsock.h>



int main(){
    WSADATA wsa;
    
    int sd,cd,cad1;
    struct sockaddr_in sad,cad;
    char str[50];
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(sd,(struct sockaddr*)&sad,sizeof(sad));
    listen(sd,10);

    cad1=sizeof(cad);
    cd=accept(sd,(struct sockaddr*)&cad,&cad1);

    recv(cd,str,sizeof(str),0);
    printf("Client says :%s\n",str);
    closesocket(sd);
    //close(sd);
}

//gcc server.c -o server.exe -lws2_32  