
#include "stdlib.h"
#include "stdio.h"
#include "getopt.h"
#include "regex.h"


void number_lines(FILE* file, const char* format, const regex_t* regex, size_t* offset);

int main (int argc, char** argv)
{
  const char* regex_str = ".*[ -~].*";
  const char* format = "% 5d %s\n";
  regex_t regex;
  int i;

  int argfail = 0;

  int m = 0;
  while ((m = getopt(argc, argv,"b:n:")) != -1) {

    switch(m) {
    case 'b':
      switch(optarg[0]) {
      case 't':
	regex_str = ".*[ -~].*";
	if (optarg[1] != '\0') argfail = 1;
	break;
      case 'a':
	regex_str = ".*";
	if (optarg[1] != '\0') argfail = 1;
	break;
      case 'n':
	regex_str = "(?!.*)";
	if (optarg[1] != '\0') argfail = 1;
	break;
      case 'p':
	if (optarg[1] == '\0') argfail = 1;
	regex_str = optarg+1;
	break;
      default:
	argfail = 1;
      }
      break;
    case 'n':
      if      (optarg[0]=='l' && optarg[1]=='n' && optarg[2] == '\0') format = "%- 5d %s\n";
      else if (optarg[0]=='r' && optarg[1]=='n' && optarg[2] == '\0') format = "% 5d %s\n";
      else if (optarg[0]=='r' && optarg[1]=='z' && optarg[2] == '\0') format = "%05d %s\n";
      else argfail = 1;
      break;
    case '?':
    default:
      argfail = 1;
    }

    if (argfail == 1) {
      fprintf(stderr, "Wait a sec, are you trying to trick me again?\n");
      return 1;
    }
  }
  
  regcomp(&regex, regex_str, REG_EXTENDED);

  argv = argv + optind;
  argc = argc - optind;

  size_t offset = 1;

  if (argc == 0) {
    number_lines(stdin, format, &regex, &offset);
  } else {

    for (i = 0; i < argc; ++i) {

      FILE* file = fopen(argv[i], "r");
      
      if (file == NULL) {
	fprintf(stderr, "Where the fuck is %s?\n", argv[i]);
	return 1;
      }

      number_lines(file, format, &regex, &offset);

      fclose(file);
    }
  }

  regfree(&regex);

  return 0;
}


void number_lines(FILE* file, const char* format, const regex_t* regex, size_t* offset)
{
  char* line = NULL;
  size_t len = 0;

  while(getline(&line, &len, file) > 0) {
    if (regexec(regex, line, 0, NULL, REG_EXTENDED) == 0) {
      printf(format, *offset, line);
      ++(*offset);
    } else {
      printf("      %s", line);
    }
  }

  if (line != NULL) free(line);
}
