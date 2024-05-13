#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char* word = "iiw";
	FILE* f;
	fopen_s(&f, "E:\RGRTOI.txt", "r");
	if (f == NULL)
		return -1;
	fprintf(f, "aaa\nabd\nbba\nbbb\nccc\nddd\neee\nfff\nggg\nhha\nhhh\niii\nwww\n");
	printf("%s", Search_word(f, word));
	fclose(f);
}

char* Search_word(FILE* f, char* word)
{
	char* net = "Nety Slova :(";
	int d = 0;
	char buff[100];
	fopen_s(&f, "E:\RGRTOI.txt", "r");
	fseek(f, 0, SEEK_END);
	int k = ftell(f) + 5;
	int end = k;
	int seredina = 0;
	if ((ftell(f) + 5) % 2 == 0)
		seredina = ((ftell(f) + 5) / 2) - 5;
	else
		seredina = ((ftell(f) / 2));
	int help = seredina;
	int l = 0;
	fseek(f, 0, SEEK_SET);
	fgets(buff, 100, f);
	if (Str_pr(buff, word) == 0)
		return buff;

	fseek(f, -5, SEEK_END);
	fgets(buff, 100, f);
	if (Str_pr(buff, word) == 0)
		return buff;

	fseek(f, seredina, SEEK_SET);
	fgets(buff, 100, f);

	if ((int)buff[d] >= (int)word[d]) {
		while (k != l || l > k)
		{
			if (l >= end)
				return net;
			if (buff[d] == word[d])
				while (buff[d] == word[d])
					d++;
			if (Str_pr(buff, word) == 0)
				return buff;
			if (l + 5 == k)
				return net;
			if ((int)word[d] > (int)buff[d])
			{
				l = help;
				if ((help+k) % 2 == 0) {
					fseek(f, (help+k)/2, SEEK_SET);
					help = (help + k) / 2;
				}
				else {
 					fseek(f, ((k + help) +5)/2, SEEK_SET);
					help = (help + k+5) / 2;
				}
			}
			if ((int)buff[d] > (int)word[d])
			{
				k = help;
				if ((help % 2 == 0)) 
				{
					fseek(f, (help) / 2, SEEK_SET);
					help = help / 2;
				}
				else {
					;
					fseek(f, (help+5) / 2, SEEK_SET);
					help = (help+5) / 2;

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
				return buff;
			if (l + 5 == k)
				return net;
			if ((int)word[d] > (int)buff[d])
			{
				l = help;
				if ((help+k) % 2 != 0) {
					fseek(f, ((k+help-5)/2) - end, SEEK_END);
					help = (k + help - 5) / 2;
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
				if ((help+l) % 2 != 0) {
					fseek(f, ((l + help - 5) / 2) - end, SEEK_END);
					help = (l + help - 5) / 2;
				}
				else {
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
}

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
