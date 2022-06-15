#include<bits/stdc++.h>
using namespace std;
int main()
{
    bool a[26];
    for(int i=0;i<26;i++)
    {
        a[i]=false;
    }
    int n;
    int tot=0,wtot=0;
    string str;
    cin>>n>>str;
    for(int i=0;i<str.length();i++)
    {
       if(a[str[i]-65]==false)
       {
           if(tot<n)
           {
               tot++;
           a[str[i]-65]=true;}
           else
           {
               wtot++;
               a[str[i]-65]=true;
           }
       }
       else
       {
           tot--;
           a[str[i]-65]=false;
       }
    }
    cout<<wtot<<endl;
    return 0;
}
