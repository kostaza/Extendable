#include "stdafx.h"
#include "Directory.h"
#include <Windows.h>
#include <vector>
#include <stdexcept>
#include <iostream>


Directory::Directory(const std::wstring &dir){
	m_handle = CreateFileW(dir.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
	while (m_handle == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open the plugins directory, with error code: " << GetLastError() << "\nCheck if the directory exists and try again" << std::endl;
		system("pause");
		m_handle = CreateFileW(dir.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, nullptr);
	}
}

Directory::~Directory() {
	if (!CloseHandle(m_handle))
		std::cout << "Failed to close directory handle..." << std::endl;
}

std::wstring Directory::getNextCreatedFileName() const {
	std::vector<char> buf(sizeof(FILE_NOTIFY_INFORMATION) + MAX_PATH);
	DWORD bytes = 0;

	if (!ReadDirectoryChangesW(m_handle, reinterpret_cast<LPVOID>(&buf[0]), (DWORD)buf.size(), false, FILE_NOTIFY_CHANGE_FILE_NAME, &bytes, nullptr, nullptr))
		std::cout << "Failed to read directory changes, with error number: " << GetLastError() << std::endl;
	if (bytes != 0) {
		FILE_NOTIFY_INFORMATION *info = (FILE_NOTIFY_INFORMATION *)&buf[0];
		if (info->Action == FILE_ACTION_ADDED) {
			return std::wstring(info->FileName, info->FileNameLength);
		}
	}
	return L"";
}
