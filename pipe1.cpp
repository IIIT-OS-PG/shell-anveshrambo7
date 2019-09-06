#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include<sys/wait.h>

using namespace std;
int c=0;

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
	else
	wait(0);
	
}

void execute1(string str)
{
	 cout<<"In Execute\n";
	c++;
	string fileNo = to_string(c);
	string file = "d"+fileNo+".txt";
	char* fileName= (char*)file.c_str();
	
	cout<<file<<endl;
	
	
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
		int fd1 = open(fileName,O_RDWR | O_CREAT | O_TRUNC,0666);
		dup2(fd1,1);
		close(fd1);
		
			if(execvp(args[0],args)==-1)
				perror("exec");
		
	}
	else 
		wait(0);
}

void pipee(string str,int count)
{
	string s1="",s2="";
	int i,j,k;
	
	{
	// for(i=0; i<str.length(); i++)
	// {
		
		// if(str[i]!='|')
			// s1+=str[i];
		// else break;
	// }
	
	// for(++i; i<str.length(); i++)
	// {
		// if(str[i]!='|')
			// s2+=str[i];
		// else
			// break;
	// }
	}
	
	j=0;
	k=0;
	
	for(i=0; i<=count; i++)
	{
		s1="";
		for(j=k; j<str.length(); j++)
		{
			if(str[j]!='|')
				s1+=str[j];
			else break;
		}
		k=++j;
		
		if(i==0)
		{
			execute1(s1);
		}
		else if(i<count)
		{
			string fileNo = to_string(i);
			string file = " d"+fileNo+".txt";
			
			string com="";
			com +=s1+file;
			cout<<com<<endl;
			execute1(com);
		}
		else if(i==count)
		{
			string fileNo = to_string(i);
			string file = " d"+fileNo+".txt";
			
			string com="";
			com +=s1+file;
			cout<<com<<endl;
			execute(com);
		}
	}
	
	// execute1(s1);
	
	// string com = "";
	// com +=s2+" d.txt";
	// cout<<com<<endl;
	// execute(com);

}

int main()
{
	while(1)
	{
		c=0;
		string str;
		getline(cin,str);
		char buff[1024];
		int i,count=0;
		
		for(i=0; i<str.length(); i++)
		{
			if (str[i]=='|')
				count++;
		}
		//cout<<count<<"\n";
		if(count>0)
		{
			pipee(str,count);
		}
		else
			execute(str);
	}
	return 0;
}