#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum type {
	ID,
	IF,
	NUM
};
struct prime {
	enum type t;
	char *cont;
	int row, col;
};

void lexeme(char c);
void print(char *s);

char *tmp;
int row = 1, col = 1;

int main() {
	char next;
	tmp = (char *)malloc(100 * sizeof(char));
	while (scanf("%c", &next)) {
		lexeme(next);
	}
}
void lexeme(char c) {
	static int pos = 0;
	if (c == ' ' || c == 0x0D || c == 0x0A) {
		tmp[pos] = '\0';
		print(tmp);
		tmp[0] = '\0';
		pos = 0;
		if (c == 0x0A) {
			row++;
			col = 1;
		}
		else col++;
	}
	else {
		tmp[pos++] = c;
		col++;
	}
}
void print(char *s) {
	if (strcmp(s, "if")==0) {
		printf("IF (%d, %d)\n", row, col - 2);
	}
	else if (s[0] >= '0'&&s[0] <= '9') {
		printf("NUM(%d) (%d, %d)\n", (int)atof(s), row, col - strlen(s));
	}
	else if(s[0]) {
		printf("ID(%s), (%d, %d)\n", s, row, col - strlen(s));
	}
}