#include<windows.h>
#include<stdio.h>
int main() {
	int hwndDOS = GetForegroundWindow();

	ShowWindow(hwndDOS, SW_HIDE);
	MessageBox(NULL,"ת���������Ժ����ԡ�","Oops!",MB_OK|MB_ICONWARNING);
}
