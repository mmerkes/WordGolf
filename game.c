/*
version 0.00002
NOTES:
1. Need to check words by dictionary
2. For timed games, running out of time would be a penalty stroke
3. Create two player option - create different function in menu
4. Have option for pro tour rules or amateur tour rules
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


char board[25]; //houses characters for the board
char temp[25];	//temporarily houses board characters while checking validity
char word[25]; //stores the characters of the word input from user
int length, count, cumScore = 0, hole; //length of word, count, adds score, hole
bool holeOver = false;
int difficulty, par = 0; //difficulty of the hole, cumulative par
int scorecard[9][2]; //[par][score]

char letters[100][2] = { //[letter][difficulty value]
						{'Z', 5}, {'J', 5}, {'Q', 4}, {'X', 4}, {'K', 3},
						{'V', 3}, {'B', 2}, {'B', 2}, {'P', 2}, {'P', 2}, 
						{'G', 2}, {'G', 2}, {'W', 2}, {'W', 2}, {'Y', 2},
						{'Y', 2}, {'F', 2}, {'F', 2}, {'M', 2}, {'M', 2},
						{'M', 2}, {'C', 2}, {'C', 2}, {'C', 2}, {'U', 1},
						{'U', 1}, {'U', 1}, {'L', 1}, {'L', 1}, {'L', 1},
						{'L', 1}, {'D', 1}, {'D', 1}, {'D', 1}, {'D', 1},
						{'H', 1}, {'H', 1}, {'H', 1}, {'H', 1}, {'R', 1},
						{'R', 1}, {'R', 1}, {'R', 1}, {'R', 1}, {'R', 1},
						{'S', 1}, {'S', 1}, {'S', 1}, {'S', 1}, {'S', 1}, 
						{'S', 1}, {'N', 1}, {'N', 1}, {'N', 1}, {'N', 1}, 
						{'N', 1}, {'N', 1}, {'N', 1}, {'I', 1}, {'I', 1}, 
						{'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, {'I', 1}, 
						{'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, {'O', 1}, 
						{'O', 1}, {'O', 1}, {'O', 1}, {'A', 1}, {'A', 1}, 
						{'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, {'A', 1}, 
						{'A', 1}, {'T', 1}, {'T', 1}, {'T', 1}, {'T', 1}, 
						{'T', 1}, {'T', 1}, {'T', 1}, {'T', 1}, {'T', 1}, 
						{'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, 
						{'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, {'E', 1}, 
					};

//Get random character
char generateChar (void) {
    
	char randChar;
	
	int random = (int)(100 * (rand() / (RAND_MAX +
                                      1.0)));
	
	//65 in ASCII is 'A'
	randChar = letters[random][0];
	//increases difficulty rating based on letter
	difficulty += letters[random][1];
	
	return randChar;
}

//Create an array of 25 random characters
void generateBoard (char array[25]) {
	difficulty = 0;
	int i;
	
	for(i = 0; i < 25; i++)
		array[i] = generateChar();
}

//print game board
void displayBoard (char matrix[25]) {
	int i, column;
    
    printf("\n");
    	printf("  +---+---+---+---+---+---+\n");
	for (i = 0; i < 25; ) {
		printf("  |");
		for ( column = 1; column <= 5; ++column ) {
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
	
	while((c = getchar()) != '\n') {
		if(c == '0') {
			holeOver = true;
			c = getchar();
			break;	
		}
		//changes lowercase to uppercase letter
		if(c >= 97 && c <= 122)
			c -= 32;
		word[length] = c;
        length++;
	}
	return length;
}

//verify that all of the letters are available to use
bool checkLetters(void) {
	bool validLetter, validWord = true;
	int i, j;
	
	for(i = 0; i < length; i++) {
		if(holeOver)
			break;
		validLetter = false;
		for(j = 0; j < 25; j++) {
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
	if(validWord)
		count +=length;
		
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
		for(i = 0; i < 25; i++)
			temp[i] = board[i];
			
		validWord = checkLetters();  

		if(validWord) {
			for(i = 0; i < 25; i++)
				board[i] = temp[i];
		}
	}
}

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
}

//print scorecard
void displayScorecard(void) {
	int i;
	
	printf("SCORECARD\n");
	printf("       1  2  3  4  5  6  7  8  9  TOTAL\n");
	printf("------+--+--+--+--+--+--+--+--+--+----+\n");
	printf("Par   ");
	for(i = 0; i < 9; i++)
		printf("%3i", scorecard[i][0]);
		printf("%4i\n", par);
	printf("Score ");
	for(i = 0; i < 9; i++)
		printf("%3i", scorecard[i][1]);
		printf("%4i\n", cumScore);
	printf("------+--+--+--+--+--+--+--+--+--+----+\n");
}

//start a new hole
void playHole (void) {
	holeOver = false;
	count = 0;
	
	generateBoard(board);
	setPar();
	displayScorecard();
	displayBoard(board);
	
	//play game board until hole is over
	while(!holeOver) {
		playWord();
		displayBoard(board);
		if(count == 25)
			holeOver = true;
	}
	scorecard[hole - 1][1] = (25 - count);
	cumScore += scorecard[hole - 1][1];
}

int main (void) {
    
    char generateChar (void);
    void generateBoard (char array[25]);
    void displayBoard (char matrix[25]);
    void playHole (void);
    void playWord (void);
    void setPar(void);
    
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