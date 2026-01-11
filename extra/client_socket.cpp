#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock_fd;
    struct sockaddr_un addr;
    char buffer[100];
    
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/tmp/my_socket");
    
    connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
    
    const char* message = "Hello from client!";
    write(sock_fd, message, strlen(message) + 1);
    
    read(sock_fd, buffer, sizeof(buffer));
    std::cout << "Client received: " << buffer << std::endl;
    
    close(sock_fd);
    return 0;
}