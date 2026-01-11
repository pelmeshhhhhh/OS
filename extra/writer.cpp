#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
    const char* shm_name = "/my_shm";
    const int SIZE = 4096;
    
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    
    char* ptr = (char*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    std::string message = "Hello from writer process!";
    sprintf(ptr, "%s", message.c_str());
    
    std::cout << "Writer: Data written to shared memory" << std::endl;
    
    sleep(2);
    
    munmap(ptr, SIZE);
    shm_unlink(shm_name);
    
    return 0;
}