#include "core.h"

LPSTR lpszService_Host = NULL;
DWORD dwService_Port = 0;
LPSTR lpszService_User = NULL;
LPSTR lpszService_Pass = NULL;

LPSTR lpszUsing_VM = NULL;

LPSTR lpszVM_Path = NULL;
LPSTR lpszVM_User = NULL;
LPSTR lpszVM_Pass = NULL;
LPSTR lpszVM_Dir  = NULL;

LPSTR lpszUseFile = NULL;

int main(int argc, char** argv)
{
	VMware VM;
	LPSTR lpszRemotePath = NULL, lpszFileName = NULL;

	if (argv[1] == NULL) {
		printf("Please specify a file to run VMwared!\n");
		goto abort;
	}
	lpszUseFile = argv[1];

	// Read Settings from Config
	lpszService_Host = Config::ReadString("vmservice", "host");
	lpszService_User = Config::ReadString("vmservice", "usr");
	lpszService_Pass = Config::ReadString("vmservice", "pwd");
	dwService_Port =   Config::ReadNumber("vmservice", "port");

	lpszUsing_VM = Config::ReadString("using", "machine");
	if (lpszUsing_VM == NULL) 
	{
		printf("Please specify a VM to use inside config.ini, (using\\machine)\n");
		goto abort;
	}
	lpszVM_Path = Config::ReadString(lpszUsing_VM, "vmx");
	lpszVM_User = Config::ReadString(lpszUsing_VM, "usr");
	lpszVM_Pass = Config::ReadString(lpszUsing_VM, "pwd");
	lpszVM_Dir =  Config::ReadString(lpszUsing_VM, "dir");

	printf("Using Machine:\n");
	printf("\tVMX: \"%s\"\n", lpszVM_Path);
	printf("\tUSR: \"%s\"\n", lpszVM_User);
	printf("\tPWD: \"%s\"\n", lpszVM_Pass);
	printf("\tDIR: \"%s\"\n\n", lpszVM_Dir);

	// Connect to vmware api service
	printf("Connecting to VMware API Service...\n");
	if (VM.Connect(lpszService_Host, dwService_Port, lpszService_User, lpszService_Pass))
		printf("Connected!\n\n");
	else {
		printf("Error connecting..\n\n");
		goto abort;
	}

	// Start virtual machine and wait until vmwaretools is loaded
	printf("Starting Virtual Machine: %s\n", lpszUsing_VM);
	if (VM.Start(lpszVM_Path, TRUE))
		printf("Started!\n\n");
	else {
		printf("Error starting..\n\n");
		goto abort;
	}

	// 10 sec sleep so VM should be ready to login
	printf("Sleep for 10 seconds...\n\n");
	Sleep(10 * 1000);

	// Login to the Guest OS (VM)
	printf("Logging into %s\n", lpszUsing_VM);
	if (VM.Login(lpszVM_User, lpszVM_Pass, TRUE))
		printf("Logged in as %s:%s!\n\n", lpszVM_User, lpszVM_Pass);
	else {
		printf("Error logging in as %s:%s...\n\n", lpszVM_User, lpszVM_Pass);
		goto abort;
	}

	// Transfer file to Guest OS (VM)
	lpszRemotePath = RemotePath(lpszUseFile, lpszVM_Dir);
	lpszFileName = strrchr(lpszUseFile, '\\');
	lpszFileName++;

	printf("Copying %s to \"%s\" on %s\n", lpszFileName, lpszRemotePath, lpszUsing_VM);
	if (VM.FileToGuest(lpszUseFile, lpszRemotePath))
		printf("Successfully copied %s\n\n", lpszFileName);
	else {
		printf("Error copying %s\n\n", lpszFileName);
		goto abort;
	}

	// Execute file and do not wait (specify TRUE if you need it to wait for executed process to terminate)
	printf("Executing %s on %s\n", lpszFileName, lpszUsing_VM);
	if (VM.ExecuteFile(lpszRemotePath, FALSE))
		printf("Executed %s!\n\n", lpszFileName);
	else {
		printf("Error executing %s...\n\n", lpszFileName);
		goto abort;
	}

	printf("Finished!\n");

abort:

	if (lpszService_Host) Mem::Free(lpszService_Host);
	if (lpszService_User) Mem::Free(lpszService_User);
	if (lpszService_Pass) Mem::Free(lpszService_Pass);

	if (lpszUsing_VM) Mem::Free(lpszUsing_VM);

	if (lpszVM_Path) Mem::Free(lpszVM_Path);
	if (lpszVM_User) Mem::Free(lpszVM_User);
	if (lpszVM_Pass) Mem::Free(lpszVM_Pass);
	if (lpszVM_Dir)  Mem::Free(lpszVM_Dir);
	
	system("pause");
	return 0;
}


LPSTR RemotePath(LPSTR lpszLocalPath, LPSTR lpszRemotePath)
{
	static CHAR szRemotePath[MAX_PATH] = { 0 };
	CHAR szTmp[MAX_PATH] = { 0 };
	LPSTR pch;

	lstrcpyA(szTmp, lpszLocalPath);
	pch = strrchr(szTmp, '\\');
	
	lstrcpyA(szRemotePath, lpszRemotePath);
	lstrcatA(szRemotePath, pch);

	return szRemotePath;
}
