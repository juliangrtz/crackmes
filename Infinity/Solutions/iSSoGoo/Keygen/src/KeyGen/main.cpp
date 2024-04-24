/*
	Keygen for Himsord's Infinity Keygenme v1

	Author:	iSSoGoo
	URL:	http://crackmes.de/users/himsord/infinity_keygenme_v1/
*/

// includes
#include <Windows.h>
#include "input.h"
#include "resource.h"

// main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// uneeded parameters
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Create GUI
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc, 0);

	return 0;
}