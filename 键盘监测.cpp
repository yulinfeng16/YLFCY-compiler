#include<iostream>
#include<cmath>
#include<string>
#include<iostream>
#include<windows.h>
#define KEY_DOWN(VK_NONAME)((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
using namespace std;
int color(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
int check(char c,int a) {
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
}}
int main() {
	while(1) {
		check('Q',NULL);
		check('W',NULL);
		check('E',NULL);
		check('R',NULL);
		check('T',NULL);
		check('Y',NULL);
		check('U',NULL);
		check('I',NULL);
		check('O',NULL);
		check('P',NULL);
		printf("\n\n ");
		check('A',NULL);
		check('S',NULL);
		check('D',NULL);
		check('F',NULL);
		check('G',NULL);
		check('H',NULL);
		check('J',NULL);
		check('K',NULL);
		check('L',NULL);
		printf("\n\n   ");
		check('Z',NULL);
		check('X',NULL);
		check('C',NULL);
		check('V',NULL);
		check('B',NULL);
		check('N',NULL);
		check('M',NULL);
		printf("\n\n");
		check(' ',NULL);
		check(' ',NULL);
		check('0',NULL);
		check('1',NULL);
		check('2',NULL);
		check('3',NULL);
		check('4',NULL);
		check('5',NULL);
		check('6',NULL);
		check('7',NULL);
		check('8',NULL);
		check('9',NULL);
		printf("\n\n");
		Sleep(20);
		system("cls");
	}
	return 0;
}
