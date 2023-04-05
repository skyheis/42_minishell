#include <stdio.h>

int	main()
{
	char str[1];
	int i = 0;

	str[0] = ' ';
	while (str[i] && str[i] != 32 && str[i] != '|' && str[i] != '<' && str[i] != '>')
		printf("si");
}
