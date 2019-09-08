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
int c1=0;


void execute3(string str)
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

void executePipe(string str)
{
	//cout<<"In Execute\n";
	c1++;
	string fileNo = to_string(c1);
	string file = "d"+fileNo+".txt";
	char* fileName= (char*)file.c_str();
	
	cout<<file<<" created"<<endl;
	
	
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

void pipee(char* str,int count)
{
	string s1="",s2="";
	int i,j,k;
	//cout<<str<<endl;
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
	int ioFlag=0;
	int doubleIoFlag=0;
	
	for(i=0; i<=count; i++)
	{
		s1="";
		for(j=k; j<strlen(str); j++)
		{
			if(str[j]!='|')
				s1+=str[j];
			else 
				break;
		}
		k=++j;
		
		//cout<<s1<<",";
		if(i==0)
		{
			executePipe(s1);
		}
		else if(i<count)
		{
			string fileNo = to_string(i);
			string file = " d"+fileNo+".txt";
			
			string com="";
			com +=s1+file;
			//cout<<com<<endl;
			executePipe(com);
		}
		else if(i==count)
		{
			string ioCommand="";
			string ioFile="";
			string fileNo = to_string(i);
			string file = " d"+fileNo+".txt";
			
			//cout<<s1;
			
			//Detecting > or >> in pipe Command
			for(int y=0; y<s1.length(); y++)
			{
				if(s1[y]=='>' && s1[y+1]=='>')
				{
					doubleIoFlag=1;
				}
				if(s1[y]=='>')
				{
					ioFlag=1;
					break;
				}
			}
			
			if(ioFlag==1)
			{
				int y;
				for(y=0; y<s1.length(); y++)
				{
					if(s1[y]!=' ')
					{
						if(s1[y]!='>')	
							ioCommand+=s1[y];
						else 
							break;
					}	
				}
				
				if(s1[y+1]=='>')
					y+=2;
				else
					y++;
				for(y; y<s1.length(); y++)
				{
					if(s1[y]!=' ')
						ioFile+=s1[y];

				}
				
				cout<<ioCommand<<","<<ioFile<<endl;
				
				ioCommand +=" "+file;
				executePipe(ioCommand);
				
				fileNo = to_string(i+1);
				file = " d"+fileNo+".txt";
				
				if(doubleIoFlag==1)
				{
					file="d"+fileNo+".txt";
					char* f=(char*)file.c_str();
					char* ifile=(char*)ioFile.c_str();
					int fr = open(f,O_RDONLY);
					int fw = open(ifile, O_WRONLY | O_CREAT | O_APPEND, 0644);
					char c;
					while(read(fr,&c,1)!=0)
						write(fw,&c,1);
					close(fr);
					close(fw);
					return;
				}
				
				string copyCommand="";
				copyCommand ="cp"+file+" "+ioFile;
				cout<<copyCommand<<endl;
				execute3(copyCommand);
				return ;
				
			}
			
			string com="";
			com +=s1+file;
			//cout<<com<<endl;
			execute3(com);
		}
	}
	
	// execute1(s1);
	
	// string com = "";
	// com +=s2+" d.txt";
	// cout<<com<<endl;
	// execute(com);

}

void pipeAlias(char* str,map<string,string> m)
{
	map<string,string>::iterator it;
	//cout<<str<<endl;
	char* command = str;
	char* pch;
	char* args[100];
	string modifiedCommand="";
	
	// cout<<"Map Contents are\n";
	// for(it=m.begin();it!=m.end(); it++)
		// cout<<it->first<<","<<it->second<<endl;
	
	
	
	pch = strtok (command,"|");
	int i=0;
		
	while (pch != NULL)
	{
		args[i] = pch;
		//cout<<pch<<",";
		pch = strtok (NULL, "|");
		i++;
	}
	
	for(int x=0;x<i; x++)
	{
		int found=0;
		//cout<<args[x]<<","<<endl;
		char* s = args[x];
		string com;
		int k;
		
		for(k=0; k<strlen(s); k++)
		{
			if(s[k]!=' ')
				break;
		}
		
		for(k; k<strlen(s); k++)
		{
			if(s[k]!=' ')
				com+=s[k];
			else 
				break;
		}
		
		//cout<<"alias is "<<com<<endl;
		string actualCommand = "";
		
		
		for(it=m.begin();it!=m.end(); it++)
		{
			if(it->second==com)
			{
				found = 1;
				//cout<<com<<" is found\n";
				actualCommand+=it->first;

				for(k; k<strlen(s); k++)
				{
					actualCommand+=s[k];
				}
				break;
			}
		}
		
		if(found==0)
			actualCommand=string(s);
		//cout<<actualCommand<<endl;
		//char* wholeCommand = (char*)actualCommand.c_str();
		if(x<(i-1))
		{	
			modifiedCommand+=actualCommand+"|";
		}	
		else
			modifiedCommand+=actualCommand;
	}
	
	// for(int x=0;x<i; x++)
		
		//cout<<modifiedCommand<<endl;
		str = (char*)modifiedCommand.c_str();
		pipee(str,i-1);
	
}


// int main()
// {
	// while(1)
	// {
		// //c=0;
		// //string str;
		// //getline(cin,str);
		// //char buff[1024];
		// int i,count=0;
		
		// for(i=0; i<str.length(); i++)
		// {
			// if (str[i]=='|')
				// count++;
		// }
		// //cout<<count<<"\n";
		// if(count>0)
		// {
			// pipee(str,count);
		// }
		// else
			// execute(str);
	// }
	// return 0;
// }