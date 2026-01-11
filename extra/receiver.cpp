#include <iostream>
#include <mqueue.h>
#include <cstdlib>

int main() {
    mqd_t mq;
    const char* queue_name = "/test_queue";
    char buffer[256];
    
    mq = mq_open(queue_name, O_RDONLY);
    
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    
    ssize_t bytes_read = mq_receive(mq, buffer, 256, NULL);
    
    if (bytes_read >= 0) {
        std::cout << "Receiver got: " << buffer << std::endl;
    }
    
    mq_close(mq);
    mq_unlink(queue_name);
    return 0;
}