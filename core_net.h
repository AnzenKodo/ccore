#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>

void net_fetch(const char *hostname, const char *path, const char *filename) {
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server_addr;

    // Step 1: Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error: socket creation failed.");
    }

    // Step 2: Resolve hostname to IP address
    struct hostent *he = gethostbyname(hostname);
    if (he == NULL) {
        perror("Error: gethostbyname failed.");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, he->h_addr_list[0], he->h_length);

    // Step 3: Connect to server
    if (connect(
        sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)
    ) < 0) {
        perror("Error: connection failed");
        close(sockfd);
        exit(1);
    }

    // Step 4: Send HTTP GET request
    char request[2048];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\n"
                                        "Host: %s\r\n"
                                        "Connection: close\r\n"
                                        "\r\n", path, hostname);

    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Error: send failed");
        exit(1);
    }

    // Step 5: Open file to save data
    FILE *fp = fopen(filename + 1, "wb");
    if (!fp) {
        perror("Error: failed to open file");
        exit(1);
    }

    // Step 6: Receive the response and write to file
    ssize_t bytes_read;
    while ((bytes_read = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes_read, fp);
    }

    if (bytes_read < 0) {
        perror("Error: receive failed");
    }

    printf("File downloaded successfully\n");

    fclose(fp);
    close(sockfd);
}
