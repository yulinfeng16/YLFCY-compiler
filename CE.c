#include<windows.h>
#include<stdio.h>
int main() {
	int hwndDOS = GetForegroundWindow();

	ShowWindow(hwndDOS, SW_HIDE);
	MessageBox(NULL,"转换出错。请稍后重试。","Oops!",MB_OK|MB_ICONWARNING);
}
