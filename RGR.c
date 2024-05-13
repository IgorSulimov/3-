#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Str_pr(char* str1, char* str2)
{
	int i = 0;
	while (i != 3)
	{
		if (str1[i] == str2[i])
			i++;
		else
			return 1;
	}
	return 0;
}
char* Search_word1(FILE* f, char* word)
{
	char* net = "Nety Slova :(";
	char buff[100];
	int d = 0;
	f = fopen("RGRTOI.txt","r");
	fseek(f, 0, SEEK_END);
	int k = ftell(f) - 5;
	int end = ftell(f);
	int seredina = 0;
	if (((ftell(f)-3) /2) %4 == 0)
		seredina = ((ftell(f) -3) / 2);
	else
		seredina = ((((ftell(f)-3 -6) / 2)));
	int help = seredina;
	int l = 0;
	fseek(f, 0, SEEK_SET);
	fgets(buff, 100, f);
	if (Str_pr(buff, word) == 0)
		return word;

	fseek(f, -5, SEEK_END);
	fgets(buff, 100, f);
	if (Str_pr(buff, word) == 0)
		return word;

	fseek(f, seredina, SEEK_SET);
	fgets(buff, 100, f);

	if ((int)buff[d] >= (int)word[d])
	{
		while (k != l || l > k)
		{
			if (l >= end)
				return net;
			if (buff[d] == word[d])
				while (buff[d] == word[d])
					d++;
			if (Str_pr(buff, word) == 0)
				return word;
			if (l + 4 == k)
				return net;
			if ((int)word[d] > (int)buff[d])
			{
				l = help;
				if (((help+k) / 2) % 4 == 0) {
					fseek(f, (help+k)/2, SEEK_SET);
					help = (help + k) / 2;
					}
				else {
 					fseek(f, ((k + help) +4)/2, SEEK_SET);
					help = (help + k+4) / 2;
					}
			}
			if ((int)buff[d] > (int)word[d])
			{
				k = help;
				if ((help / 2) % 4 == 0) 
				{
					fseek(f, (help) / 2, SEEK_SET);
					help = help / 2;
				}
				else 
				{
				fseek(f, (help+4) / 2, SEEK_SET);
				help = (help+4) / 2;
				}
			}
			fgets(buff, 100, f);
			d = 0;
		}
	}


	if ((int)buff[d] < (int)word[d])
	{
		while (k != l || l > k)
		{
			if (buff[d] == word[d])
				while (buff[d] == word[d])
					d++;
			if (l >= end)
				return net;
			if (Str_pr(buff, word) == 0)
				return word;
			if (l + 4 == k)
				return net;
			if ((int)word[d] > (int)buff[d])
			{
				l = help;
				if (((help+k) / 2) % 4 != 0) 
				{
					fseek(f, ((k+help+4)/2) - end, SEEK_END);
					help = (k + help +4)/2;
				}
				else
				{
					fseek(f, ((k + help) / 2) - end, SEEK_END);
					help = (k + help) / 2;
				}
			}
			if ((int)buff[d] > (int)word[d])
			{
				k = help;
				if (((help+l) / 2) % 4 != 0) 
				{
					fseek(f, ((l + help - 4) / 2) - end, SEEK_END);
					help = (l + help - 4) / 2;
				}
				else 
				{
					fseek(f, ((l + help) / 2) - end, SEEK_END);
					help = ((l + help) / 2);

				}
			}
			fgets(buff, 100, f);
			d = 0;
		}
	}
	return net;
	fclose(f);
	return 0;
}


int main(int argc,char* argv[])
{
        argc = 2;
	char* word = argv[argc];
	FILE* f;
	argc = 1;
	f = fopen(argv[argc],"r");
	if (f == NULL)
		return -1;
	fprintf(f, "aaa\nabd\nbba\nbbb\nccc\nddd\neee\nfff\nggg\nhha\nhhh\niii\nwww\n\n");
	printf("%s", Search_word1(f, word));
	fclose(f);
}

