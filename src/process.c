#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>

#include "process.h"
#include "types.h"
#include "message.h"

int create_process(char const * path) {
    STARTUPINFO si;
	PROCESS_INFORMATION pi;
	
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcess(
			TEXT(path),
			NULL,
            NULL,
            NULL,
            FALSE,
			CREATE_NEW_CONSOLE,
			NULL,NULL,
			&si,
			&pi
		)
	) {
        fail_message("create process failed");
        return FALSE;
    }
    return TRUE;
}

int get_process(char const * process_name) {
    if (GetProcessIdFromName(TEXT(process_name))) {
        //success_message("found process");
        return TRUE;
    }
    else {
        //fail_message("process not found");
        return FALSE;
    }
}

DWORD GetProcessIdFromName(const char* process_name) {
	PROCESSENTRY32 pe32;
	
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapshot, &pe32)) {
		return FALSE;
    }
    char pname[300];
	do {
		sprintf(pname, "%s", pe32.szExeFile);
		if(lstrcmpi(pname, process_name) == 0) {
			return pe32.th32ProcessID;
		}
		
	} while (Process32Next(hSnapshot, &pe32));
	
	CloseHandle(hSnapshot);
	return FALSE;
}