#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void open_url(char *url) {
  pid_t pid = fork();
  if (!pid) {
    if (execlp("cmd", "cmd", "/c", "start", url, NULL) == -1) {
      if (execlp("launch", "launch", url, NULL) == -1) {
        if (execlp("xdg-open", "xdg-open", url, NULL) == -1) {
          fprintf(stderr, "Can't open url in broswer: %s\n", strerror(errno));
        }
      }
    }
  }
}

int main() {
  char *url = "https://www.duckduckgo.com";
  open_url(url);
}
