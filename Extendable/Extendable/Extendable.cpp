// Extendable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Directory.h"
#include "Module.h"
#include <iostream>
#include <Windows.h>
#include <string>

void LoadAndExecuteDLLs(std::wstring dir);
bool matchingExtension(const std::wstring &fname);

int main()
{
	std::cout << "Working..." << std::endl;

	std::wstring path = L"..\\..\\Plugins";
	LoadAndExecuteDLLs(path);

	return 0;
}

void LoadAndExecuteDLLs(std::wstring dir) {
	Directory direct(dir);
	while (1) {
		std::wstring name = direct.getNextCreatedFileName();
		std::wstring path(dir + L"\\" + name);
		if (matchingExtension(name)) {
			try {
				Module dll(path);
				try {
					func_pointer func = dll.getFunction("start");
					std::string ret = func("Hello World!");

					std::cout << "\nThe return value from the dll is: " << ret << std::endl;		//'start' execution
				}
				catch (int err) {
					std::cout << "Failed to load the function 'start'. Error: " << err << std::endl;
					continue;
				}
			}
			catch (int err) {
				std::cout << "Unable to load the dll. Error: " << err << std::endl;
				continue;
			}
		}

		DeleteFileW(path.c_str());						//delete the file after the dll was unload
	}
}

bool matchingExtension(const std::wstring & fname) {
	size_t pos = fname.find_last_of('.');
	return (pos != std::string::npos && wcscmp(fname.substr(pos + 1, std::string::npos).c_str(), L"dll") == 0);
}
