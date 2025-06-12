#include <stdio.h>
#include <string.h>
#include <winsock2.h>

int main() {
    WSADATA wsa;
    SOCKET sd, cd;
    struct sockaddr_in sad, cad;
    int cadl, i, j, dl, divl;
    char data[50], divisor[50], data1[50];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9995);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr*)&sad, sizeof(sad));
    listen(sd, 10);
    printf("Waiting for connection...\n");

    cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr*)&cad, &cadl);
    printf("Client connected.\n");

    recv(cd, data, sizeof(data), 0);
    recv(cd, divisor, sizeof(divisor), 0);

    printf("Received Data: %s\n", data);
    printf("Received Divisor: %s\n", divisor);

    dl = strlen(data);
    divl = strlen(divisor);

    strcpy(data1, data);  // backup the received codeword

    for (i = 0; i < dl - (divl - 1); i++) {
        if (data[i] == '1') {
            for (j = 0; j < divl; j++) {
                data[i + j] = (data[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Check if remainder is all zeros
    int error = 0;
    for (i = dl - (divl - 1); i < dl; i++) {
        if (data[i] != '0') {
            error = 1;
            break;
        }
    }

    if (error == 0) {
        printf("\nOriginal data received correctly.\n");
        printf("Actual data: ");
        for (i = 0; i < dl - (divl - 1); i++)
            printf("%c ", data1[i]);
        printf("\n");
    } else {
        printf("\nData received is incorrect (error detected).\n");
    }

    closesocket(cd);
    closesocket(sd);
    WSACleanup();

    return 0;
}

