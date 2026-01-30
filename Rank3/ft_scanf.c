#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			return (1);
		}
	}
	return (0);
}

int match_char(FILE *f, char c)
{
	int c_read;
	c_read = fgetc(f);
	if (c_read == c)
		return (1);
	else if (c_read != c && c_read != EOF)
		ungetc(c_read, f);
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	char	*ptr;
	int		c;

	ptr = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (0);
	*ptr = (char)c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	*ptr;
	int	c;
	long	result = 0;
	int	sign = 1;
	int	digits_read = 0;
	ptr = va_arg(ap, int *);

	c = fgetc(f);
	while (isspace(c))
		c = fgetc(f);
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (isdigit(c))
	{
		digits_read++;
		result = result * 10 + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	if (digits_read == 0)
		return (0);
	*ptr = (int)(result * sign);
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*ptr = va_arg(ap, char *);
	int		c = fgetc(f);
	int		len = 0;

	while (isspace(c))
		c = fgetc(f);
	if (c == EOF)
		return (0);
	while (c != EOF && !isspace(c))
	{
		ptr[len++] = (char)c;
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	ptr[len] = '\0';
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void)
{
	char c;
	int d;
	char s[100];
	int ret;

	printf("Testing scanf with format: \"%%c %%d %%s\"\n");
	printf("Enter a character, an integer, and a string:\n");
	
	ret = ft_scanf("%c %d %s", &c, &d, s);
	
	printf("\nReturn value: %d\n", ret);
	printf("Character: '%c'\n", c);
	printf("Integer: %d\n", d);
	printf("String: %s\n", s);

	return (0);
}
