
#include "sim_app.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>  
#include <netdb.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "definitions.h"


#define UART2_PORT 52002
#define UART3_PORT 52003

#define MAX_SOCKET_CONNECTIONS 10

#define SA struct sockaddr 
#define BACKLOG 1   
#define NUM_SOCKS 2

// Callback function forward declearation
extern void reset_counters();

SIM_SOCKET_DATA sim_socks[MAX_SOCKET_CONNECTIONS];

SIM_SOCKET_DATA U2;
SIM_SOCKET_DATA U3;

SIM_SOCKET_DATA *uart_socks[NUM_SOCKS];

uint8_t sim_counter = 0;

int REGISTER_SOCK(char* SERVERNAME, int PORT)
{

    int status;
    int s, conn_s;
    struct addrinfo hints;
    struct addrinfo *servinfo; 
    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", PORT);
    struct sockaddr_storage client_addr;
    socklen_t addr_size;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    if ((status = getaddrinfo(NULL, port_str, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    int yes=1;
    if (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    } 

    if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1) {
        perror("setsockopt (TCP_NODELAY)");
        exit(1);
    }

    bind(s, servinfo->ai_addr, servinfo->ai_addrlen);
    listen(s, BACKLOG);

    // now accept an incoming connection:
    addr_size = sizeof(client_addr);
    (void)fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);

    return s;
}


void close_socket(SIM_SOCKET_DATA* U){
  U->connected = false;
  close(U->connected);
  U->csock = 0;
}


void SIM_APP_Initialize ( void )
{
    char* SERVERNAME = "";
    U2.sock = REGISTER_SOCK(SERVERNAME, UART2_PORT);
    U3.sock = REGISTER_SOCK(SERVERNAME, UART3_PORT);
    uart_socks[0] = &U2;
    uart_socks[1] = &U3;
}


void SIM_APP_Tasks ( void )
{
  char buf;

  if(sim_counter > 20){
    for(int i=0;i<NUM_SOCKS;i++){
      if(!uart_socks[i]->connected){
        ATTEMPT_CONNECTION(uart_socks[i]);
      } else {
        int retval = recv(uart_socks[i]->csock, &buf, 1, MSG_PEEK);
        if (retval == 0){
          printf("CLOSING SOCKET MAIN %d \r\n", i);
          close_socket(uart_socks[i]);
          reset_counters();
        }
      }
    } 
    sim_counter = 0;
  }

  sim_counter++;
  vTaskDelay(10);
}

void ATTEMPT_CONNECTION(SIM_SOCKET_DATA* U){
  struct sockaddr_storage addr;
  socklen_t addr_len = sizeof(addr);
  int result = accept(U->sock, (struct sockaddr *)&addr, &addr_len);

  if (result == -1) {
      return;
  } else {
    U->csock = result;
    U->connected = true;
  }
}


int UART_SIM_Send(SIM_SOCKET_DATA* U, uint8_t* pWrBuffer, const size_t size){
  if(U->connected){
    return send(U->csock, pWrBuffer, size,0);
  } else {
    return 0; // Returns 0 when not connected
  }
}

int UART_SIM_Recv(SIM_SOCKET_DATA* U, uint8_t* pRdBuffer, const size_t size){
  if(U->connected){
    int response = recv(U->csock, pRdBuffer, size,0);
    if(response == 0){
      printf("SOCKET %d CLOSED\r\n", response);
      close_socket(U);
      return size;
    } else if (response < 0){
      return 0;
    }
    return response;
  } else {
    return 0; // Returns 0 when not connected
  }
}

int UART_SIM_RecvPeek(SIM_SOCKET_DATA* U, uint8_t* pRdBuffer, const size_t size){
  if(U->connected){
    int response = recv(U->csock, pRdBuffer, size, MSG_PEEK);
    if(response == 0){
      printf("SOCKET %d CLOSED\r\n", response);
      close_socket(U);
      return size;
    } else if (response < 0){
      return 0;
    }
    return response;
  } else {
    return size;
  }
}

size_t UART2_Write(uint8_t* pWrBuffer, const size_t size) {
    return UART_SIM_Send(&U2,pWrBuffer, size);
}

size_t UART2_Read(uint8_t* pRdBuffer, const size_t size) {
    return UART_SIM_Recv(&U2,pRdBuffer, size);
}

size_t UART3_Write(uint8_t* pWrBuffer, const size_t size) {
    return UART_SIM_Send(&U3,pWrBuffer, size);
}

size_t UART3_Read(uint8_t* pRdBuffer, const size_t size) {
    return UART_SIM_Recv(&U3,pRdBuffer, size);
}


/*******************************************************************************
 End of File
 */
