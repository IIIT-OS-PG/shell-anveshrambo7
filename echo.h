#include<iostream>
#include<map>
#include<string>
#include<stdlib.h>
using namespace std;

map<const char *,const char*> variables;
string ma="Map Created";
void set()
{
	variables["PATH"] = getenv("PATH");
	variables["HOME"] = getenv("HOME");
	variables["USER"] = getenv("USER");
	variables["HOSTNAME"] = getenv("HOSTNAME");
	variables["PS1"] = getenv("PS1");
}

void ECHO(char* str)
{
	
	set();
	//cout<<"echo\n";
	int i;
	string a = "",b="";
	//cout<<str<<"\n";
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]==' ')
			break;
	}
	
	for(; i<strlen(str); i++)
	{
		if(str[i]!=' ')
			break;
	}
	
	int j=i;
	if(str[j]=='$' && str[j+1]!='$')
	{
		for(++j;j<strlen(str); j++)
			b+=str[j];
		//cout<<b<<endl;
		char* var = (char *)b.c_str();
		 map<const char *,const char*>::iterator it;
		for(it=variables.begin(); it!=variables.end(); it++)
			if(strcmp(it->first,var)==0)
			cout<<it->second<<"\n";
		
		return;
	}
	if(str[j]=='$'&&str[j+1] == '$')
	{
		cout<<getpid()<<endl;
		return ;
	}
	if(str[j]=='$' && str[j+1] == '?')
	{
		cout<<getpid()<<endl;
		return ;
	}
	for(++i;i<strlen(str); i++)
	{
		if(str[i]!='"')
			a+=str[i];
	}
	
	cout<<a<<"\n";
}


// int main()
// {
	// string str;
	// getline(cin,str);
	// string e = "echo";
	// int i;
	
	// for(i=0; i<str.length(); i++)
	// {
		// if(str[i]!=e[i])
			// break;
		
	// }
	
	// // set();
	// // map<const char *,const char*>::iterator it;
	// // for(it=variables.begin(); it!=variables.end(); it++)
		// // cout<<it->first<<" "<<it->second<<"\n";
	
	// if(i==4)
		// ECHO(str);
	
	// return 0;
// }		