#pragma once
#include <Windows.h>
#include <string>

typedef std::string (__stdcall *func_pointer) (std::string);	// Other function signatures won't be supported in this case

class Module {
public:
	Module(const std::wstring &fileName);
	virtual ~Module();
	func_pointer getFunction(const char* function) const;

private:
	HMODULE m_file;
};
