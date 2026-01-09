#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <algorithm>

bool isProcessRunning(int pid) {
    return kill(pid, 0) == 0;
}

int main() {
    const char* envName = "PROC_TO_KILL";
    setenv(envName, "xclock,gedit", 1);

    pid_t testPid = fork();
    if (testPid == 0) {
        execlp("sleep", "sleep", "100", (char*)NULL);
        return 0;
    }

    sleep(1);

    std::cout << "Process " << testPid << " exists: " << (isProcessRunning(testPid) ? "Yes" : "No") << std::endl;

    std::string cmd = "./killer --id " + std::to_string(testPid);
    system(cmd.c_str());

    sleep(1);

    std::cout << "Process " << testPid << " exists: " << (isProcessRunning(testPid) ? "Yes" : "No") << std::endl;

    unsetenv(envName);

    return 0;
}