#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(char argc,char *argv[]){
    int sock;
    struct sockaddr_in server,client;
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        error("Socket error");
    }

    bzero((char*)&server,sizeof(server));
    int port_no = aoti(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_no);

    if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0){
        error("Bind error");
    }

    listen(sock,5);

    int clilen = sizeof(client);
    int newsock = accept(sock,(struct sockaddr*)&client,&clilen);
    if(newsock < 0){
        error("Error on accept");
    }

    char buffer[256];
    bzero(buffer,265);

    int n = read(newsock,buffer,255);
    if(n < 0){
        error("error reading from socket");
    }

    FILE *f;
    char c[2000];
    char ch;
    int i = 0;
    if(f = freopen(buffer,"r",stdin) != NULL){
        while (ch = getc(stdin)!=EOF)
        {
            c[i++] = ch;
        }
        c[i] = '\0';
        n = write(newsock,c,1999);
        
    }
    


    




    return 0;
}



