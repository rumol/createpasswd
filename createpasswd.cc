#include <stdlib.h>
#include <unistd.h>

#include <iostream>

extern char *__progname;

void usage(int exit_status) {
  std::cerr << __progname << " [-ehr] [-n number_of_password] [-l min_password_length] [-p distribution_parameter] [-m max_password_length]" << std::endl;
  exit(exit_status);
}

char random_char() {
  return (char) (' ' + arc4random_uniform('~' - ' ' - 5));
}

int main(int argc, char *argv[]) {
  int ch;
  int min_passwd_len, max_passwd_len;
  int distribution_param = 4;
  int nb_pass = 1;

  bool display_end, help, random_len;

  display_end = help = random_len = false;
  min_passwd_len = max_passwd_len = 12;

  while ((ch = getopt(argc, argv, "ehn:m:l:p:r")) != -1)
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
    case 'p':
      distribution_param = atoi(optarg);
      break;
    case 'r':
      random_len = true;
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
      std::cout << random_char();
    if (random_len)
      while (arc4random_uniform(distribution_param))
        std::cout << random_char();

    if (display_end)
      std::cout << '$';
    std::cout << std::endl;
  }
}
