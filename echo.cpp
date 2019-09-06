#include<iostream>
#include<map>
#include<string>
#include<stdlib.h>
using namespace std;

map<const char *,const char*> variables;

void set()
{
	variables["PATH"] = getenv("PATH");
	variables["HOME"] = getenv("HOME");
	variables["USER"] = getenv("USER");
	variables["HOSTNAME"] = getenv("HOSTNAME");
	variables["PS1"] = getenv("PS1");
}
void ECHO(string str)
{
	int i;
	string a = "";
	cout<<str<<"\n";
	for(i=0; i<str.length(); i++)
	{
		if(str[i]==' ')
			break;
	}
	
	for(; i<str.length(); i++)
	{
		if(str[i]!=' ')
			break;
	}
	
	for(++i;i<str.length(); i++)
	{
		if(str[i]!='"')
			a+=str[i];
	}
	
	cout<<a;
}
int main()
{
	string str;
	getline(cin,str);
	string e = "echo";
	int i;
	
	for(i=0; i<str.length(); i++)
	{
		if(str[i]!=e[i])
			break;
		
	}
	
	// set();
	// map<const char *,const char*>::iterator it;
	// for(it=variables.begin(); it!=variables.end(); it++)
		// cout<<it->first<<" "<<it->second<<"\n";
	
	if(i==4)
		ECHO(str);
	
	return 0;
}		