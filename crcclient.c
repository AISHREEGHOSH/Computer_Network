#include <stdio.h>
#include <string.h>
#include <winsock2.h>

int main() {
    WSADATA wsa;
    SOCKET sd;
    struct sockaddr_in sad;
    char data[50], divisor[50], data1[50];
    int i, j, dl, divl;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9995);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd, (struct sockaddr*)&sad, sizeof(sad));

    printf("Enter input data (binary): ");
    scanf("%s", data);
    printf("Enter divisor (binary): ");
    scanf("%s", divisor);

    dl = strlen(data);
    divl = strlen(divisor);

    // Backup original data before modifying
    strcpy(data1, data);

    // Append divl - 1 zeros to data
    for (i = 0; i < divl - 1; i++)
        data[dl + i] = '0';
    data[dl + i] = '\0';

    // Copy for CRC processing
    strcpy(data1, data);

    // Perform division
    for (i = 0; i < dl; i++) {
        if (data1[i] == '1') {
            for (j = 0; j < divl; j++) {
                data1[i + j] = (data1[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Append remainder to original data
    for (i = dl; i < dl + divl - 1; i++) {
        data[i] = data1[i];
    }
    data[dl + divl - 1] = '\0';

    printf("Codeword to send: %s\n", data);

    send(sd, data, sizeof(data), 0);
    send(sd, divisor, sizeof(divisor), 0);

    closesocket(sd);
    WSACleanup();
    return 0;
}
