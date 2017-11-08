#include <stdio.h>
#include <string.h>

char brackets(int *num, const char *const str) {
	while(1)
		switch(str[*num]) {

		case '\0':
			return '\1';

		case '[':
			(*num) += 1;
			if(brackets(num, str) != ']') return '\0';
			break;

		case '(':
			(*num) += 1;
			if(brackets(num, str) != ')') return '\0';
			break;

		case ')':
			(*num) += 1;
			return ')';

		case ']':
			(*num) += 1;
			return ']';

		default:
			(*num) += 1;

		}//switch
}

//wrapper function for valid brackets.
int validBrackets(const char *const string) {
	int index = 0; char c = brackets(&index, string);
	return c && c != ')' && c != ']';
}


int main() {
	char str[1000];
	scanf("%s", str);
	if(validBrackets(str)) {
		printf("Correct!!!");
	} else {
		printf("Incorrect");
	}
}
