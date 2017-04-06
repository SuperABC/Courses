#include <iostream>
#define MAX_LENGTH 1000

using namespace std;

enum dataType {
	EQUATION,
	PRODUCTION,
	NUMBER
};
enum operatorType {
	PLUS,
	MINUS,
	MULTY,
	DIVIDE,
	LBRACE,
	RBRACE,
	END,
	OTHER
};

int parseEquation(char **str, int lastPend);
int parseProduction(char **str, int lastPend);
void syntaxError();

operatorType lookFoward(char *str);
char *passNum(char *str);
char *passOperator(char *str, char op);
bool fisrtNum(char *str);

int term = 0;

int main() {
	char *equ = new char[MAX_LENGTH];
	while (1) {
		term = 0;
		cin.getline(equ, MAX_LENGTH);
		int res = parseEquation(&equ, 0);
		if(!term)cout << "The result is:  " << res << endl;
	}
}

int parseEquation(char **str, int lastPend) {
	int res = 0;
	int first = 1;
	if (lookFoward(*str) == END || lookFoward(*str) == RBRACE) {
		if (term)return 1;
		if (!fisrtNum(*str))syntaxError();
		res = atoi(*str);
		*str = passNum(*str);
		return res;
	}
	while (lookFoward(*str) != END&&lookFoward(*str) != RBRACE) {
		if (term)return 1;
		switch (lookFoward(*str)) {
		case PLUS:
			if (first) {
				first = 0;
				if (!fisrtNum(*str))syntaxError();
				if (lookFoward(*str) != LBRACE) {
					res = atoi(*str);
					*str = passNum(*str);
					if (lastPend)return res;
				}
			}
			*str = passOperator(*str, '+');
			res += parseEquation(str, 1);
			break;
		case MINUS:
			if (first) {
				first = 0;
				if (!fisrtNum(*str))syntaxError();
				if (lookFoward(*str) != LBRACE) {
					res = atoi(*str);
					*str = passNum(*str);
					if (lastPend)return res;
				}
			}
			*str = passOperator(*str, '-');
			res -= parseEquation(str, 1);
			break;
		case LBRACE:
		case MULTY:
		case DIVIDE:
			first = 0;
			res = parseProduction(str, 0);
			break;
		}
	}
	return res;
}
int parseProduction(char **str, int lastPend) {
	int res = 0;
	int first = 1;
	if (lookFoward(*str) == END || lookFoward(*str) == RBRACE) {
		if (term)return 1;
		if (!fisrtNum(*str))syntaxError();
		res = atoi(*str);
		*str = passNum(*str);
		return res;
	}
	while (lookFoward(*str) != END&&lookFoward(*str) != RBRACE) {
		if (term)return 1;
		if (first) {
			first = 0;
			if (!fisrtNum(*str))syntaxError();
			if (lookFoward(*str) != LBRACE) {
				res = atoi(*str);
				*str = passNum(*str);
				if (lastPend)return res;
			}
		}
		switch (lookFoward(*str)) {
		case MULTY:
			*str = passOperator(*str, '*');
			res *= parseProduction(str, 1);
			break;
		case DIVIDE:
			*str = passOperator(*str, '/');
			res /= parseProduction(str, 1);
			break;
		case LBRACE:
			*str = passOperator(*str, '(');
			res = parseEquation(str, 0);
			*str = passOperator(*str, ')');
			break;
		case PLUS:
		case MINUS:
			return res;
		}
	}
	return res;
}
void syntaxError() {
	if (term == 1)return;
	term = 1;
	cout << "Syntax Error! Please verify." << endl;
}

operatorType lookFoward(char *str) {
	while (*str == ' ' || *str == '.' || (*str > '0' && *str < '9'))str++;
	switch (*str) {
	case '+':return PLUS;
	case '-':return MINUS;
	case '*':return MULTY;
	case '/':return DIVIDE;
	case '\0':return END;
	case '(':return LBRACE;
	case ')':return RBRACE;
	}
	syntaxError();
	return OTHER;
}
char *passNum(char *str) {
	while (*str == ' ')str++;
	while (*str >= '0'&&*str <= '9')str++;
	while (*str == ' ')str++;
	return str;
}
char *passOperator(char *str, char op) {
	while (*str == ' ')str++;
	if (*str == op)str++;
	else syntaxError();
	return str;
}
bool fisrtNum(char *str) {
	while (*str == ' ')str++;
	if (*str >= '0'&&*str <= '9')return 1;
	else return 0;
}