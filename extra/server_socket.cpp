#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[100];
    
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/my_socket");
    
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    
    listen(server_fd, 5);
    
    std::cout << "Server: Waiting for connection..." << std::endl;
    
    client_fd = accept(server_fd, NULL, NULL);
    
    read(client_fd, buffer, sizeof(buffer));
    std::cout << "Server received: " << buffer << std::endl;
    
    const char* response = "Hello from server!";
    write(client_fd, response, strlen(response) + 1);
    
    close(client_fd);
    close(server_fd);
    unlink("/tmp/my_socket");
    
    return 0;
}