#include "core.h"

// Function will connect to the vmware api service
BOOL VMware::Connect(LPSTR lpszHostanme, DWORD dwHostPort, LPSTR lpszUsername, LPSTR lpszPassword)
{

	jobHandle = VixHost_Connect(VIX_API_VERSION, CONNTYPE, lpszHostanme, dwHostPort, lpszUsername, lpszPassword, 0, VIX_INVALID_HANDLE, NULL, NULL);

	err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &hostHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}


	Vix_ReleaseHandle(jobHandle);
	return TRUE;

abort:
	if (jobHandle)
		Vix_ReleaseHandle(jobHandle);
	if (vmHandle)
		Vix_ReleaseHandle(vmHandle);
	if (hostHandle)
		VixHost_Disconnect(hostHandle);

	return FALSE;
}

// Function will start the virtual machine and wait until booted up (if specified with mWait)
// Note if mWait is specified, the machine must have vmware tools installed...
BOOL VMware::Start(LPSTR lpszVmxPath, BOOL mWait)
{

	jobHandle = VixVM_Open(hostHandle, lpszVmxPath, NULL, NULL);
	err = VixJob_Wait(jobHandle, VIX_PROPERTY_JOB_RESULT_HANDLE, &vmHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}
	Vix_ReleaseHandle(jobHandle);

	jobHandle = VixVM_PowerOn(vmHandle,	VMPOWEROPTIONS, VIX_INVALID_HANDLE,	NULL, NULL); 
	err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}
	Vix_ReleaseHandle(jobHandle);

	if (mWait)
	{
		jobHandle = VixVM_WaitForToolsInGuest(vmHandle,	300, NULL, NULL); 
		err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
		if (VIX_FAILED(err)) {
			printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
			goto abort;
		}
		
		Vix_ReleaseHandle(jobHandle);
	}


	return TRUE;

abort:
	if (jobHandle)
		Vix_ReleaseHandle(jobHandle);
	if (vmHandle)
		Vix_ReleaseHandle(vmHandle);
	if (hostHandle)
		VixHost_Disconnect(hostHandle);

	return FALSE;
}

// Function will login to the virtual machine
// Guest OS MUST have a password set, and auto login must be enabled on the guest machine
BOOL VMware::Login(LPSTR lpszUsername, LPSTR lpszPassword, BOOL mInteractiveEnvironment)
{

	jobHandle = VixVM_LoginInGuest(vmHandle, lpszUsername, lpszPassword, mInteractiveEnvironment ? VIX_LOGIN_IN_GUEST_REQUIRE_INTERACTIVE_ENVIRONMENT : 0, NULL, NULL);
	err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}

	Vix_ReleaseHandle(jobHandle);
	return TRUE;

abort:
	if (jobHandle)
		Vix_ReleaseHandle(jobHandle);
	if (vmHandle)
		Vix_ReleaseHandle(vmHandle);
	if (hostHandle)
		VixHost_Disconnect(hostHandle);

	return FALSE;
}

// Function will execute a file on the Guest OS (lpszFilePath must be located on the Guest machine)
BOOL VMware::ExecuteFile(LPSTR lpszFilePath, BOOL mWait)
{
	INT nOptions = VIX_RUNPROGRAM_ACTIVATE_WINDOW;

	if (mWait == FALSE)
		nOptions |= VIX_RUNPROGRAM_RETURN_IMMEDIATELY;

	jobHandle = VixVM_RunProgramInGuest(vmHandle, lpszFilePath, NULL /*flags*/, nOptions, VIX_INVALID_HANDLE, NULL, NULL);
	err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}
	
	Vix_ReleaseHandle(jobHandle);
	return TRUE;

abort:
	if (jobHandle)
		Vix_ReleaseHandle(jobHandle);
	if (vmHandle)
		Vix_ReleaseHandle(vmHandle);
	if (hostHandle)
		VixHost_Disconnect(hostHandle);

	return FALSE;
}

BOOL VMware::FileToGuest(LPSTR lpszLocalFile, LPSTR lpszRemoteFile)
{

	jobHandle = VixVM_CopyFileFromHostToGuest(vmHandle, lpszLocalFile, lpszRemoteFile, 0, VIX_INVALID_HANDLE, NULL, NULL); 
	err = VixJob_Wait(jobHandle, VIX_PROPERTY_NONE);
	if (VIX_FAILED(err)) {
		printf("ERROR: %s\n", Vix_GetErrorText(err, NULL));
		goto abort;
	}

	Vix_ReleaseHandle(jobHandle);
	return TRUE;

abort:
	if (jobHandle)
		Vix_ReleaseHandle(jobHandle);
	if (vmHandle)
		Vix_ReleaseHandle(vmHandle);
	if (hostHandle)
		VixHost_Disconnect(hostHandle);

	return FALSE;
}