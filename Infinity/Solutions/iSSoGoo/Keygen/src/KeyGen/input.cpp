// includes
#include <Windows.h>
#include "resource.h"
#include "input.h"
#include "serial.h"


// This functions dispatches all the messages sent to the window
BOOL CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message) {

		case WM_INITDIALOG: {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_YEAR), EM_SETLIMITTEXT, 4, 0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_MONTH), EM_SETLIMITTEXT, 2, 0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_DAY), EM_SETLIMITTEXT, 2, 0);

			SYSTEMTIME sysTime;
			GetSystemTime(&sysTime);
			SetDlgItemInt(hWnd, IDC_EDIT_YEAR, sysTime.wYear, FALSE);
			SetDlgItemInt(hWnd, IDC_EDIT_MONTH, sysTime.wMonth, FALSE);
			SetDlgItemInt(hWnd, IDC_EDIT_DAY, sysTime.wDay, FALSE);
			SetDlgItemText(hWnd, IDC_EDIT_SERIAL, getSerial(sysTime.wYear, sysTime.wMonth, sysTime.wDay).c_str());

			HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));

			if (hIcon) {
				SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
				SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
				DestroyIcon(hIcon);
			}
						
			break;
		}

		case WM_COMMAND: {
			switch (HIWORD(wParam)) {
				case EN_CHANGE: {
					switch (LOWORD(wParam)) {
						case IDC_EDIT_YEAR:
						case IDC_EDIT_MONTH:
						case IDC_EDIT_DAY: {
							uint32_t year = GetDlgItemInt(hWnd, IDC_EDIT_YEAR, NULL, FALSE);
							uint32_t month = GetDlgItemInt(hWnd, IDC_EDIT_MONTH, NULL, FALSE);
							uint32_t day = GetDlgItemInt(hWnd, IDC_EDIT_DAY, NULL, FALSE);
							SetDlgItemText( hWnd, IDC_EDIT_SERIAL, getSerial(year, month, day).c_str() );
							break;
						}

						default: {
							return DefWindowProc(hWnd, message, wParam, lParam);
						}
					}

					break;
				}

				default: {
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}

			break;
		}

		case WM_LBUTTONDOWN:{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);
			break;
		}

		default:{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return FALSE;
}