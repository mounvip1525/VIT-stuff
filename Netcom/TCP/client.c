#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
int main(int argc, char *argv[])
{
    int sockfd,portno,n;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    if(argc<3){
        printf("Input format: ./client (loopback adress) (port number)");
        exit(1);
    }
    portno=atoi(argv[2]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("Error in opening c");
        exit(1);
    }
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
        printf("Connection failed");
        exit(1);
    }
    while(1){
        bzero(buffer,1024);
        fgets(buffer,1024,stdin);
        n=write(sockfd,buffer,strlen(buffer));
        if(n<0){
            printf("Error in writing on buffer");
            exit(1);
        }
        bzero(buffer,1024);
        n=read(sockfd,buffer,1024);
        if(n<0){
            printf("error in reading from buffer");
            exit(1);
        }
        printf("Server message:%s",buffer);
        if(!strncmp("bye",buffer,3))
            break;
    }s
    close(sockfd);
    return 0;
}