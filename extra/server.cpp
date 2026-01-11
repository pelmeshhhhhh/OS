#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char* fifo_path = "/tmp/my_fifo";
    
    mkfifo(fifo_path, 0666);
    
    std::cout << "Server: Waiting for client..." << std::endl;
    
    int fd = open(fifo_path, O_RDONLY);
    char buffer[100];
    
    read(fd, buffer, sizeof(buffer));
    std::cout << "Server received: " << buffer << std::endl;
    
    close(fd);
    unlink(fifo_path);
    return 0;
}