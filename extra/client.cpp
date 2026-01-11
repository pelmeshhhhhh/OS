#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char* fifo_path = "/tmp/my_fifo";
    
    int fd = open(fifo_path, O_WRONLY);
    
    std::string message = "Hello from client!";
    write(fd, message.c_str(), message.size() + 1);
    
    std::cout << "Client: Message sent" << std::endl;
    
    close(fd);
    return 0;
}