#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<map>
#include<iterator>

#include <readline/readline.h>
#include <readline/history.h>

#include "echo.h"
#include "io_redirect.h"
#include "pipe.h"
#include "cd.h"


using namespace std;

map<string,string> aliasMap;
int pipeFlag=0,ioFlag=0;

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
			//perror("exec");
			cout<<args[0]<<": command not found\n";
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
	
	{
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

int main()
{
	while(1)
	{
		// if(command[0]==NULL)
			// continue;
		
		
		char* str;
		str = readline(">> "); 
		if (strlen(str) > 0) 
		{
			add_history(str);
		}
		
		
		string al = "alias";
		string gr = "grep";
		string ec = "echo";
		string c = "cd";
		string ope = "open";
		
		//cout<<"Enter the command";
		//getline(cin,str);
		int i,j,k,l,m,n,o,count=0;
		int op=1;
		
		for(i=0; i<al.length(); i++)
		{
			if(str[i]!=al[i])
				break;
		}
		
		for(j=0; j<al.length(); j++)
		{
			if(str[j]!=gr[j])
				break;
		}
		
		for(k=0; k<ec.length(); k++)
		{
			if(str[k]!=ec[k])
				break;
			
		}
		
		for(n=0; n<strlen(str); n++)
		{
			if(str[n]!=c[n])
				break;
		}
		
		for(o=0; o<strlen(str); o++)
		{
			if(str[o]!=ope[o])
				break;
		}
		
		for(l=0; l<strlen(str); l++)
		{
			if(str[l] == '>')
			{
				ioFlag=1;
				break;
			}
		}
		
		if(str[l+1]=='>')
		op=2;
		
		for(m=0; m<strlen(str); m++)
		{
			if (str[m]=='|')
				count++;
		}
		
		if(i==5)
			aliass(str);
		else if(j==4)
			grepp(str);
		else if(k==4)
			ECHO(str);
		else if(count>0)
		{
			//alias(str);
			c1=0;
			cout<<"HI from pipe\n";
			pipeAlias(str,aliasMap);
		}
		else if(l<strlen(str))
			io(str,op);
		else if(n==2)
		{
			if (cd(str) < 0) 
			{
                perror(str);
            }
		}
		else if(o==4)
		{
			open(str);
		}
		else
			check1(str);
	}
	return 0;
}