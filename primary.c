#include <stdio.h> 
#include <string.h>    
#include <sys/socket.h>    
#include <stdlib.h>
#include "ccitt16.h"
#include "utilities.h"
#include "introduceerror.h"

void primary(int sockfd, double ber) {
	//Initialize packet and msg values
	int read_size;
    char msg[DATA_LENGTH], srv_reply[150], packet[PACKET_SIZE];
	int packetNum = 0;
	struct packet_buffer buffer[50];
	int sendWindow[WINDOW_SIZE = {0, 1, 2}];
	srv_reply[0] = 0;

    while(1)
    {
        printf("Enter message : ");

		//Take message in
		fgets(msg, DATA_LENGTH+1, stdin);

		//Build our packet to send out and update our packetNum
		buildPacket(packet, DATA_PACKET, msg, packetNum);

		struct packet_buffer buff = {packet};
		buffer[packetNum] = buff;

		printPacket(packet);

		//Allow possible errors
		IntroduceError(packet, ber);
        
        if(srv_reply[0] == 0){
			//If I get a value less than 0, something has failed
			if (send(sockfd, packet, PACKET_SIZE, 0) < 0)
			perror("Sending has failed!")
		}
		else if (srv_reply[0] == '2'){
			shiftWindow(sendWindow, WINDOW_SIZE, 1);
			if (send(sockfd, packet, PACKET_SIZE, 0) < 0
			perror("Sending has failed! (2)"))
		}
		else if (srv_reply[0] == '3'){
			int i;
			for(i = 0; i < 3, i++){
				if(send(sockfd, buffer + sendWindow[i], PACKET_SIZE, 0) < 0){
					perror("Sending has failed! (3)")
				}
			}
		}
        // Receive a reply from the server
		// NOTE: If you have more data than 149 bytes, it will 
		// 			be received in the next call to "recv"
		// read_size - the length of the received message 
		// 				or an error code in case of failure
		// msg - a buffer where the received message will be stored
		// 149 - the size of the receiving buffer (any more data will be 
		// 		delievered in subsequent "recv" operations
		// 0 - Options and are not necessary here

		if(packetNum >= 2){
			if( (read_size = recv(sockfd, srv_reply, 149, 0)) < 0){
				perror("Something has gone wrong! (Read_Size)")
			}
		}

		// Null termination since we need to print it
		srv_reply[read_size] = '\0';
        printf("Server's reply: %s\n", srv_reply);
    }
  
}

