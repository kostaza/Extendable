// myDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "myDLL.h"


std::string __declspec(dllexport) __stdcall start(std::string argument) {
	std::reverse(argument.begin(), argument.end());
	return argument;
}
