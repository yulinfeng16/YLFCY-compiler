#include<iostream>
#include<ctime>
#include<unistd.h>
#include<cstring>
#include<bits/stdc++.h>
#include<windows.h>
#include<sstream>
#include<new>
#include<conio.h>
#include"max(3).h"
#include<vector>
#include<string>
#include"colorset.h"
using namespace std;
string aaaa;
int yyyyyyy=0;
float to_float(string s);
int hhh();
/*
int fffff111() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	cout << "����̮�����󷴳�\n";
	cout << "  ��������������\n";
	sleep(3);
	cout<<"����ʱ����ΰ��"<<endl;
	sleep(1);
	cout<<"�������������ܿ����?"<<endl;
	sleep(1);
	cout<<"��ӵ���㹻�ĳ���Ԫ�غ�\n ";
	sleep(1);
	cout<<"���۳ɹ�����˺�ѶԳ���������\n ";
	sleep(1);
	cout<<"�󷴳��ʱ��������\n";
	sleep(1);
	cout<<"�����濪ʼ�Ը�����ٶ�̮��\n";
	sleep(1);
	cout<<"Խ��Խ�����ʿ�ʼ���������ľ�£\n";
	sleep(1);
	cout<<" һ�����ʼ��ȼ��е����\n ";
	sleep(1);
	cout<<"���������Ŀ�ʼ����\n ";
	sleep(1);
	cout<<"��������ͳһ������֤��ɡ�\n ";
	sleep(1);
	cout<<"����ʼȫ��ϵ���ٽ�����\n ";
	sleep(1);
	cout<<"��������ϡ�\n";
	sleep(1);
	cout<<" ��ģʽ��׼����ϡ�\n ";
	sleep(1);
	cout<<"������ģʽ������\n ";
	sleep(1);
	cout<<"����ʼ�������泣����\n ";
	sleep(1);
	cout<<"������ɹ��� " << endl;
	sleep(1);

	cout<<"����������\n ";
	sleep(1);
	cout<<"����\n ";
	sleep(1);
	cout<<"�����������������֮��\n ";
	sleep(1);
	cout<<"�����Լ���... ...\n";
	sleep(1);
	cout<<"���������а\n";
	sleep(1);
}*/
int mmmmmm(int a,string b[100000001]);
string b[10000000+1];
int mmmmmm(int a,string b[100000001]) {
	freopen("��Ŀ.ylfcy.cpi","w",stdout);
	for(int ii=1; ii<a; ii++) {
		cout<<b[ii]<<endl;
	}
	fclose(stdout);
}
string h;
int ui,nm;
int main() {
	typedef void (*Hello)();
	HMODULE hMOD=LoadLibrary("dll.dll");
	system("title YLFCY������v0.4.0pre");
	red();
	if(hMOD==NULL) {
		cout<<" |���棺dll.dll����ʧ�ܣ�"<<endl;
	} else {

	}
	Hello hello=(Hello)GetProcAddress(hMOD,"_ZN8DllClass10HelloWorldEv");
	char z=24;
	float u;
#include"keydownprint.h"
	int u1;
	string size="�������루";
	string size1="��������(";
	string size0="��������u��";
	string size2="��������u(";
	string::size_type idx;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	int a=2;
	cout << "1��";
	green();
	cout<<"#useclude_" ;
	blue();
	cout<<"ylfcy.std.h"<<endl;
	gotoxy(NULL,NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	while(1) {
		cout<<a<<"��";
		//cin >> b[a];
		getline(cin,b[a]);
		if(b[a]=="comp_(0)"||b[a]=="COMP_(0)"||b[a]=="comp_��0��"||b[a]=="COMP_��0��"||b[a]=="���д���"||b[a]=="ִ�д���") {
			break;
		}
		if(b[a]=="�������") {
			yellow();
			cout<<"��ע�⣬�˲���ֻ�ܱ�����룬���Ĵ��뽫�������롣"<<endl;
			white(0);
			mmmmmm(a,b);
		}
		if(b[a]=="quit"||b[a]=="^q") {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|/**/FOREGROUND_RED);
			cout<<" ������Ҫ��ֹ�༭����Y=1;N=Other��"<<endl<<" ��ȷ������";
			cin>>yyyyyyy;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			if(yyyyyyy==1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				system("taskkill /f /im ��Ŀ1.exe");
			} else {
				yellow();
				cout<<" ���˳���ȡ������"<<a<<"�д��뽫�������롣"<<endl;
				white(0);
			}
		}
		a++;
	}/**/SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	cout<<"_________________"<<endl;
	cout<<"���н����"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	for(int i=1; i<=a; i++) {
		size="�������루";
		size1="��������(";
		if(b[i]=="���Դ���") {
			hello();
		} else {
			if(isNum(b[i])) {
				cout<<b[i]<<endl;
			} else {
				idx=b[i].find(size);
				if(idx == string::npos ) { //�����ڡ�
					idx=b[i].find(size1);
					if(idx == string::npos ) {

					} else {
						u=to_float(b[i]);
						u1=u;
						if(u-u1>=0.5) {
							cout<<u1+1<<endl;
						} else {
							cout<<u1<<endl;
						}
					}
				} else { //���ڡ�
					u=to_float(b[i]);
					u1=u;
					if(u-u1>=0.5) {
						cout<<u1+1<<endl;
					} else {
						cout<<u1<<endl;
					}
				}
				idx=b[i].find(size0);
				if(idx == string::npos ) { //�����ڡ�
					idx=b[i].find(size2);
					if(idx == string::npos ) {
					} else {
						u=to_float(b[i]);
						u1=u;
						cout<<u1+1<<endl;
					}
				} else { //���ڡ�
					u=to_float(b[i]);
					u1=u;
					cout<<u1+1<<endl;
				}
				size="��������d��";
				size1="��������d(";
				idx=b[i].find(size);
				if(idx == string::npos ) { //�����ڡ�
					idx=b[i].find(size1);
					if(idx == string::npos ) {

					} else {
						u=to_float(b[i]);
						u1=u;
						cout<<u1<<endl;
					}
				} else { //���ڡ�
					u=to_float(b[i]);
					u1=u;
					cout<<u1<<endl;
				}
				if(b[i]=="����"||b[i]=="help") {
					system("start ����.txt");
				}
				if(b[i]=="print_help"||b[i]=="���°���") {
					hhh();
				}
				if(b[i]=="�򿪼�����") {
					system("start ccc.exe");
				}
				if(b[i]=="�򿪼��̼��") {
					system("start ���̼��.exe");
				}
				size="��������ʾ��ִ�� ";
				size1="��������ִ�� ";
				idx=b[i].find(size);
				int zifuchuann=0;
				if(idx==string::npos) {
					idx=b[i].find(size1);
					if(idx!=string::npos) {
						//b[i].erase(b[i].end());
						char cha[255];
						for(int j=13; j<=b[i].length(); j++,zifuchuann++) {
							cha[zifuchuann]=b[i][j];
							//cout<<b[i][j];
						}
						/*cout<<endl;*/
						goto sb250;
					}
				} else {
					char cha[255];
					//b[i].erase(b[i].end());
					for(int j=17; j<=b[i].length(); j++,zifuchuann++) {
						cha[zifuchuann]=b[i][j];
						//cout<<b[i][j];
					}
					//cout<<endl;
sb250:/*a[strlen(cha)-1]=0;*/
					char chab[255];
					for(int k=0; k<strlen(cha); k++) {
						chab[k]=cha[k];
					}

					cout<<"+======ִ�н��=======-"<<endl;
					system(chab);
					cout<<"-=====================-"<<endl;
				}
				//if(b[i]=="open_")
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	cout<<"������ɣ�";
	system("pause");
	return 0;
}
float to_float(string s) {
	int i = 0,n=0;
	int point_index = s.find('.');
	float result= 0,under_0=0;//under_0�洢С������
	if (count(s.begin(), s.end(), '.')>1) {
		return 0;//�ַ�����ֻ����1����0��С���㣬��Ȼ�����˳�
	}
	if (s.find('.') != -1) { //�ַ�������С����
		if (point_index >= 1 && point_index<s.size()-1) { //С����λ�ú����������ַ�����1λ,�Ҳ��������һλ
			for (i = 0; i <= point_index - 1; i++) { //������������
				if (s[i] >= '0'&&s[i] <= '9') {
					result = result * 10 + s[i] - 48;
				}
			}
			for (i = s.size() - 1; i >= point_index-1 ; i--) { //����С������
				if (s[i] >= '0'&&s[i] <= '9') {
					if (i == point_index-1) {
						under_0 = under_0 * 0.1 + 0;//i=С����ǰһλ��under_0+0
					} else {
						under_0 = under_0* 0.1 + s[i] - 48;
					}
				}
			}
			result = result + under_0;//���������ֺ�С���������
		}
	} else { //�ַ���ֻ����������
		for (i = 0; i <= s.size() - 1; i++) {
			if (s[i] >= '0'&&s[i] <= '9') {
				result= result * 10 + s[i] - 48;
			}
		}
	}
	return result;
}
int hhh() {
	freopen("����.txt","w",stdout);
	cout<<"Ŀǰ������䣺"<<endl<<"����������������"<<endl<<"���Դ���"<<endl<<endl;
	cout<<"��������ı���"<<endl<<"����������������\n"<<"�������루x��"<<endl<<"��������(x)"<<endl<<endl;
	cout<<"���x��������������ֵ��x����>0,������������δ֪�������\n"<<"����������������\n"<<"��������u��x��\n ��������u(x)"<<endl;
	cout<<endl<<"���x��2147483647����������ֵ��x����>0,������������δ֪�������\n"<<"����������������\n"<<endl;
	cout<<"��������d��x��\n ��������d(x)\n\n ���x��-2147483647����������ֵ��\n x����>0,������������δ֪�������"<<endl;
	cout<<"����������������"<<endl<<"���д���\n\n��ʼ���롣\n"<<"����������������"<<endl<<"����"<<endl<<"help"<<endl<<endl<<"��������ļ�\n"<<"����������������\n";
	cout<<"print_help"<<endl<<endl<<"�ڰ�װĿ¼��������ļ���\n����������������"<<endl;
	cout<<"quit"<<endl<<"^q"<<endl<<endl<<"�رձ�д���ڡ�"<<endl<<"����������������\n"<<"�������"<<endl<<endl<<"���������������װĿ¼��"<<endl;
	cout<<"����������������\n"<<"�򿪼�����"<<endl<<endl<<"�򿪳������ü�������\n"<<"����������������\n"<<"�򿪼��̼�� \n\n"<<"�򿪳������ü��̼�⡣"<<endl<<"����������������\n";
	cout<<"��������ִ�� str"<<"��������ʾ��ִ�� str"<<"\n\n"<<"�������У�cmd.exe��ִ��strָ��"<<endl;
	fclose(stdout);
}
string jjj();
string jjj() {
	string mmm="����������������";
	return mmm;
}

