#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <signal.h>
#include <dirent.h>
#include <fstream>
#include <sstream>

std::vector<int> getPidsByName(const std::string& name) {
    std::vector<int> pids;
    DIR* dir = opendir("/proc");
    if (!dir) return pids;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            char* endptr;
            int pid = strtol(entry->d_name, &endptr, 10);
            if (*endptr == '\0') {
                std::string cmdPath = std::string("/proc/") + entry->d_name + "/comm";
                std::ifstream commFile(cmdPath);
                std::string commName;
                if (std::getline(commFile, commName) && commName == name) {
                    pids.push_back(pid);
                }
            }
        }
    }
    closedir(dir);
    return pids;
}

void killProcess(int pid) {
    kill(pid, SIGKILL);
}

int main(int argc, char* argv[]) {
    char* envVal = getenv("PROC_TO_KILL");
    if (envVal) {
        std::stringstream ss(envVal);
        std::string name;
        while (std::getline(ss, name, ',')) {
            for (int pid : getPidsByName(name)) killProcess(pid);
        }
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--id" && i + 1 < argc) {
            killProcess(std::stoi(argv[++i]));
        } else if (arg == "--name" && i + 1 < argc) {
            for (int pid : getPidsByName(argv[++i])) killProcess(pid);
        }
    }

    return 0;
}