#include<iostream>
using namespace std;
int k=0,n;
int main(){
     cout<<"盘子数=";
     cin>>n;
     mov(n,'a','b','c');
     return 0;
}
void mov(int n,char a,char b,char c)
{
     if(n==0)
     {
       return;
     }
     mov(n-1,a,b,c);
     k++;
     cout<<k<<":从"<<a<<"->"<<c<<endl;
     mov(n-1,b,a,c);
}
