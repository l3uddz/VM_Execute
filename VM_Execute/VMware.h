#define  VMPOWEROPTIONS VIX_VMPOWEROP_LAUNCH_GUI
#define  CONNTYPE    VIX_SERVICEPROVIDER_VMWARE_WORKSTATION

class VMware
{
public:
	BOOL Connect(LPSTR lpszHostanme, DWORD dwHostPort, LPSTR lpszUsername, LPSTR lpszPassword);
	BOOL Start(LPSTR lpszVmxPath, BOOL mWait);
	BOOL Login(LPSTR lpszUsername, LPSTR lpszPassword, BOOL mInteractiveEnvironment);
	BOOL ExecuteFile(LPSTR lpszFilePath, BOOL mWait);
	BOOL FileToGuest(LPSTR lpszLocalFile, LPSTR lpszRemoteFile);

private:
	VixError err;
	VixHandle hostHandle = VIX_INVALID_HANDLE;
	VixHandle jobHandle = VIX_INVALID_HANDLE;
	VixHandle vmHandle = VIX_INVALID_HANDLE;
};