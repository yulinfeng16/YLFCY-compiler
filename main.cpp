#include <bits/stdc++.h>
#include"graphics.h"
#include<windows.h>
#define GRAY 0xaaaaaa
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void child_button_generate(int brox,int broy,int daxiao);
int textxycache[2];/*Do not edit!*/
/* ����Ŀʹ�þɰ�graphicsSDK���ƶ��� */
void child_button_generate(int brox,int broy,int daxiao) {
	setlinestyle_with_style_thickness(PS_SOLID,2);
	rectangle(brox-15*daxiao,broy-5*daxiao,brox+15*daxiao,broy+5*daxiao);
	textxycache[0]=brox-15*daxiao+2;
	textxycache[1]=broy-5*daxiao+3;
	setfillcolor(0xfefefe);
	floodfill(brox,broy,GRAY);
	//return 0;
}
int main(int argc, char** argv) {
	textxycache[0]=0;
	textxycache[1]=0;
	initgraph_with_flag(300,100,NOMINIMIZE);
	setbkcolor(0xd1eeee);
	cleardevice();
	setcolor(0x000000);
	settextstyle(14, 0, _T("Consolas"));
	wchar_t s[]=L"���ڼ����������";
	outtextxy(50,25,LPCTSTR(s));
	Sleep(10000);
	graphdefaults();
	initgraph_with_flag(300,300,NOMINIMIZE);
	setbkcolor(0xd1eeee);
	cleardevice();
	setcolor(0x000000);
	settextstyle(14, 0, _T("Consolas"));
	outtextxy(50,25,LPCTSTR(s));
	setcolor(GRAY);
	line(-100,75,1000,75);
	setcolor(0x0000ff);
	setlinestyle_with_style_thickness(PS_SOLID,5);
	circle(30,100,14);
	setfillcolor(0x004fff);
	floodfill(30,100,0x0000ff);
	setcolor(0xffffff);
	setbkmode(TRANSPARENT);
	outtextxy(27,95,LPCSTR(L"X"));
	setcolor(0x000000);
	outtextxy(50,100,LPCSTR(L" �����޷����ӵ���������"));
	outtextxy(50,115,LPCSTR(L" ���ܴ˰汾��ֹͣ�ṩ֧�ֺܾ�,"));
	outtextxy(50,130,LPCSTR(L" ���߷����������˹��ϡ�"));
	setcolor(GRAY);
	child_button_generate(250,260,2);
	setcolor(0x000000);
	outtextxy(textxycache[0],textxycache[1],LPCSTR(L"ȷ�� (O)"));
	while(1) {
		if(MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if(msg.uMsg==WM_LBUTTONDOWN) {
				if(msg.x>=textxycache[0]-2&&msg.x<=250+30&&msg.y>=textxycache[1]-3&&msg.y<=260+10)
				{
					break;
				 }
				 else
				 {
				 	Sleep(10);
				  } 
			}
		}
	}
	closegraph();
	return 0;
}
