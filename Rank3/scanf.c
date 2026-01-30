#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char c;
	int d;
	char s[100];
	int ret;

	printf("Testing scanf with format: \"%%c %%d %%s\"\n");
	printf("Enter a character, an integer, and a string:\n");
	
	ret = scanf("%c %d %s", &c, &d, s);
	
	printf("\nReturn value: %d\n", ret);
	printf("Character: '%c'\n", c);
	printf("Integer: %d\n", d);
	printf("String: %s\n", s);

	return (0);
}
