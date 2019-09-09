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
//int c=0;
void execute2(string str)
{
	int status;
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
		{	//perror("exec");
			status=127;
			perror("exec");
		}
		else
		{
			cout<<"HI";
			status=0;
		}
	}
	else
	wait(0);
}

void executeIO(string str)
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
		int fd1 = open("IO.txt",O_RDWR | O_CREAT | O_TRUNC,0666);
		dup2(fd1,1);
		close(fd1);
		
			if(execvp(args[0],args)==-1)
				perror("exec");
		
	}
	else 
		wait(0);
} 

void io(char* str,int op)
{
	int i,j,k;
	char buff[100000];
	string command="",fileName="";
	
	for(i=0; i<strlen(str); i++)
	{
		if(str[i]!='>')
			command+=str[i];
		else
			break;
	}
	
	executeIO(command);
	
	command = "";
	
	if(op==2)
		j=i+2;
	else
		j=++i;
	for(; j<strlen(str); j++)
	{
		if(str[j]!=' ')
		fileName+=str[j];
	}
	
	char *file = (char*)fileName.c_str();
	cout<<file<<endl;
	
	if(op==1)
	{
		command+="cp IO.txt "+fileName;
		execute2(command);
	}
	else
	{
		int fr = open("IO.txt",O_RDONLY);
		int fw = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		char c;
		while(read(fr,&c,1)!=0)
			write(fw,&c,1);
		close(fr);
		close(fw);
	}
}

