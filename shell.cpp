#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<vector>
#include<string.h>

using namespace std;

int cd(char *path) 
{
	
    return chdir(path);
}
int main()
{
	while(1)
	{
		char* args[10];
		vector<string> v;
		string str;
		getline(cin,str);
		
		
		char* command = (char*) str.c_str();
		string newLine="\n";
		if(command[0]==NULL)
			continue;
		char* pch;
		pch = strtok (command," ");
		int i=0;
		
		while (pch != NULL)
		{
			//printf ("%s\n",pch);
			args[i] = pch;
			pch = strtok (NULL, " ");
			i++;
		}
		args[i] = NULL;
		i++;
		
		
		
		
		if (strcmp(args[0], "cd") == 0) {
            if (cd(args[1]) < 0) {
                perror(args[1]);
            }

            continue;
        }
		
		for(int j=0; j<i; j++)
		{
			cout<<args[j]<<"\n";
		}
		/* char* args[3];
		string ls = "ls";
		string ls1 = "-l";
		args[0] = (char*) ls.c_str();
		args[1] = (char*) ls1.c_str();
		args[2] = null; */
		
		pid_t pid = fork();
		
		if(pid==0)
		{
			cout<<"child:"<<pid<<"\n";
			if(execvp(args[0],args)==-1)
				perror("exec");
		}

		if(pid>0)
		{
			wait(0);
			cout<<"parent:"<<pid<<"\n";	
		}
	}
	return 0;
}
