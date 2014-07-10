
namespace Config
{
	LPSTR GetConfigPath();
	LPSTR ReadString(LPSTR lpszSection, LPSTR lpszSetting);
	DWORD ReadNumber(LPSTR lpszSection, LPSTR lpszSetting);
}