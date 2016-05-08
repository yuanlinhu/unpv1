

//#include "unp.h"
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 256
#define err_sys printf

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	sockaddr_in servaddr;

	if(argc != 2) 
	{
		printf("usage: a.out <IPaddress>");

	}	

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) 
	{
				
	}

	if(connect(sockfd, (const sockaddr*)&servaddr, sizeof(servaddr)) < 0) 
	{
		err_sys("connect error");
	}

	while( (n = read(sockfd, recvline, MAXLINE)) > 0) 
	{
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
			err_sys("fputs error");


	}

	if(n < 0) 
	{
		err_sys("read error");
	}

	exit(0);
}
