#include "csapp.h"
#include "tftp-server.h"

int main(int argc, char** argv)
{
	// Client and server sockets
	struct sockaddr_in server;
	struct sockaddr_in client;

	int portNumber;	// Port number 	
	
	/* Check arguments */
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <port number>\n", argv[0]);
		exit(0);
	}
	else
	{
		portNumber = argv[1];
	}

	
	while(1)
	{
		
	}

	exit(0);
}
