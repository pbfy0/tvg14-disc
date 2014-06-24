#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

int APIENTRY WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d){
	srand(time(NULL));
	char tempfile[1024];
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char tmpdir[1024];// = (char *)getenv("TEMP");
	GetEnvironmentVariable("TEMP", tmpdir, sizeof(tmpdir));
	
	sprintf(tempfile, "%s\\tvg14-%d\0", tmpdir, rand());
	char cmd[1024];
	sprintf(cmd, "--user-data-dir=%s --start-maximized --allow-file-access-from-files --app=\"%s\\game\\index.html\"", tempfile, cwd);
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "open";
	ShExecInfo.lpFile = "chrome\\chrome.exe";
	ShExecInfo.lpParameters = cmd;   
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo);

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	SHFILEOPSTRUCT str = {
		NULL,
		FO_DELETE,
		tempfile,
		"",
		FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI,
		FALSE,
		0,
		""
	};
	SHFileOperation(&str);
	//memset(cmd, 0, 1024);
	//sprintf(cmd, "rd /s /q %s", tempfile); // GAH!
	//system(cmd);
}