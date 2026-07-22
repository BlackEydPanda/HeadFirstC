#include <sys/socket.h>
int read_in(int socket, char *buf, int len) {
  char *string = buf;
  int slen = len;
  int c = recv(socket, string, slen, 0);

  while (string[c - 1] != '\n') {
    string += c;
    slen -= c;
    c = recv(socket, string, slen, 0);
  }

  if (c < 0)
    return c;
  else if (c == 0)
    buf[0] = '\0';
  else
    string[c - 1] = '\0';
  return len - slen;
}
