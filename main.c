#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int port = 1337;
int connection_backlog_size = 1000;

int main()
{
    char http_response[80] = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\nContent-Type: text/plain\r\n\r\na";
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *)&server_address, sizeof(server_address)) == 0)
    {
        printf("Socket running on port %d.\n", port);
    }
    else
    {
        printf("Error binding to port %d.\n", port);
    }
    listen(sock, connection_backlog_size);

    for (;;)
    {
        int client_sock = accept(sock, NULL, NULL);
        send(client_sock, http_response, strlen(http_response) + 1, 0);
        close(client_sock);
    }
    close(sock);
    return 0;
}