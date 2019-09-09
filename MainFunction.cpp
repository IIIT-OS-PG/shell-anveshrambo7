#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<map>
#include<iterator>
#include <limits.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "echo.h"
#include "io_redirect.h"
#include "pipe.h"
#include "cd.h"
#include "alias.h"


using namespace std;


int pipeFlag=0,ioFlag=0;

int main()
{
	setMAP();
	
	vector<char* > commandHistory;
	while(1)
	{
		char* str;
		char cwd[PATH_MAX];
		string dr="";
		getcwd(cwd,sizeof(cwd));
		//cout<<cwd;
		dr=string(cwd);
		dr+="$ ";
		cout<<"\u001b[36;1m"<<dr<<"\u001b[0m";
		str = readline(""); 
		if (strlen(str) > 0) 
		{
			add_history(str);
			commandHistory.push_back(str);
		}
		
		string al 	= "alias";
		string gr 	= "grep";
		string ec 	= "echo";
		string c 	= "cd";
		string ope 	= "open";
		string hist = "history";
		
		int i,j,k,l,m,n,o,p,count=0;
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
				
		for(p=0; p<strlen(str); p++)
		{
			if(str[p]!=hist[p])
				break;
		}
		
		if(i==5)
			aliass(str);
		else if(j==4)
			grepp(str);
		else if(k==4)
			ECHO(str);
		else if(count>0)
		{
			c1=0;
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
		else if(p==7)
		{
			history(commandHistory);
		}
		else
			check1(str);
			
	}
	return 0;
}