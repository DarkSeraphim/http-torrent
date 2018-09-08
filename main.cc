#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <string>

#include <chrono>
#include <thread>

using namespace std;

void read_stream(int fd, vector<char>& buffer, int block_size = 64)
{
    char buf[block_size] = {0};
    int len;
    using namespace std::chrono;

    printf("Start reading\n");
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    while ((len = read(fd, buf, block_size)) > 0)
    {
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double, std::milli> time_span = t2 - t1;
        printf("Read %d bytes in %f milliseconds\n", len, time_span.count());
        buffer.assign(buf, buf + len);
        t1 = high_resolution_clock::now();
    }
    printf("End reading\n");
}

int server()
{
    int server_fd, client_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Sock!\n");
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    printf("Setopt\n");
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    {
        perror("Socket bind");
        exit(EXIT_FAILURE);
    }
    printf("Hey, Listen!\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("Socket listen");
        exit(EXIT_FAILURE);
    }
    printf("Accept\n");
    int length = sizeof(address);
    if ((client_fd = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &length)) < 0)
    {
        perror("Socket accept");
        exit(EXIT_FAILURE);
    }
    printf("Client!\n");
    vector<char> buffer;
    read_stream(client_fd, buffer);
    printf("Read it all!\n");   
    string request = string(buffer.begin(), buffer.end());
    char response[] = "HTTP/1.1 200 OK\r\n\r\n";   
    send(client_fd, response, strlen(response), 0);
    send(client_fd, request.c_str(), request.length(), 0);
    close(client_fd);
    close(server_fd);
    return 0;
}

int client()
{
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket failed");
        return -1;
    }
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0)
    {
        printf("Invalid address\n");
        return -1;
    }
    printf("Connect\n");
    if (connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
    {
        printf("Connection failed\n");
        return -1;
    }
    char msg[92] = {0};
    for (int i = 0; i < 92; i++) msg[i] = i;
    char buffer[1024] = {0};
    send(client_fd, msg, 92 * sizeof(char), 0);
    printf("Now waiting 30s\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(30000));
    int vsize = read(client_fd, buffer, 1024);
    printf("%s\n", buffer);
    close(client_fd);
    return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2 || (strcmp(argv[1], "server") != 0 && strcmp(argv[1], "client") != 0))
	{
		printf("Usage: %s <client|server>\n", argv[0]);
		return 0;
	}
    if (strcmp(argv[1], "server") == 0)
    {
        return server();
    }
    else
    {
        return client();
    }
}
