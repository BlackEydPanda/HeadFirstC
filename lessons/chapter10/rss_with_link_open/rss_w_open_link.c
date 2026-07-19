
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

void open_url(char *url) {
  pid_t pid = fork();
  if (!pid) {
    printf("%s\n", url);
    if (execlp("cmd", "cmd", "/c", "start", url, NULL) == -1) {
      if (execlp("launch", "launch", url, NULL) == -1) {
        if (execlp("xdg-open", "xdg-open", url, NULL) == -1) {
          fprintf(stderr, "Can't open url in broswer: %s\n", strerror(errno));
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char *phrase = argv[1];
  char *vars[] = {"RSS_FEED=https://www.theguardian.com/world/rss", NULL};

  int fd[2];
  if (pipe(fd) == -1) {
    error("Can't create the pipe");
  }

  pid_t pid = fork();
  if (pid == -1) {
    error("Can't fork process");
  }

  if (!pid) {
    if (dup2(fd[1], 1) == -1) {
      error("Can't pipe Standard Output");
    }
    close(fd[0]);

    if (execle("/usr/bin/python3", "/usr/bin/python3", "./rssgossip.py", "-u",
               phrase, NULL, vars) == -1) {
      error("Can't run script");
    }
  }

  dup2(fd[0], 0);
  close(fd[1]);

  char line[255];
  while (fgets(line, 255, stdin)) {
    if (line[0] == '\t') {
      open_url(line + 1);
    }
  }

  return 0;
}
