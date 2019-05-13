#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf("Wrong number of arguments\n");
        return 0;
    }

    int testnumber = atoi(argv[1]);

    // sd - socket descriptor
    int sd,buff,server_addres_length;
    struct sockaddr_in server_address,client_address;

    sd=socket(AF_INET,SOCK_DGRAM,0);

    bzero((char *) &client_address, sizeof(client_address));

    client_address.sin_family=AF_INET;
    client_address.sin_addr.s_addr=htonl(INADDR_ANY);
    client_address.sin_port=htons((short)0);

    bzero((char *) &server_address, sizeof(server_address));

    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=htonl(2568159690); //specific server
    server_address.sin_port=htons((short)5000);
    
    bind(sd,(struct sockaddr *) &client_address,sizeof(client_address));

    server_addres_length = sizeof(server_address);

    buff = htonl(testnumber);
    sendto(sd,(char *) &buff,sizeof(int),0,(struct sockaddr *) &server_address,server_addres_length);

    recvfrom(sd,(char *) &buff,sizeof(int),0,(struct sockaddr *) &server_address,&server_addres_length);
    int answer=ntohl(buff);

    printf("Answer: %d\n",answer);
}