#include "core.h"

LPVOID Mem::Alloc(DWORD dwSize)
{
	return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
}

LPVOID Mem::ReAlloc(LPVOID lpData, DWORD dwNewSize)
{
	return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, lpData, dwNewSize);
}

BOOL Mem::Free(LPVOID lpData)
{
	if (lpData == NULL) return TRUE;
	return HeapFree(GetProcessHeap(), 0, lpData);
}

DWORD Mem::Size(LPVOID lpData)
{
	return (DWORD)HeapSize(GetProcessHeap(), 0, lpData);
}
