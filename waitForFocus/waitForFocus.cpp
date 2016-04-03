// waitForFocus.cpp : This program waits for a window of a specified name to load
//

#include "stdafx.h"
//#include <Windows.h>
//#include <Winuser.h>
#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <atlstr.h>
//#include <ShellApi.h>
#include <iostream>
#include "atlstr.h"

using namespace std;

LPWSTR pszMem;

BOOL CALLBACK FindWindowBySubstr(HWND hwnd, LPARAM substring)
{
	//cout << "start:" << endl;
	//cout << LPCTSTR(substring) << endl;
	//_tprintf(LPCTSTR(substring));
	//cout << "endl" << endl;
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];

	if (GetWindowText(hwnd, windowTitle, TITLE_SIZE))
	{
		//_tprintf(TEXT("%s\n"), windowTitle);
		// Uncomment to print all windows being enumerated
		string fstr = CW2A(windowTitle);
		if (fstr.find(string("Chrome")) != string::npos) {
			cout << "Found window!" << endl;
		}
		if (_tcsstr(windowTitle, LPCTSTR(substring)) != NULL)
		{
			// We found the window! Stop enumerating.
			cout << substring << endl;
			_tprintf(TEXT("%s\n"), windowTitle);
			return false;
		}
	}
	return true; // Need to continue enumerating windows
}

int main(int argc, char* argv[])
{
	if (argc > 2) {
		cout << "Dear user this program takes 1 argument not " << argc - 1 << endl;
		cout << "The argument should be part of the name of the window you want to wait for" << endl;
	}
	else if (argc == 2) {
		if (string(argv[1]) == "/h" || string(argv[1]) == "-h" || string(argv[1]) == "/?" || string(argv[1]) == "-?"){
			cout << "This program takes one input, part of the window name, and waits for that window to load" << endl;
		}
		else {
			cout << "\"" << argv[1] << "\"" << endl;
			CHAR substring[] = "Chrome";
			cout << EnumWindows(FindWindowBySubstr, (LPARAM)substring) << endl;
			bool nfound = true;
			while (nfound) {
				HWND WINAPI GetForegroundWindow(void);
				pszMem = (LPWSTR)VirtualAlloc((LPVOID)NULL,
					(DWORD)(50), MEM_COMMIT,
					PAGE_READWRITE);
				GetWindowText(GetForegroundWindow(), pszMem,
					50);
				cout << GetForegroundWindow() << ", ";
				string resstr = CW2A(pszMem);
				wcout << pszMem << endl;
				if (resstr.find(string(argv[1])) != string::npos && !(resstr.find(string("waitForFocus.exe")) != string::npos)) {
					cout << "found!" << endl;
					nfound = false;
				}
				else {
					Sleep(1000);
				}
			}

		}
	}
	else if (argc == 1) {
		cout << "This program takes one input, part of the window name, and waits for that window to load" << endl;
	}
	else {
		cout << "How did you manage to pass a negative number of flags?" << endl;
	}
    return 0;
}

