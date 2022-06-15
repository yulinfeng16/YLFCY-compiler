#include<bits/stdc++.h>
#include<windows.h>
#include<wchar.h>
#include<Shlobj.h>
#define elif else if
//感谢：https://www.5axxw.com/questions/content/cuot5e
using namespace std;
string str[100000];
BOOL SetConsoleColor(WORD wAttributes) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;

	return SetConsoleTextAttribute(hConsole, wAttributes);
}
string GetEeEPath() {
	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	string strPath2 = "";
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0;				//删除文件名，只获得路径字串
	strPath2 = (string)szFilePath;
	return strPath2;
}//感谢：https://www.csdn.net/tags/NtTaEg1sMzAtYmxvZwO0O0OO0O0O.html
void charTowchar(const char *chr, wchar_t *wchar, int size) {
	MultiByteToWideChar( CP_ACP, 0, chr,
	                     strlen(chr)+1, wchar, size/sizeof(wchar[0]) );
}//感谢：https://blog.csdn.net/weixin_30826761/article/details/96334010
wchar_t *wchar = (wchar_t *)malloc(sizeof(wchar_t) * 64);
string stringbianliangming[100000];
int main() {
	for(int u=0; u<100000; u++) {
		stringbianliangming[u]="";
	}
	cout<<"请将文件拖入这里后按回车  -->   ";
	string wjm;
	getline(cin,wjm);
	wjm.erase(std::remove(wjm.begin(),wjm.end(),'\"'),wjm.end());
	string str_url = _pgmptr;
	for(int i=str_url.length(); i>=0; i--) {
		if(str_url[i]=='\\') {
			break;
		} else {
			str_url[i]=0;
		}
	}
	cout<<"convertmaster: convert "<<wjm<<" to "<<str_url<<"..."<<endl;
	freopen(wjm.c_str(),"r",stdin);
	FILE *fp;
	fp=fopen("out.cpp","w");
	fflush(fp);
	FILE *pcon;
	pcon=fopen("CON","w");
	ofstream fout1("out.cpp",ios::out);
	fprintf(fp,"#include<bits/stdc++.h>\n using namespace std;\n #define elif else if\n int main(){");
	fprintf(pcon,"print includes...\n");
	fprintf(fp,"//By YLFCY\n");
	string::size_type idx;
	string finds="输出";
	string bianliang="定义变量";
	string zhengxing="整型";
	string floatss="浮点型";
	string stringss="字符串";
	string boolss="布尔型";
	int zhegeshizhendeu=0;
	for(int i=0; getline(cin,str[i]); i++) {
		idx=str[i].find(finds);
		if(i!=0) {
			fprintf(fp,"\n");
		}
		if(idx!=string::npos) {
			fprintf(fp,"cout<<");
			if(str[i][4]=='"') {
				fprintf(fp,"\"");
				string aaaaa="";
				for(int k=5; k<=str[i].length()-2; k++) {
					aaaaa+=str[i][k];
				}
				fprintf(fp,aaaaa.c_str());
				fprintf(fp,"\"");
			} else {
				string aaaaa="";
				for(int k=4; k<=str[i].length()-1; k++) {
					aaaaa+=str[i][k];
				}
				fprintf(fp,aaaaa.c_str());
			}
			fprintf(fp,";");
		} else {
			idx=str[i].find(bianliang);
			if(idx!=string::npos) {
				string::size_type zx=str[i].find(zhengxing);
				string::size_type fd=str[i].find(floatss);
				string::size_type zf=str[i].find(stringss);
				string::size_type br=str[i].find(boolss);
				if(zx!=string::npos) {
					fprintf(fp,"int ");
				}
				if(fd!=string::npos) {
					fprintf(fp,"double ");
				}
				if(zf!=string::npos) {
					fprintf(fp,"string ");
				}
				if(br!=string::npos) {
					fprintf(fp,"bool ");
				}
				string strstrstrstr;
				for(int jjj=8; str[i][jjj]!='='; jjj++) {
					strstrstrstr+=str[i][jjj];
					//if(!strstrstrstr[0]<0)
				}
				fprintf(fp,strstrstrstr.c_str());
				fprintf(fp," = ");
				bool lr;
				if(zx!=string::npos) {
					lr=false;
					string scscsc="";
					for(int jjj=8; jjj<str[i].length()-5; jjj++) {
						if(lr) {
							if(str[i][jjj]>='0'&&str[i][jjj]<='9') {
								scscsc+=str[i][jjj];
							}
						} else {
							if(str[i][jjj]=='=') {
								lr=true;
							}
						}
					}
					charTowchar(scscsc.c_str(), wchar, sizeof(wchar_t) * 64);
					fwprintf(fp,wchar);
				}
				if(fd!=string::npos) {
					lr=false;
					string scscsc="";
					for(int jjj=8; jjj<str[i].length()-7; jjj++) {
						if(lr) {
							if((str[i][jjj]>='0'&&str[i][jjj]<='9')||str[i][jjj]=='.') {
								scscsc+=str[i][jjj];
							}
						} else {
							if(str[i][jjj]=='=') {
								lr=true;
							}
						}
					}
					fprintf(fp,scscsc.c_str());
				}
				if(zf!=string::npos) {
					stringbianliangming[zhegeshizhendeu]=strstrstrstr;
					fprintf(fp,"\"");
					lr=false;
					string scscsc="";
					for(int jjj=8; jjj<str[i].length()-7; jjj++) {
						if(lr) {
							if((str[i][jjj]>='A'&&str[i][jjj]<='Z')||(str[i][jjj]>='a'&&str[i][jjj]<='z')||(str[i][jjj]>='0'&&str[i][jjj]<='9')) {
								scscsc+=str[i][jjj];
							} else {
								system("start CE.exe");
								exit(0);
							}
						} else {
							if(str[i][jjj]=='=') {
								lr=true;
							}
						}
					}
					zhegeshizhendeu++;
					fprintf(fp,scscsc.c_str());
					fprintf(fp,"\"");
				}
				if(br!=string::npos) {
					//fprintf(fp,"test");
					lr=false;
					string scscsc="";
					for(int jjj=7; jjj<=str[i].length()-8; jjj++) {
						if(lr) {
							//if((str[i][jjj]>='A'&&str[i][jjj]<='Z')||(str[i][jjj]>='a'&&str[i][jjj]<='z')) {
							scscsc+=str[i][jjj];
						} else {
							if(str[i][jjj]=='=') {
								lr=true;
							}
						}
					}
					if(scscsc=="true"||scscsc=="True"||scscsc=="TRUE") {
						fprintf(fp,"true");
					} else {
						if(scscsc=="false"||scscsc=="False"||scscsc=="FALSE") {
							fprintf(fp,"false");
						} else {
							system("start CE.exe");
							exit(0);
						}
					}
				}
				fprintf(fp,";");
			} else {
				string xiugaibianliang="修改变量";
				idx=str[i].find(xiugaibianliang);
				if(idx!=string::npos) {
					string _strstrstrstr;
					for(int jjj=8; str[i][jjj]!='='; jjj++) {
						_strstrstrstr+=str[i][jjj];
						//if(!strstrstrstr[0]<0)
					}
					//cout<<_strstrstrstr<<endl;
					fprintf(fp,_strstrstrstr.c_str());
					fprintf(fp," = ");
					bool _isstring=false;
					for(int w=0; w<zhegeshizhendeu; w++) {
						if(_strstrstrstr==stringbianliangming[w]) {
							_isstring=true;
						}
					}
					if(_isstring) {
						fprintf(fp,"\"");
						bool lr=false;
						string scscsc="";
						for(int jjj=8; jjj<str[i].length(); jjj++) {
							if(lr) {
								if((str[i][jjj]>='A'&&str[i][jjj]<='Z')||(str[i][jjj]>='a'&&str[i][jjj]<='z')||(str[i][jjj]>='0'&&str[i][jjj]<='9')) {
									scscsc+=str[i][jjj];
								} else {
									system("start CE.exe");
									exit(0);
								}
							} else {
								if(str[i][jjj]=='=') {
									lr=true;
								}
							}
						}
						fprintf(fp,scscsc.c_str());
						fprintf(fp,"\"");
					} else {
						bool lr=false;
						string scscsc="";
						for(int jjj=0; jjj<str[i].length(); jjj++) {
							if(lr) {
								if(str[i][jjj]!='"') {
									scscsc+=str[i][jjj];
								} else {
									system("start CE.exe");
									exit(0);
								}
							} else {
								if(str[i][jjj]=='=') {
									lr=true;
								}
							}
						}
						fprintf(fp,scscsc.c_str());
					}
					fprintf(fp,";");
				} else {
					string ruguo="如果";
					idx=str[i].find(ruguo);
					if(idx!=string::npos) {
						fprintf(fp,"if(");
						string abababab="";
						for(int jj=4; jj<str[i].length()-2; jj++) {
							abababab+=str[i][jj];
						}
						fprintf(fp,abababab.c_str());
						fprintf(fp,"){");
					} else {
						if(str[i]=="结束") {
							fprintf(fp,"}");
						}
						elif(str[i]=="否则") {
							fprintf(fp,"else{");
						}
						elif(str[i]=="换行") {
							fprintf(fp,"cout<<endl;");
						}
						else {
						}
					}
				}
			}
		}
		fprintf(pcon,"第");
		int aaaaaaaaaaaaaaaa=i+1;
		char shuchushuchushuchu[256];
		itoa(aaaaaaaaaaaaaaaa,shuchushuchushuchu,10);
		fprintf(pcon,shuchushuchushuchu);
		fprintf(pcon,"行完成...\n");
	}
	fprintf(fp,"\nsystem(\"pause\");\nreturn 0;}");
	fclose(fp);
	fclose(pcon);
	cout<<"转换好的c++代码文件已经存放至 ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	cout<<str_url<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bout.cpp";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<" 并准备好编译。"<<endl;
	cout<<"开始编译独立文件..."<<endl;
	cout<<"...准备中"<<endl;
	Sleep(2000);
	string bianyimingling="MinGW64\\bin\\g++.exe ";
	char desktoppath[255];
	SHGetSpecialFolderPath(
	    NULL,
	    desktoppath,
	    CSIDL_DESKTOPDIRECTORY,
	    FALSE
	);
	bianyimingling+=" \"";
	bianyimingling+=GetEeEPath();
	bianyimingling+="\\out.cpp\" -o \"";
	bianyimingling+=desktoppath;
	bianyimingling+="\\out.exe\" -m32 -I\"%CppIncludeDir0%\" -I\"%CppIncludeDir1%\" -I\"%CppIncludeDir2%\" -I\"%CppIncludeDir2%\\c++\" -L\"%LibDir0%\" -static-libgcc -m32";
	SetConsoleColor(FOREGROUND_GREEN);
	cout<<"Cmd:"<<bianyimingling<<endl;
	SetConsoleColor(FOREGROUND_GREEN| FOREGROUND_INTENSITY| BACKGROUND_INTENSITY);
	cout<<"- 输出文件名："<<desktoppath<<"\\out.exe"<<endl;
	SetConsoleColor(FOREGROUND_RED);
	freopen("CON", "r", stdin);
	if(system(bianyimingling.c_str())!=0)
	{
		cout<<"编译错误！"<<endl;
	}else{
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<"编译进程结束。"<<endl;}
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("pause");
	return 0;
}
