#include "stdafx.h"
#include "Module.h"
#include <stdexcept>
#include <Windows.h>
#include <iostream>


Module::Module(const std::wstring &fileName) {
	std::wcout << "\nLoading... " << fileName << std::endl;
	m_file = LoadLibraryW(fileName.c_str());
	if (m_file == NULL) {
		std::cout << "Failed to load dll. Error number: " << GetLastError() << "\nMake sure the dll exists in the plugins folder and try again" << std::endl;
		system("pause");
		m_file = LoadLibraryW(fileName.c_str());
		if (m_file == NULL) throw GetLastError();
	}
}

Module::~Module() {
	if (!FreeLibrary(m_file))
		std::cout << "Failed to unload module, with error number: " << GetLastError() << std::endl;
}


func_pointer Module::getFunction(const char* function) const {
	func_pointer func = (func_pointer)GetProcAddress(m_file, function);
	if (!func) throw GetLastError();
	
	return func;
}
