#include<bits/stdc++.h>
#include"ylfcy.h"
using namespace std;
struct aaaa{
	string studentname;
	int totalscore;
};
int mmax;
aaaa aa[100000];
int chengjipaixu(int n)
{
	string _max;
	_max.clear();
	for(int i=0;i<n;i++)
	{
		cin>>aa[i].studentname>>aa[i].totalscore;
		if(i==0)
		{
			mmax=aa[0].totalscore;
			_max=aa[0].studentname;
		}
		else
		{
			if(aa[i].totalscore>=mmax)
			{
				mmax=aa[i].totalscore;
				_max=aa[i].studentname;
			}
		}
	}
	cout<<_max;
	return 0;
}
