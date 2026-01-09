#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <vector>

void checkProcess(const std::string& label, const std::string& name) {
    bool found = false;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(hSnapshot, &pe)) {
        do {
            std::wstring wName(pe.szExeFile);
            std::string currentName(wName.begin(), wName.end());
            if (name == currentName) {
                found = true;
                break;
            }
        } while (Process32NextW(hSnapshot, &pe));
    }
    CloseHandle(hSnapshot);
    std::cout << label << ": " << (found ? "RUNNING" : "NOT FOUND") << "\n";
}

int main() {
    _putenv("PROC_TO_KILL=mspaint.exe");

    ShellExecuteA(NULL, "open", "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
    ShellExecuteA(NULL, "open", "mspaint.exe", NULL, NULL, SW_SHOWNORMAL);

    Sleep(2000);

    DWORD notepadId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W pe;
    pe.dwSize = sizeof(PROCESSENTRY32W);
    if (Process32FirstW(hSnap, &pe)) {
        do {
            std::wstring wName(pe.szExeFile);
            std::string currentName(wName.begin(), wName.end());
            if (currentName == "notepad.exe") {
                notepadId = pe.th32ProcessID;
                break;
            }
        } while (Process32NextW(hSnap, &pe));
    }
    CloseHandle(hSnap);

    std::cout << "--- BEFORE ---\n";
    checkProcess("Notepad", "notepad.exe");
    checkProcess("Paint", "mspaint.exe");

    std::string killerPath = "D:\\Visual Studio(projects)\\Killer\\x64\\Debug\\Killer.exe";
    std::string cmd = "\"" + killerPath + "\" --id " + std::to_string(notepadId);

    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    Sleep(1000);

    std::cout << "\n--- AFTER ---\n";
    checkProcess("Notepad", "notepad.exe");
    checkProcess("Paint", "mspaint.exe");

    _putenv("PROC_TO_KILL=");

    system("pause");
    return 0;
}