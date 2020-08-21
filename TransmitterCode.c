#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// 1M
#define BUFFER_LEN 1048576
#define SENSOR_USB "/dev/sensorPort"

#define SERVER_PORT 6060
#define SERVER_ADDRESS "192.168.1.41"

char buffer[BUFFER_LEN];

int main() {

        /* Open the Serial Port */
        int sensor_fd = serialOpen(SENSOR_USB, 115200);


        /* Create the Server Address Struct */
        struct sockaddr_in server_address;
        bzero(&server_address, sizeof(server_address));
        server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
        server_address.sin_port = htons(SERVER_PORT);
        server_address.sin_family = AF_INET;

        /* create the Network Socket */
        int sockfd;
        // Creating socket file descriptor
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
                perror("socket creation failed");
                exit(1);
        }

        int bytes_avail;

        int byte;
        while(1){

                while ( ( bytes_avail = serialDataAvail(sensor_fd) ) > 0  ){


                        /* Read in the Data */
                        read(sensor_fd, buffer, bytes_avail);


                        /* Send the Data */
                        sendto(sockfd, buffer, bytes_avail, 0, (const struct sockaddr *) &server_address, sizeof(server_address));

                }
                /* if ctrl^D, break */
//              if ( (byte = getchar())  ==  EOF ){
//                      break;
//              }

        }

        close(sockfd);
        serialClose(sensor_fd);

        return 0;
}

