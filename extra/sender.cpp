#include <iostream>
#include <mqueue.h>
#include <string.h>
#include <cstdlib>

int main() {
    mqd_t mq;
    const char* queue_name = "/test_queue";
    struct mq_attr attr;
    
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;
    
    mq = mq_open(queue_name, O_CREAT | O_WRONLY, 0644, &attr);
    
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    
    const char* message = "Hello from sender!";
    mq_send(mq, message, strlen(message) + 1, 0);
    
    std::cout << "Sender: Message sent" << std::endl;
    
    mq_close(mq);
    return 0;
}