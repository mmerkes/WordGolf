#include <stdio.h>
#include <string.h>

int main ( void )
{
    static const char filename[] = "/usr/share/dict/words";
    FILE *file = fopen ( filename, "r" );
    char word[25];
    int i = 0;
    char c;
    
    for(i = 0; i < 25; i++)
        word[i] = 0;
    i = 0;
    
    printf("Enter a word: ");
    do {
        c = getchar();
        word[i] = c;
        i++;
    }
    while ( c != '\n');
    
    if ( file != NULL )
    {
        char line [ 26 ]; //maximum line length
        while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
        {
      		if(strcmp(word, line) == 0 ) {
      			printf("The program found %s\n", line);
      			break;
      		}
        }
        fclose ( file );
    }
    else
    {
        perror ( filename ); //why file didn't open
    }
    return 0;
}


//http://www.daniweb.com/software-development/c/code/216411/reading-a-file-line-by-line










