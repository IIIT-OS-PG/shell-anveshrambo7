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

void executeIO(string str)
{
	
	// cout<<"In Execute\n";
	// c++;
	// string fileNo = to_string(c);
	// string file = "IO"+fileNo+".txt";
	// char* fileName= (char*)file.c_str();
	
	// cout<<file<<endl;
	
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

void io(string str,int op)
{
	int i,j,k;
	char buff[100000];
	string command="",fileName="";
	
	for(i=0; i<str.length(); i++)
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
	for(; j<str.length(); j++)
	{
		if(str[j]!=' ')
		fileName+=str[j];
	}
	char *file = (char*)fileName.c_str();
	
	if(op==1)
	{
		command+="cp IO.txt "+fileName;
		execute(command);
	}
	else
	{
		int fr = open("IO.txt",O_RDONLY);
		int bytes=read(fr,&buff,100000);
		int fw = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		write(fw,&buff,fw);
	}
}

int main()
{
	int op=1;
	string str;
	getline(cin,str);
	
	int i;
	
	for(i=0; i<str.length(); i++)
	{
		if(str[i] == '>')
			break;
	}
	if(str[i+1]=='>')
		op=2;
	if(i<str.length())
		io(str,op);
	else
		execute(str);
	
	return 0;
}