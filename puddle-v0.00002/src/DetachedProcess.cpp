#include "DetachedProcess.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#include "Log.h"

DetachedProcess::DetachedProcess(std::string cmd)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(NULL, &cmd[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		Log::get().write(1, "Failed to created process with: " + cmd);
		return;
	}

	//WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

DetachedProcess::~DetachedProcess()
{}