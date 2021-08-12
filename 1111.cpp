#include "1111.h"
#include<bits/stdc++.h>
#include<cstring>

int daima(string a,string b)
{
	string::size_type idx;
	idx=a.find(b);
	if(idx==string::npos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
