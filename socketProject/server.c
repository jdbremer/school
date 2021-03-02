  #include <stdio.h>
  #include <stdlib.h>
  #include <strings.h>
  #include <string.h>
  #include <sys/types.h> 
  #include <sys/socket.h>
  #include <netinet/in.h>

  void error(char *msg)
  {
      perror(msg);
      exit(1);
  }

   int main(int argc, char *argv[])
   {
        int sockfd, newsockfd, portno, clilen;
        char buffer[256];
        char sendBuff[512];
        struct sockaddr_in serv_addr, cli_addr;
        int n;
        if (argc < 2) {
            fprintf(stderr,"ERROR, no port provided\n");
            exit(1);
        }
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
           error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(argv[1]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(portno);
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) 
                 error("ERROR on binding");
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
             error("ERROR on accept");
        while(1){
		bzero(buffer,256);
		bzero(sendBuff,512);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		printf("From Client: %s\n",buffer);
		sprintf(sendBuff, "From Server: %s\n",buffer); 
		n = write(newsockfd,sendBuff, sizeof(sendBuff));
		if (n < 0) error("ERROR writing to socket");
        }
        return 0; 
   }


