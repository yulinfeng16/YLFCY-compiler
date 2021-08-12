#include<windows.h>
#include<cmath>
#include "max(3).h"
#include "stdio.h"
#include<windows.h>
#include<string>
#include<bits/stdc++.h>
using namespace std;
int red()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
}
int blue()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
}
int green()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
}
int purple()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
}
int yellow()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
 } 
int white(int i)
{
	if(i==0)
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);	
else
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
}
int fu_sushu(int m)
{
	int i,k;
	k=(int)sqrt((double)m);
	for(i=2;i<=k;i++)
	{
		if(m%i==0)
		{
			break;
		}
	}
	if(i>k)
        printf("%d是素数\n",m);
    else
        printf("%d不是素数\n",m);
}
int gotoxy(int x, int y) {
	if(x!=NULL&&y!=NULL){
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}}
bool isNum(std::string str) {
	stringstream sin(str);
	double d;
	char c;
	if(!(sin >> d)) {
		return false;
	}
	if (sin >> c) {
		return false;
	}
	return true;
}
