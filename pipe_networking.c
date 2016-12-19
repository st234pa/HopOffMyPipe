#include "pipe_networking.h"

int server_handshake(int *c) {

  // 1. Server creates a WKP
  mkfifo("WKP", 0644);
  printf("WKP created\n");
  
  // 2. Server waits for a connection
  int fd = open("WKP", O_RDONLY);
  printf("Server connected to WKP\n");
  
  // 6. Server receives client's message and removes WKP
  char msg[MESSAGE_BUFFER_SIZE+1];
  read(fd, msg, MESSAGE_BUFFER_SIZE);
  msg[MESSAGE_BUFFER_SIZE] = 0;
  printf("Private FIFO name: %s\n", msg);
  remove("WKP");
  printf("WKP removed\n");  
  
  // 7. Server connects to client FIFO, sends initial acknowledgement message
  int fd2 = open(msg, O_WRONLY);
  printf("Server connected to private FIFO, sending acknowledgment...\n");
  write(fd2, "confirmed", strlen("confirmed")+1);

  //11. Receive client's message
  read(fd, msg, MESSAGE_BUFFER_SIZE);
  msg[MESSAGE_BUFFER_SIZE] = 0;
  printf("Client confirmation message: %s\n", msg);

  //12. Return fds of pipes
  *c = fd;
  return fd2;
}

int client_handshake(int *s) { 

  // 3. Client creates a private FIFO
  mkfifo("private", 0644);
  printf("Private FIFO created\n");
  
  // 4. Client connects to WKP and sends the private FIFO name
  int fd = open("WKP", O_WRONLY);
  printf("Client connected to WKP\n");
  
  write(fd, "private", strlen("private")+1);
  printf("Sent private FIFO name to server\n");
  
  int fd2 = open("private", O_RDONLY);
  printf("Client connected to private");

  // 5. Client waits for message from server
  char msg[MESSAGE_BUFFER_SIZE+1];
  read(fd2, msg, MESSAGE_BUFFER_SIZE);
  msg[MESSAGE_BUFFER_SIZE] = 0;
  printf("Acknowledgement message from server: %s\n", msg);
  
  // 8. Client received server's message, removes its private FIFO
  remove("private");
  printf("private FIFO removed\n");
  
  // 9. Client sends message back to server
  write(fd, "gotchu", strlen("gotchu")+1);

  //10. Return fds of pipes
  *s = fd;
  return fd2;
}

