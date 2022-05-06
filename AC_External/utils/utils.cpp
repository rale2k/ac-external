#include "includes.h"

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess) {
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, size, nullptr);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess) {
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dst, nopArray, size, hProcess);
	delete[] nopArray;
}

DWORD utils::GetProcessID(const std::wstring& processName) {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);
	// If we don't do the above, CreateToolhelp32Snapshot fails.

	// Create a snapshot of all running processes.
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}
	// Iterate through all the following processes in the snapshot.
	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;

}

uintptr_t utils::GetModuleBaseAddress(DWORD procId, const std::wstring& modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!modName.compare(modEntry.szModule))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t utils::DMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;

	for (unsigned int i = 0; i < offsets.size(); ++i)
	{	
		ReadProcessMemory(h_process, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}

	return addr;
}

void utils::ClearScreen() {
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}












// ...

std::ostream& operator<< (std::ostream& out, String16 string) {
	for (int i = 1; i < 16; i++) {
		if (string.str[i] != '.') {
			out << string.str[i];
		}
	}
	return out;
}

std::ostream& operator<< (std::ostream& out, Vector3 v) {
	out << "X: " << v.x << " Y: " << v.y << " Z: " << v.z;
	return out;
}

std::ostream& operator<< (std::ostream& out, Vector2 v) {
	out << "X: " << v.x << " Y: " << v.y;
	return out;
}
