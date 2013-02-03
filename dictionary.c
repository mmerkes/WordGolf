#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//need to use strcmp in string.h

int main (void) {
	FILE *dictionary;
	char buf[25];
	char word[25];
	bool validWord;
	
	dictionary = fopen("words.txt", "r");	
	if (!dictionary)
		return 1;
		
	char c;
    int length = 0;
	int i;
	
	for(i = 0; i < 25; i++)
		word[i] = 0;
	
	while((c = getchar()) != '\n') {
		word[length] = c;
        length++;
	}
	
	while (fgets(buf, 25, dictionary) != word)
		printf("%s", buf);
		
		printf("%s", buf);
		
	fclose (dictionary);
	
	return 0;
}