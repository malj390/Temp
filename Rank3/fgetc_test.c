#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;
	
	printf("Type some characters (Ctrl+D to end):\n");
	
	// Read characters one by one from stdin
	while ((c = fgetc(stdin)) != EOF)
	{
		printf("\nRead character: '%c' (ASCII: %d)\n", c, c);
		
		// Show if it's whitespace
		if (isspace(c))
			printf("  -> This is whitespace!\n");
	}
	
	printf("\nReached EOF\n");
	return (0);
}
