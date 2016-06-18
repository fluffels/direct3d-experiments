#include <stdlib.h>
#include <windows.h>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow) {
	int argc = 0;
	LPCWSTR cmd_line = GetCommandLineW();
	LPWSTR* argvw = CommandLineToArgvW(cmd_line, &argc);
	char** argv = new char*[argc];
	for (int i = 0; i < argc; i++) {
		int len = wcslen(argvw[i]) + 1;
		argv[i] = new char[len];
		size_t copied = 0;
		wcstombs_s(&copied, argv[i], len, argvw[i], _TRUNCATE);
	}
	START_EASYLOGGINGPP(argc, (char**)argv);
	LOG(TRACE) << "Logging initialized.";
	MessageBox(NULL, "Hello, world!", "Note", MB_OK);
	return 0;
}
