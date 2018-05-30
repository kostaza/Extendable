#pragma once
#include <Windows.h>
#include <string>

class Directory {
public:
	Directory(const std::wstring &dir);
	virtual ~Directory();
	std::wstring getNextCreatedFileName() const;

private:
	HANDLE m_handle;
};

