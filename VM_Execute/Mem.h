
namespace Mem
{
	LPVOID Alloc(DWORD dwSize);
	LPVOID ReAlloc(LPVOID lpData, DWORD dwNewSize);
	BOOL Free(LPVOID lpData);
	DWORD Size(LPVOID lpData);
}