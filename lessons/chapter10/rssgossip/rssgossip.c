#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *feeds[] = {"https://www.theguardian.com/world/rss",
                   "https://feeds.bbci.co.uk/news/rss.xml",
                   "https://feeds.npr.org/1001/rss.xml"};

  int times = 3;
  char *phrase = argv[1];
  int i;

  for (i = 0; i < times; i++) {
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL};
    pid_t pid = fork();
    if (pid == -1) {
      fprintf(stderr, "Can't form process: %s\n", strerror(errno));
      return 1;
    }

    if (!pid) {
      if (execle("/usr/bin/python3", "/usr/bin/python3", "./rssgossip.py",
                 phrase, NULL, vars) == -1) {
        fprintf(stderr, "Can't run script: %s\n", strerror(errno));
        return 1;
      }
    }
  }
  // TODO: this does not do a clean exit. Doublecheck why
  return 0;
}
