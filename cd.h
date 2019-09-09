#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include <stdio.h>

using namespace std;

int cd(char *str) 
{
	//char* command = (char*) str.c_str();
	string path="";
	
	for(int i=2; i<strlen(str); i++)
	{
		if(str[i]!=' ')
			path+=str[i];
	}
	
	if(path=="")
		return chdir(getenv("HOME"));
	char* p = (char*)path.c_str(); 
	return chdir(p);
}
