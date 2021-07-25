#include<bits/stdc++.h>
using namespace std;
int a1[10000],a[5001],b[5001];
int main()
{
  /*在这写✍你的代码*/
  int n;
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>a1[i];
  }
  if(n%2==0)
  {
    for(int i=0;i<n/2;i++)
    {
      a[i]=a1[i];
    }
    for(int i=n/2;i<n;i++)
    {
      b[i]=a1[i];
    }
    for(int i=0;i<n/2;i++)
    {
      cout<<a[i]<<" ";
    }
    for(int i=n/2;i<n;i++)
    {
      cout<<b[i]<<endl;
    }
  }
  else
  {
    for(int i=0;i<ceil(n/2);i++)
    {
      a[i]=a1[i];
    }
    for(int i=floor(n/2)+1;i<n;i++)
    {
      b[i]=a1[i];
    }
    for(int i=0;i<ceil(n/2);i++)
    {
      cout<<a[i]<<" ";
    }
    for(int i=ceil(n/2);i<n;i++)
    {
      cout<<b[i]<<endl;
    }
  }
  return 0;
}
