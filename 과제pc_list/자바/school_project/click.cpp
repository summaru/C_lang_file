#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


int main()
{
	FreeConsole();
		
	char *link = "\\jre1.8.0_131\\bin\\java.exe";
	char Path[MAX_PATH];
	char parameter[100];
	int len = 0;
	FILE *fp;
	
	memset(Path,0,sizeof(MAX_PATH));
	memset(parameter,0,sizeof(100));
	
	GetCurrentDirectory(MAX_PATH, Path);
	strcat(Path,link);
	
	fp = fopen("�Ű�����.txt","r");
	if(fp == NULL)
	{
		fp = fopen("�Ű�����.txt","w+");
		return 0;
	}
	
	fgets(parameter,100,fp);
	
	ShellExecute(NULL,
	"open",
	Path,
	parameter,
	NULL,
	SW_SHOW
	);
	
	return 0;
}
