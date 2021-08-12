#include<iostream>
#include<windows.h>
#include"keydownprint.h"
using namespace std;
#define KEY_DOWN(VK_NONAME)((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
#pragma G++ diagnostic ignored "-Wunused-but-set-variable"
#pragma G++ diagnostic ignored "-Wunused-variable"
#pragma G++ diagnostic ignored "-Wformat="
#pragma G++ diagnostic ignored "-Wreturn-type"
#pragma G++ diagnostic ignored "-Wpointer-arith"
#pragma disable(Warnning No)
void check_printkey(char c,int a){
	if(a==NULL){
	if(!KEY_DOWN(c))
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
	cout<<" "<<c<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}else{
if(!KEY_DOWN(c))
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
	cout<<" "<<c<<" ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
}
bool checkkey(char cc){
	if(KEY_DOWN(cc))
	{
		return true;
	}
	else
	{
		return false;
	}
}
