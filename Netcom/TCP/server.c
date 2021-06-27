#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc,char * argv[]) {
    int sockfd,newsockfd,portno,n;
    struct sockaddr_in server_address,client_address;
    char buffer[1024];
    socklen_t len;
    if(argc<2){
        printf("Input format: ./server (port number)");
        exit(1);
    }
    portno=atoi(argv[1]);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        printf("Error in opening socket");
        exit(1);
    }
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=INADDR_ANY;
    server_address.sin_port=htons(portno);
    if(bind(sockfd,(struct sockaddr *) &server_address,sizeof(server_address))<0)
        printf("Error in binding");
    listen(sockfd,5);
    len=sizeof(client_address);
    newsockfd=accept(sockfd,(struct sockaddr *) &client_address,&len);
    if(newsockfd<0){
        printf("Error in accepting");
        exit(1);
    }
    while(1){
    bzero(buffer,1024);
    n=read(newsockfd,buffer,1024);
    if(n<0){
        printf("Error in reading from buffer");
        exit(1);
    }
    printf("Client message:%s",buffer);
    bzero(buffer,1024);
    fgets(buffer,1024,stdin);
    n=write(newsockfd,buffer,1024);
    if(n<0){
        printf("Error in writing to buffer");
        exit(1);
    }
    if(!strncmp("bye",buffer,3))
        break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}