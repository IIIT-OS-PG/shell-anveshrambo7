#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<map>
#include<iterator>

using namespace std;

map<string,string> m;

void execute(string str)
{
	char* command = (char*) str.c_str();
	char* pch;
	char* args[100];
	
	pch = strtok (command," ");
	int i=0;
		
	while (pch != NULL)
	{
		args[i] = pch;
		pch = strtok (NULL, " ");
		i++;
	}
	
	args[i] = NULL;
	
	
	pid_t pid = fork();
		
	if(pid==0)
	{
		if(execvp(args[0],args)==-1)
			perror("exec");
	}
	
}

void check1(string str)
{
	map<string,string>::iterator it;
	string s="";
	int i=0;
	
	for(; i<str.length(); i++)
	{
		if(str[i]!=' ')
		{
			s+=str[i];
		}
		else 
			break;
	}
	
	for(it=m.begin();it!=m.end(); it++)
	{
		if(it->second==s)
		{
			s="";
			s+=it->first;
			for(;i<str.length();i++)
			{
				s+=str[i];
			}
			
			execute(s);
			return ;
		}
	}
	execute(str);
}

void check(string command,string alias)
{
	map<string,string>::iterator it;
	
	for(it=m.begin();it!=m.end(); it++)
	{
		if(it->second==alias)
		{
			m.erase(it);
			m[command]=alias;
			return;
		}
	}
	
	m[command] = alias;
}

void aliass(string str)
{
	int i,j,k=0;
	string com="";
	char* args[100];
	vector<string> v; 
	
	for(i=0; i<str.length(); i++)
		if(str[i]==' ')
			break;
	
	for(++i;i<str.length(); i++)
		if(str[i]!='=')
			com+=str[i];
		else
			break;
	
	v.push_back(com);
	
	for(com="",i+=2;i<str.length();i++)
		if(str[i]!='"')
			com+=str[i];
		else
			break;
		
	v.push_back(com);
	
	check(v[1],v[0]);
	
	// else
	// {
		// cout<<v[0]<<", "<<v[1]<<"\n";
		
		// char* command = (char*) v[1].c_str();
		// char* pch;
		
		// pch = strtok (command," ");
		// i=0;
			
		// while (pch != NULL)
		// {
			// args[i] = pch;
			// pch = strtok (NULL, " ");
			// i++;
		// }
		
		// args[i] = NULL;
		// i++;
		
		// pid_t pid = fork();
		
		// if(pid==0)
		// {
			//system("./bashRC.sh");
			//cout<<"child:"<<pid<<"\n";
			// if(execvp(args[0],args)==-1)
				// perror("exec");
		// }
	// }
}

int main()
{
	while(1)
	{
		string str;
		string al = "alias";
		//cout<<"Enter the command";
		getline(cin,str);
		int i;
		
		for(i=0; i<al.length(); i++)
		{
			if(str[i]!=al[i])
				break;
		}
		
		if(i==5)
			aliass(str);
		else
			check1(str);
		
	}
	return 0;
}