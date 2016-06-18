#include <stdlib.h>
#include <windows.h>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

const char window_class_name[] = "myWindowClass";
const char window_title[] = "My Window";
const int window_width = 640;
const int window_height = 480;

int error(const char* msg) {
	LOG(ERROR) << msg;
	MessageBox(NULL, msg, "Error", MB_ICONEXCLAMATION | MB_OK);
	return 1;
}

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "LBUTTONDOWN", "Event", MB_OK | MB_ICONINFORMATION);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow) {
	/* Setup logging. */
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

	/* Register window class. */
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = window_class_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return error("Could not register window class.");

	/* Create window. */
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, window_class_name, window_title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, window_width, window_height,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) return error("Could not create window.");
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	/* Enter event loop. */
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
