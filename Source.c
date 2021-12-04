#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char letter;
	int prev_enter = -1, prev_space = -1, now = 0;
	int lines_counter = 0, words_counter = 0, letter_counter = 0;
	FILE* data;
	data = fopen(argv[2], "r");
	while ((letter = fgetc(data)) != EOF) {
		letter_counter += 1;
		if (letter == '\n') {
			letter_counter += 1;
			lines_counter += 1;
			prev_enter = now;
		}
		if ((letter == ' ') || (letter == '\n')) {
			if (prev_space != now - 1) {
				words_counter += 1;
			}
			prev_space = now;
		}
		now += 1;
	}
	if ((strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--lines") == 0)) {
		if (prev_enter != now - 1) {
			printf("%d", lines_counter + 1);
		}
		else {
			printf("%d", lines_counter);
		}
	}
	if ((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--bytes") == 0)) {
		printf("%d", letter_counter);
	}
	if ((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "--words") == 0)) {
		if (prev_space != now - 1) {
			printf("%d", words_counter + 1);
		}
		else {
			printf("%d", words_counter);
		}
	}
	return 0;
}

// checking commit