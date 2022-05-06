#pragma once

namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
}

namespace utils 
{
	template<typename T>
	T RPM(uintptr_t address) {
		T contents;
		ReadProcessMemory(h_process, (void*)address, &contents, sizeof(T), NULL);
		return contents;
	}

	DWORD GetProcessID(const std::wstring& processName);
	uintptr_t GetModuleBaseAddress(DWORD procId, const std::wstring& modName);
	uintptr_t DMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);
	void ClearScreen();
}

std::ostream& operator<< (std::ostream& out, String16 string);
std::ostream& operator<< (std::ostream& out, Vector3 v);
std::ostream& operator<< (std::ostream& out, Vector2 v);