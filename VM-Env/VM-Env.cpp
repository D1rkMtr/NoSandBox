#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>

#define BUFFER_SIZE 100

int Error(const char* msg) {
	printf("%s (%u)\n",msg, GetLastError());
	return -1;
}

int main() {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnapshot)
		return Error("Failed in CreateToolhelp32Snapshot\n");

	PROCESSENTRY32 PE32;
	PE32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hSnapshot, &PE32))
		return Error("Failed in Process32First\n");

	while (Process32Next(hSnapshot, &PE32)) {
		//printf("ImageName : %ws\n", PE32.szExeFile);
		size_t i;
		char* pMBBuffer = (char*)malloc(BUFFER_SIZE);
		const wchar_t* pWCBuffer = PE32.szExeFile;

		wcstombs_s(&i, pMBBuffer, (size_t)BUFFER_SIZE, pWCBuffer, (size_t)BUFFER_SIZE - 1); 

		if (!strcmp("vmtoolsd.exe", pMBBuffer)) {
			printf("vmtoolsd.exe detected\nVMWare process , QUIT!!");
			return -1;
		}
		if (!strcmp("vm3dservice.exe", pMBBuffer)) {
			printf("vm3dservice.exe detected\nVMWare process , QUIT!!");
			return -1;
		}
		if (!strcmp("VGAuthService.exe", pMBBuffer)) {
			printf("vmtoolsd.exe detected\nVMWare process , QUIT!!");
			return -1;
		}
		if (!strcmp("ProcessHacker.exe", pMBBuffer)) {
			printf("ProcessHacker detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("procexp64.exe", pMBBuffer)) {
			printf("ProcessExplorer detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("x64dbg.exe", pMBBuffer)) {
			printf("x64dbg detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("windbg.exe", pMBBuffer)) {
			printf("WinDbg detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("DbgX.Shell.exe", pMBBuffer)) {
			printf("WinDbg detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("ImmunityDebugger.exe", pMBBuffer)) {
			printf("Immunity Debugger detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("Procmon64.exe", pMBBuffer)) {
			printf("Process Monitor detected\nQUIT!!");
			return -1;
		}
		if (!strcmp("pestudio.exe", pMBBuffer)) {
			printf("pestudio detected\nQUIT!!");
			return -1;
		}
		// ....
		
		if (pMBBuffer)
		{
			free(pMBBuffer);
		}
	}

	printf("Congrats!!! We survived!!\n");

	return 0;
}