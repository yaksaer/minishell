#include "cd.h"

int main(int argc, char **argv)
{
	errno = 0;
	{
//		if (args[1] == NULL) {
//			fprintf(stderr, "lsh: expected argument to \"cd\"\n");
//		} else {
		if (chdir(argv[1]) != 0)
			perror(NULL);
	}
	return 0;
}

