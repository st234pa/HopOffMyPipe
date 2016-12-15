#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int server_handshake(int *fc) {
  mkfifo("WKP", 0644);
}

int client_handshake(int *ts) {
  mkfifo("private", 0644);
}
