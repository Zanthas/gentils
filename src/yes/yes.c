#include <stdio.h>


#define VERSION "Gentils Yes v0.0.1/n"

int main(int argc, char *argv[]){
	char *str;
	if(argc == 1)
		str = "y";
	else
		str = argv[1];
	
	while(1){
		printf("%s\n", str);
	}
	return 0;
}
