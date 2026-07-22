#include <sys/socket.h>

int read_in(int socket, char *buf, int len) {
  if (len < 2)
    return 0;

  int input_left = len;
  int received_chars = 0;

  do {
    received_chars = recv(socket, buf + (len - input_left), input_left, 0);

    if (received_chars < 0) {
      return received_chars;
    }
    input_left -= received_chars;
  } while (received_chars != 0 && buf[len - input_left - 1] != '\n');

  // TODO: Test
  buf[len - input_left > 2 ? len - input_left - 2 : 0] = '\0';
  return len - input_left;
}
