#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int open_listener_socket() {
  int opened_socket = socket(PF_INET, SOCK_STREAM, 0);
  if (opened_socket == -1)
    error("Can't opeen socket");

  return opened_socket;
}

void bind_to_port(int socket, int port) {
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;

  if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
                 sizeof(int)) == -1)
    error("Can't set the reuse option on the socket");

  if (bind(socket, (struct sockaddr *)&name, sizeof(name)) == -1)
    error("Can't bind to socket");
}

int say(int socket, char *s) {
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    fprintf(stderr, "Error talking to the client: %s\n", strerror(errno));
  return result;
}

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

int listener_d;

// TODO: Properly handle this
void handle_shutdown(int sig) {
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "Bye!\n");
  exit(0);
}

int catch_signal(int sig, void (*handler)(int)) {
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

int accept_connection() {
  if (!listener_d)
    return -1;
  struct sockaddr_storage client_addr;
  unsigned int address_size = sizeof(client_addr);
  int connect_d =
      accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
  if (connect_d == -1)
    puts("Could not accept connection");
  return connect_d;
}

int main() {
  if (catch_signal(SIGINT, handle_shutdown) == -1) {
    error("Can't map the handler");
  }

  listener_d = open_listener_socket();
  int port = 3030;
  bind_to_port(listener_d, 3030);
  if (listen(listener_d, 10) == -1)
    error("Could not initiate listen on port");
  printf("Server listening on port %i\n", port);

  char message[50];
  while (1) {
    int connection = accept_connection();
    if (connection == -1) {
      error("Can't open secondary socket");
    }

    if (!fork()) {
      close(listener_d);
      if (say(connection, "Knock! Knock!\n") != -1) {
        if (read_in(connection, message, 50) < 0) {
          close(connection);
          exit(0);
        }
        if (!strcasecmp(message, "Who's there?")) {
          if (say(connection, "Oscar!\n") == -1) {
            close(connection);
            exit(0);
          }
          if (read_in(connection, message, 50) < 0) {
            close(connection);
            exit(0);
          }
          if (!strcasecmp(message, "Oscar who?")) {
            if (say(connection,
                    "Oscar silly question, you get a silly answer") == -1) {
            }
          } else {
            say(connection, "You should say: Oscar who?");
          }
        } else {
          say(connection, "You should say: 'Who's there?'");
        }
      }
      close(connection);
      exit(0);
    }
    close(connection);
  }

  return 0;
}
