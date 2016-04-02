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

using namespace std;

LPWSTR pszMem;

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

