/*
version 0.00002
NOTES:
1. Need to check words by dictionary
2. For timed games, running out of time would be a penalty stroke
3. Create two player option - create different function in menu
4. Have option for pro tour rules or amateur tour rules
5. Do yardage: i.e. par 4 443 yards,
	yardage * lettersUsed / lettersOnBoard

New bugs
1. does not calculate score right
2. need to rethink par 3s and 4s
3. printing scorecard inconsistent
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>


char board[25]; //houses characters for the board
char temp[25];	//temporarily houses board characters while checking validity
char word[25]; //stores the characters of the word input from user
int length, count, cumScore = 0, hole, par, shots; //length of word, count, adds score, hole
bool holeOver = false;
//int difficulty, par = 0; //difficulty of the hole, cumulative par
int scorecard[9][2]; //[par][score]

char letters[26] = { 	'Q', 'J', 'X', 'Z', 'K', 'V', 'B', 'P', 'G', 'C',
						'W', 'Y', 'U', 'F', 'H', 'M', 'L', 'D', 'R', 'N',
						'I', 'S', 'O','A', 'T', 'E'
					};

//Get random character
char generateChar (void) {
    
	char randChar;
	
	int random = (87 * (rand() / (RAND_MAX + 1.0)));
	
	random = (2640 - random * random / 3) / 100 - 1;
	
	//65 in ASCII is 'A'
	randChar = letters[random];
	
	return randChar;
}

//Create an array of 25 random characters
void generateBoard (char array[par * par]) {

	int i;
	
	for(i = 0; i < (par * par); i++)
		array[i] = generateChar();
}

//print game board
void displayBoard (char matrix[par * par]) {
	int i, column;
    
    printf("\n");
    	printf("  +---+---+---+---+---+---+\n");
	for (i = 0; i < (par * par); ) {
		printf("  |");
		for ( column = 1; column <= par; ++column ) {
			printf ("%4c", matrix[i]);
			i++;
		}
		printf ("   |\n");
	}
	printf("  +---+---+---+---+---+---+\n");
	
	printf("\n");
	if(!holeOver) {
		printf("Enter next word or 0 to putt ");
		printf("out and end the hole\n\n");
	}
}

//get a word from user
int getWord (void) {
	char c;
    length = 0;
    int i;
    for(i = 0; i < 25; i++)
    	word[i] = 0;
	
	while((c = getchar()) != '\0') {
		if(c == '0') {
			holeOver = true;
			c = getchar();
			break;	
		}
		//changes lowercase to uppercase letter
		if(c >= 97 && c <= 122 && c != '\n')
			c -= 32;
			
		word[length] = c;
			
        length++;
	}
	return (length - 1);
}

bool checkWord(void) {
	static const char filename[] = "/usr/share/dict/words";
   	FILE *file = fopen ( filename, "r" );
   	bool validWord = false;
   	int i = 0;
   	
   	while(word[i] != '\n') {
   		word[i] += 32;
   	}

   	if ( file != NULL )
   	{
      	char line [ 26 ]; //max size length
      	while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      	{  
      		if(strcmp(word, line) == 0 ) {
      			validWord = true;
      			break;
      		}    		
    	}
      	fclose ( file );
   	}
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }
   i = 0;
      	while(word[i] != '\n') {
   		word[i] -= 32;
   }
   return validWord;
}

//verify that all of the letters are available to use
bool checkLetters(void) {
	bool validLetter, validWord = true;
	int i, j;
	
	for(i = 0; i < length; i++) {
		if(holeOver)
			break;
		validLetter = false;
		for(j = 0; j < (par * par); j++) {
			if(word[i] == temp[j]) {
				temp[j] = '_';
				validLetter = true;
				break;
			}
		}
		if(validLetter != true){
			validWord = false;
			printf("Invalid word. Characters unavailable.\n");
			displayBoard(board);
			break;
		}
	}
	if(validWord) {
		if(checkWord()){
			count += length;
			shots++;
		}
	}
		
	return validWord;
}

//play a word on the game board
void playWord (void) {
    int i, length;
	bool validWord = false;
	
	while(!validWord) {
		if(holeOver)
			break;
        validWord = true;
		length = getWord();
        
		//Make temp[] equal to board[]
		for(i = 0; i < (par * par); i++)
			temp[i] = board[i];
			
		validWord = checkLetters();  

		if(validWord) {
			for(i = 0; i < (par * par); i++)
				board[i] = temp[i];
		}
	}
}

/*
void setPar(void) {
	if (difficulty <= 30) {
		printf("Hole number %i is a par 3.\n\n", hole);
		scorecard[hole - 1][0] = 3;
		par += 3;
	} else if (difficulty >= 38) {
		printf("Hole number %i is a par 5.\n\n", hole);
		scorecard[hole - 1][0] = 5;
		par += 5;
	} else {
		printf("Hole number %i is a par 4.\n\n", hole);
		scorecard[hole - 1][0] = 4;
		par += 4;
	}
} */

//print scorecard
void displayScorecard(void) {
	int i;
	
	printf("SCORECARD\n");
	printf("       1  2  3  4  5  6  7  8  9  TOTAL\n");
	printf("------+--+--+--+--+--+--+--+--+--+----+\n");
	//printf("Par   ");
	//for(i = 0; i < 9; i++)
	//	printf("%3i", scorecard[i][0]);
	//	printf("%4i\n", par);
	printf("Score ");
	for(i = 0; i < 9; i++)
		printf("%3i", scorecard[i][1]);
		printf("%4i\n", cumScore);
	printf("------+--+--+--+--+--+--+--+--+--+----+\n");
}

//start a new hole
void playHole (void) {
	holeOver = false;
	count = 0, shots = 0;
	
	printf("What par is the next hole? ");
	scanf("%i", &par);
	
	generateBoard(board);
	//setPar();
	displayScorecard();
	displayBoard(board);
	
	//play game board until hole is over
	while(!holeOver) {
		playWord();
		displayBoard(board);
		if(count == 25)
			holeOver = true;
	}
	scorecard[hole - 1][1] = ((par * par - count) + shots);
	cumScore += scorecard[hole - 1][1];
}

int main (void) {
    
    char generateChar (void);
    void generateBoard (char array[par * par]);
    void displayBoard (char matrix[par * par]);
    void playHole (void);
    void playWord (void);
    bool checkWord(void);
    //void setPar(void);
    
    bool checkLetters(void);
    int getWord (void);
    
    int i, j;
    
	srand(time(NULL));
	
	for(i = 0; i < 25; i++)
        word[i] = '0';
    
    //initialize scorecard
    for(i = 0; i < 9; i++) {
    	scorecard[i][0] = 0;
    	scorecard[i][1] = 0;
    }
	
	printf("\n\n");
	
    for(hole = 1; hole <= 9; hole++) {
		playHole();
		printf("\n\n");
    }
    
    displayScorecard();
    printf("\nThat's it! See you next round!\n\n");
    
    return 0;
}