#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // For sockaddr_in and inet_addr
#include <sys/socket.h> // For socket functions
#include <unistd.h> // For close()

void scanPorts(const char *ip, int startPort, int endPort) {
    int sock;
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ip);

    printf("Scanning ports %d to %d on %s\n", startPort, endPort, ip);

    for (int port = startPort; port <= endPort; port++) {
        target.sin_port = htons(port);

        // Create a socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            continue;
        }

        // Try to connect
        if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("Port %d: OPEN\n", port);
        } else {
            printf("Port %d: CLOSED\n", port);
        }

        // Close the socket
        close(sock);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int startPort = atoi(argv[2]);
    int endPort = atoi(argv[3]);

    if (startPort <= 0 || endPort <= 0 || startPort > endPort) {
        printf("Invalid port range.\n");
        return 1;
    }

    scanPorts(ip, startPort, endPort);

    return 0;
}
