#include <stdio.h>
#include <math.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sd, cd;
    struct sockaddr_in sad, cad;
    int cad1 = sizeof(cad);
    char data[100];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == INVALID_SOCKET) {
        printf("Could not create socket.\n");
        WSACleanup();
        return 1;
    }

    sad.sin_family = AF_INET;
    sad.sin_port = htons(9995);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr*)&sad, sizeof(sad));
    listen(sd, 10);

    printf("Waiting for client...\n");
    cd = accept(sd, (struct sockaddr*)&cad, &cad1);
    printf("Client connected!\n");

    recv(cd, data, sizeof(data), 0);
    printf("Code word received: %s\n", data);

    int dl, j = 0, k, c, sum[100], t, sl, i;
    dl = strlen(data);

    // Ask for segment length (must be power of 2)
    while(1) {
        printf("\nEnter the segment length: ");
        scanf("%d", &sl);
        j = 0;
        for(i = 1; i <= sl; i++) {
            if(pow(2,i) == sl) {
                j = 1;
                break;
            }
        }
        if(j == 1) break;
        else printf("Segment length must be a power of 2.\n");
    }

    for(i = 0; i < sl; i++) sum[i] = 0;

    for(i = dl; i > 0; i -= sl) {
        c = 0;
        k = sl - 1;
        for(j = i - 1; j >= i - sl; j--) {
            t = sum[k] + (data[j] - '0') + c;
            sum[k] = t % 2;
            c = t / 2;
            k--;
        }
    }

    // Final carry
    for(j = sl - 1; j >= 0; j--) {
        t = sum[j] + c;
        sum[j] = t % 2;
        c = t / 2;
    }

    j = 0;
    for(i = 0; i < sl; i++) {
        if(sum[i] != 1) {
            j = 1;
            break;
        }
    }

    if(j == 0) {
        printf("\nData received correctly.\n");
        printf("Actual data is: ");
        for(i = 0; i < dl - sl; i++) {
            printf("%c", data[i]);
        }
        printf("\n");
    } else {
        printf("\nData received with error.\n");
    }

    closesocket(cd);
    closesocket(sd);
    WSACleanup();

    return 0;
}
