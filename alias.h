#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<map>
#include<iterator>

map<string,string> aliasMap;

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
		{
			cout<<args[0]<<": command not found\n";
		}
	}
	else
		wait(0);
}
void open(char *str)
{
	string fileName="";
	string extension="";
	int i;
	for(i=0; i<strlen(str); i++ )
	{
		if(str[i]==' ')
			break;
	}
	
	for(i;i<strlen(str);i++)
	{
		if(str[i]!=' ')
			break;
	}
	
	for(i;i<strlen(str);i++)
	{
		if(str[i]!='.')
		{
			fileName+=str[i];
		}
		else
			break;
	}
	for(++i;i<strlen(str);i++)
	{
		if(str[i]!='.')
		{
			extension+=str[i];
		}
		else
			break;
	}
	string command = "";
	if(extension==".mp4")
	{
		command+= "vlc "+fileName+"."+extension;
		execute(command);
	}
	else
	{
		command+= "xdg-open "+fileName+"."+extension;
		execute(command);
	}
	
}

void check1(char* str)
{
	map<string,string>::iterator it;
	string s="";
	int i=0;
	
	for(; i<strlen(str); i++)
	{
		if(str[i]!=' ')
		{
			s+=str[i];
		}
		else 
			break;
	}
	
	for(it=aliasMap.begin();it!=aliasMap.end(); it++)
	{
		if(it->second==s)
		{
			s="";
			s+=it->first;
			
			string ca = s;
			
			for(;i<strlen(str);i++)
			{
				s+=str[i];
			}
			
			// if(ca=="cat")
			// {
				
			// }
			execute(s);
			return ;
		}
	}
	execute(str);
}

void check(string command,string alias)
{
	map<string,string>::iterator it;
	
	for(it=aliasMap.begin();it!=aliasMap.end(); it++)
	{
		if(it->second==alias)
		{
			aliasMap.erase(it);
			aliasMap[command]=alias;
			return;
		}
	}
	
	aliasMap[command] = alias;
}

void aliass(char* str)
{
	int i,j,k=0;
	string com="";
	char* args[100];
	vector<string> v; 
	
	for(i=0; i<strlen(str); i++)
		if(str[i]==' ')
			break;
	
	for(++i;i<strlen(str); i++)
		if(str[i]!='=')
			com+=str[i];
		else
			break;
	
	v.push_back(com);
	
	for(com="",i+=2;i<strlen(str);i++)
		if(str[i]!='"')
			com+=str[i];
		else
			break;
		
	v.push_back(com);
	
	check(v[1],v[0]);
}

void history(vector<char*> v)
{
	for(int i=0; i<v.size(); i++)
	{
		cout<<v[i]<<endl;
	}
}
void grepp(char* str)
{
	string s="";
	for(int i=0; i<strlen(str); i++)
	{
		if(str[i]!='"')
			s+=str[i];
	}
	execute(s);
}
