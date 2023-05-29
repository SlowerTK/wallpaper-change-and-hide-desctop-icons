#include <cstdio>
#include <Shlobj.h>
#include <tchar.h>
#define UNICODE // <<= remember if you set it, set it before include windows or shit happens with printf 'n stuff
#include <Windows.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

const int strMaxLen = 255;

HWND hwndSysListView32 = NULL;
TCHAR *msgNoClassName = _T("noClassName");
TCHAR *msgNoWindowText = _T("noWindowText");
TCHAR *msgEnumChildProc = _T("\t<%s> <%s> [0x%p] [0x%x]\n");

BOOL CALLBACK EnumChildProcFull(HWND hwnd, LPARAM lParam)
{
	size_t rClassName, rWindowText;
	LPTSTR lpClassName = (LPTSTR)malloc(strMaxLen);
	LPTSTR lpWindowText = (LPTSTR)malloc(strMaxLen);
	rClassName = GetClassName(hwnd, lpClassName, strMaxLen);
	rWindowText = GetWindowText(hwnd, lpWindowText, strMaxLen);
	_tprintf(msgEnumChildProc, rClassName > 0 ? lpClassName : msgNoClassName, rWindowText > 0 ? lpWindowText : msgNoWindowText, hwnd, lParam);
	free(lpWindowText);
	free(lpClassName);
	return true;
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	size_t rClassName, rWindowText;
	LPTSTR lpClassName = (LPTSTR)malloc(strMaxLen);
	rClassName = GetClassName(hwnd, lpClassName, strMaxLen);
	if (lstrcmp(_T("SysListView32"), lpClassName) == 0)
	{
		LPTSTR lpWindowText = (LPTSTR)malloc(strMaxLen);
		rWindowText = GetWindowText(hwnd, lpWindowText, strMaxLen);
		if ((rWindowText > 0) && (lstrcmp(_T("FolderView"), lpWindowText) == 0))
		{
			hwndSysListView32 = hwnd;
		}
		free(lpWindowText);
	}
	free(lpClassName);
	return true;
}

void printHelp()
{
	_tprintf(_T("The program need a parameter to work.\n"
				"iconHider.exe test\t->\tIt does nothing apart printing all the desktop childs.\n"
				"iconHider.exe hax\t->\tShow/Hide the icons using a workaround if with the api don't work.\n"));
	system("PAUSE");
}

int main(int argc, char **argv)
{
	if (argc <= 1 || argc > 2)
	{
		printHelp();
	}
	else
	{
		if (strcmp(argv[1], "-test") == 0)
		{
			EnumChildWindows(GetDesktopWindow(), *EnumChildProcFull, 0x123);
			system("PAUSE");
		}
		else if (strcmp(argv[1], "-hax") == 0)
		{
			EnumChildWindows(GetDesktopWindow(), *EnumChildProc, 0x123);
			if (hwndSysListView32 != NULL)
			{
				ShowWindow(hwndSysListView32, !IsWindowVisible(hwndSysListView32));
			}
			else
			{
				_tprintf(_T("hwndSysListView32 == NULL [da fuq???]\n"));
				system("PAUSE");
			}
		}
		else
		{
			printHelp();
		}
	}
	return 0;
}