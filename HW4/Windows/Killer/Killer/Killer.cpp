#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <sstream>

void killById(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    if (hProcess != NULL) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
        std::wcout << L"[Killer] ID " << processId << L" killed.\n";
    }
}

void killByName(const std::wstring& processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(hSnapshot, &pe)) {
        do {
            if (processName == pe.szExeFile) {
                killById(pe.th32ProcessID);
            }
        } while (Process32NextW(hSnapshot, &pe));
    }
    CloseHandle(hSnapshot);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    char* buf = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, "PROC_TO_KILL") == 0 && buf != nullptr) {
        std::string s(buf);
        std::stringstream ss(s);
        std::string name;
        while (std::getline(ss, name, ',')) {
            std::wstring wName(name.begin(), name.end());
            killByName(wName);
        }
        free(buf);
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--id" && i + 1 < argc) {
            killById(std::stoi(argv[++i]));
        }
        else if (arg == "--name" && i + 1 < argc) {
            std::string n = argv[++i];
            std::wstring wN(n.begin(), n.end());
            killByName(wN);
        }
    }
    return 0;
}