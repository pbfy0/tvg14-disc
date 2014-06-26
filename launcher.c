#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
void _run_exe(char* cmd, char* args, char hidden){
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "open";
	ShExecInfo.lpFile = cmd;
	ShExecInfo.lpParameters = args;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = hidden ? SW_HIDE : SW_SHOW;
	ShExecInfo.hInstApp = NULL; 
	ShellExecuteEx(&ShExecInfo);

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}
void run_exe_h(char* cmd, char* args){
	_run_exe(cmd, args, TRUE);
}
void run_exe(char* cmd, char* args){
	_run_exe(cmd, args, FALSE);
}

int APIENTRY WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d){
//int main(void){
	srand(time(NULL));
	char tempfile[1024];
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char tmpdir[1024];// = (char *)getenv("TEMP");
	GetTempPath(sizeof(tmpdir), tmpdir);
	
	sprintf(tempfile, "%stvg14-%d\0", tmpdir, rand());
	char buf[1024];
	CreateDirectory(tempfile, NULL);
	sprintf(buf, "x chrome.7z -o\"%s\\chrome\"", tempfile);
	run_exe_h("7zG.exe", buf);
	memset(buf, 0, 1024);
	SHFILEOPSTRUCT str = {
		NULL,
		FO_COPY,
		"game\0",
		tempfile,
		FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI,
		FALSE,
		0,
		""
	};
	SHFileOperation(&str);
	memset(buf, 0, 1024);
	sprintf(buf, "--user-data-dir=\"%s\\profile\" --start-maximized --allow-file-access-from-files --app=\"%s\\game\\index.html\"", tempfile, tempfile);
	char buf2[1024];
	sprintf(buf2, "%s\\chrome\\chrome.exe", tempfile);
	run_exe(buf2, buf);
	SHFILEOPSTRUCT str2 = {
		NULL,
		FO_DELETE,
		tempfile,
		"\0",
		FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI,
		FALSE,
		0,
		""
	};
	SHFileOperation(&str2);
	//memset(cmd, 0, 1024);
	//sprintf(cmd, "rd /s /q %s", tempfile); // GAH!
	//system(cmd);
}