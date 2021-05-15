#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int loop_forever = 1;

void on_sigint()
{
	printf("You are press CTRL + C! Good bye!");
	loop_forever = 0;
}
int main()
{
	printf("Welcome to IT007, I am 19521383!\n");
	pid_t pid;
	pid = fork();
	if(pid == 0)
		execl("/usr/bin/gedit","gedit","abcd.txt",NULL);
	else
	{
		signal(SIGINT, on_sigint);
		while(loop_forever){}
	}
	return 0;
}
