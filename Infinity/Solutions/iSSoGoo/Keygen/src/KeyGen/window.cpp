// includes
#include <Windows.h>
#include "window.h"
#include "input.h"

ATOM WINAPI registerMainWindowClass(HINSTANCE hInstance){

	// Window class
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX);

	// Optics
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	// windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KG));
	windowClass.hIcon = NULL;
	//windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = MAKEINTRESOURCEW("MainWindowClass");
	// windowClass.hIconSm = LoadIcon(windowClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	windowClass.hIconSm = NULL;

	return RegisterClassEx(&windowClass);
}