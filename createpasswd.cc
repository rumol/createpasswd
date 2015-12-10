#include <stdlib.h>
#include <unistd.h>

#include <iostream>

extern char *__progname;

void usage(int exit_status) {
  std::cerr << __progname << " [-ehrs] [-n number_password] [-l min_password_length] [-m max_password_length]" << std::endl;
  exit(exit_status);
}

int main(int argc, char *argv[]) {
  int ch;
  int min_passwd_len, max_passwd_len;
  int uniform_end = 4;
  int nb_pass = 1;

  bool display_end, help, random_len;

  display_end = help = random_len = false;
  min_passwd_len = max_passwd_len = 12;

  while ((ch = getopt(argc, argv, "ehn:m:l:rs:")) != -1)
    switch (ch) {
    case 'e':
      display_end = true;
      break;
    case 'h':
      help = true;
      break;
    case 'n':
      nb_pass = atoi(optarg);
      break;
    case 'm':
      max_passwd_len = atoi(optarg);
      break;
    case 'l':
      min_passwd_len = atoi(optarg);
      break;
    case 'r':
      random_len = true;
      break;
    case 's':
      uniform_end = atoi(optarg);
      break;
    default:
      usage(1);
    }

  if (help)
    usage(0);

  if (max_passwd_len < min_passwd_len)
    max_passwd_len = min_passwd_len;

  for (int j = 0; j < nb_pass; ++j) {
    int passwd_len = min_passwd_len + arc4random_uniform(max_passwd_len - min_passwd_len);
    for (int i = 0; i < passwd_len; ++i)
      std::cout << (char) (' ' + arc4random_uniform('~' - ' ' - 5));
    if (random_len) {
      while (arc4random_uniform(uniform_end)) {
        std::cout << (char) (' ' + arc4random_uniform('~' - ' ' - 5));
      }
    }
    if (display_end)
      std::cout << '$';
    std::cout << std::endl;
  }
}

