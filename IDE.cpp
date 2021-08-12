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
	cout << "逆向坍缩·大反冲\n";
	cout << "  ━━〈◆〉━━\n";
	sleep(3);
	cout<<"空想时代的伟力"<<endl;
	sleep(1);
	cout<<"岂是理世会所能抗衡的?"<<endl;
	sleep(1);
	cout<<"在拥有足够的超重元素后\n ";
	sleep(1);
	cout<<"方舟成功将大撕裂对冲至反宇宙\n ";
	sleep(1);
	cout<<"大反冲的时代来临了\n";
	sleep(1);
	cout<<"正宇宙开始以更快的速度坍缩\n";
	sleep(1);
	cout<<"越来越多物质开始向宇宙中心聚拢\n";
	sleep(1);
	cout<<" 一个物资极度集中的天国\n ";
	sleep(1);
	cout<<"在宇宙中心开始生成\n ";
	sleep(1);
	cout<<"》超宇宙统一理论验证完成《\n ";
	sleep(1);
	cout<<"》开始全体系超速进化《\n ";
	sleep(1);
	cout<<"》进化完毕《\n";
	sleep(1);
	cout<<" 》模式五准备完毕《\n ";
	sleep(1);
	cout<<"》空想模式启动《\n ";
	sleep(1);
	cout<<"》开始浸入宇宙常数《\n ";
	sleep(1);
	cout<<"》浸入成功《 " << endl;
	sleep(1);

	cout<<"－－·－－\n ";
	sleep(1);
	cout<<"最终\n ";
	sleep(1);
	cout<<"您将凌驾在所有文明之上\n ";
	sleep(1);
	cout<<"塑造自己的... ...\n";
	sleep(1);
	cout<<"【蓝星乌托邦】\n";
	sleep(1);
}*/
int mmmmmm(int a,string b[100000001]);
string b[10000000+1];
int mmmmmm(int a,string b[100000001]) {
	freopen("项目.ylfcy.cpi","w",stdout);
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
	system("title YLFCY编译器v0.4.0pre");
	red();
	if(hMOD==NULL) {
		cout<<" |警告：dll.dll载入失败！"<<endl;
	} else {

	}
	Hello hello=(Hello)GetProcAddress(hMOD,"_ZN8DllClass10HelloWorldEv");
	char z=24;
	float u;
#include"keydownprint.h"
	int u1;
	string size="四舍五入（";
	string size1="四舍五入(";
	string size0="四舍五入u（";
	string size2="四舍五入u(";
	string::size_type idx;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	int a=2;
	cout << "1│";
	green();
	cout<<"#useclude_" ;
	blue();
	cout<<"ylfcy.std.h"<<endl;
	gotoxy(NULL,NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	while(1) {
		cout<<a<<"│";
		//cin >> b[a];
		getline(cin,b[a]);
		if(b[a]=="comp_(0)"||b[a]=="COMP_(0)"||b[a]=="comp_（0）"||b[a]=="COMP_（0）"||b[a]=="运行代码"||b[a]=="执行代码") {
			break;
		}
		if(b[a]=="保存代码") {
			yellow();
			cout<<"请注意，此操作只能保存代码，您的代码将不被编译。"<<endl;
			white(0);
			mmmmmm(a,b);
		}
		if(b[a]=="quit"||b[a]=="^q") {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|/**/FOREGROUND_RED);
			cout<<" │您将要终止编辑！（Y=1;N=Other）"<<endl<<" │确定？：";
			cin>>yyyyyyy;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			if(yyyyyyy==1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				system("taskkill /f /im 项目1.exe");
			} else {
				yellow();
				cout<<" │退出已取消，第"<<a<<"行代码将不被编译。"<<endl;
				white(0);
			}
		}
		a++;
	}/**/SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	cout<<"_________________"<<endl;
	cout<<"运行结果："<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	for(int i=1; i<=a; i++) {
		size="四舍五入（";
		size1="四舍五入(";
		if(b[i]=="测试窗口") {
			hello();
		} else {
			if(isNum(b[i])) {
				cout<<b[i]<<endl;
			} else {
				idx=b[i].find(size);
				if(idx == string::npos ) { //不存在。
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
				} else { //存在。
					u=to_float(b[i]);
					u1=u;
					if(u-u1>=0.5) {
						cout<<u1+1<<endl;
					} else {
						cout<<u1<<endl;
					}
				}
				idx=b[i].find(size0);
				if(idx == string::npos ) { //不存在。
					idx=b[i].find(size2);
					if(idx == string::npos ) {
					} else {
						u=to_float(b[i]);
						u1=u;
						cout<<u1+1<<endl;
					}
				} else { //存在。
					u=to_float(b[i]);
					u1=u;
					cout<<u1+1<<endl;
				}
				size="四舍五入d（";
				size1="四舍五入d(";
				idx=b[i].find(size);
				if(idx == string::npos ) { //不存在。
					idx=b[i].find(size1);
					if(idx == string::npos ) {

					} else {
						u=to_float(b[i]);
						u1=u;
						cout<<u1<<endl;
					}
				} else { //存在。
					u=to_float(b[i]);
					u1=u;
					cout<<u1<<endl;
				}
				if(b[i]=="帮助"||b[i]=="help") {
					system("start 帮助.txt");
				}
				if(b[i]=="print_help"||b[i]=="更新帮助") {
					hhh();
				}
				if(b[i]=="打开计算器") {
					system("start ccc.exe");
				}
				if(b[i]=="打开键盘监测") {
					system("start 键盘监测.exe");
				}
				size="让命令提示符执行 ";
				size1="让命令行执行 ";
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

					cout<<"+======执行结果=======-"<<endl;
					system(chab);
					cout<<"-=====================-"<<endl;
				}
				//if(b[i]=="open_")
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	cout<<"运行完成，";
	system("pause");
	return 0;
}
float to_float(string s) {
	int i = 0,n=0;
	int point_index = s.find('.');
	float result= 0,under_0=0;//under_0存储小数部分
	if (count(s.begin(), s.end(), '.')>1) {
		return 0;//字符串里只能有1个或0个小数点，不然出错退出
	}
	if (s.find('.') != -1) { //字符串里有小数点
		if (point_index >= 1 && point_index<s.size()-1) { //小数点位置合理，不能在字符串第1位,且不能在最后一位
			for (i = 0; i <= point_index - 1; i++) { //计算整数部分
				if (s[i] >= '0'&&s[i] <= '9') {
					result = result * 10 + s[i] - 48;
				}
			}
			for (i = s.size() - 1; i >= point_index-1 ; i--) { //计算小数部分
				if (s[i] >= '0'&&s[i] <= '9') {
					if (i == point_index-1) {
						under_0 = under_0 * 0.1 + 0;//i=小数点前一位，under_0+0
					} else {
						under_0 = under_0* 0.1 + s[i] - 48;
					}
				}
			}
			result = result + under_0;//把整数部分和小数部分相加
		}
	} else { //字符串只有整数部分
		for (i = 0; i <= s.size() - 1; i++) {
			if (s[i] >= '0'&&s[i] <= '9') {
				result= result * 10 + s[i] - 48;
			}
		}
	}
	return result;
}
int hhh() {
	freopen("帮助.txt","w",stdout);
	cout<<"目前可用语句："<<endl<<"————————"<<endl<<"测试窗口"<<endl<<endl;
	cout<<"输出测试文本。"<<endl<<"————————\n"<<"四舍五入（x）"<<endl<<"四舍五入(x)"<<endl<<endl;
	cout<<"输出x四舍五入后的整数值。x必须>0,否则会可能引起未知结果错误。\n"<<"————————\n"<<"四舍五入u（x）\n 四舍五入u(x)"<<endl;
	cout<<endl<<"输出x向2147483647舍入后的整数值。x必须>0,否则会可能引起未知结果错误。\n"<<"————————\n"<<endl;
	cout<<"四舍五入d（x）\n 四舍五入d(x)\n\n 输出x向-2147483647舍入后的整数值。\n x必须>0,否则会可能引起未知结果错误。"<<endl;
	cout<<"————————"<<endl<<"运行代码\n\n开始编译。\n"<<"————————"<<endl<<"帮助"<<endl<<"help"<<endl<<endl<<"唤起帮助文件\n"<<"————————\n";
	cout<<"print_help"<<endl<<endl<<"在安装目录输出帮助文件。\n————————"<<endl;
	cout<<"quit"<<endl<<"^q"<<endl<<endl<<"关闭编写窗口。"<<endl<<"————————\n"<<"保存代码"<<endl<<endl<<"仅将代码输出至安装目录。"<<endl;
	cout<<"————————\n"<<"打开计算器"<<endl<<endl<<"打开程序内置计算器。\n"<<"————————\n"<<"打开键盘监测 \n\n"<<"打开程序内置键盘监测。"<<endl<<"————————\n";
	cout<<"让命令行执行 str"<<"让命令提示符执行 str"<<"\n\n"<<"让命令行（cmd.exe）执行str指令"<<endl;
	fclose(stdout);
}
string jjj();
string jjj() {
	string mmm="————————";
	return mmm;
}

