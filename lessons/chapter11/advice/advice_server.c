#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main() {
  char *advice[] = {
      "Take smaller bites\r\n",
      "Go for the tight jeans. No they do NOT make you look fat.\r\n",
      "One word: inappropriate\r\n",
      "Just for today, be honest. Tell your boss what you *really* think\r\n",
      "You might want to rething that haircut\r\n",
  };

  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  if (!listener_d)
    error("Could not create socket descriptor");

  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int reuse = 1;
  if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
                 sizeof(int)) == -1)
    error("Cannot set the reuse option on the socket");

  if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1)
    error("Could not bind listener to a port");

  if (listen(listener_d, 10) == -1)
    error("Could not initiate listen on port");
  puts("Waiting for connection");

  while (1) {
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d =
        accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if (connect_d == -1)
      puts("Could not accept connection");

    char *msg = advice[rand() % 5];

    if (send(connect_d, msg, strlen(msg), 0) == -1)
      puts("Could not send message to client");

    close(connect_d);
  }

  return 0;
}
