#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_BUF 1024

int main(int argc, char **argv) {
	DIR *dr;
	struct dirent *en;
	dr = opendir(".");
	FILE *fp;
    char buffer[MAX_BUF], input[30] = {'\0', };
	int c, count = 0;

	printf("What string are you looking for? (Up to 30 characters) : ");
	fgets(input, 30, stdin);

    
	if (dr == NULL)
		fprintf(stderr, "File not existed in the folder.\n");

	while ((en = readdir(dr))) {
		if (!strcmp(en->d_name, "."))
			continue;
		if (!strcmp(en->d_name, ".."))
			continue;
		if (!strcmp(en->d_name, *argv))
			continue;
		if (!strcmp(en->d_name, "finder.c"))
			continue;

		fp = fopen(en->d_name, "r");
        

		if (fp == NULL) {
			fclose(fp);
			continue;
        } else
            printf("File opened %s\n", en->d_name);
            
		do {
			c = fgetc(fp);
            printf("%c ", c);
			if (feof(fp))
				break;

			while (c == input[count]) {
				if (input[count] == '\n') {
					printf("File <%s> might contain string %s", en->d_name, input);
					break;
				}
				count++;
			}

		} while (1);

		count = 0;

		fclose(fp);
	}

	closedir(dr);

	return 0;
}
