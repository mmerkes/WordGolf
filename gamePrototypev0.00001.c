/*
version 0.00001
NOTES:
1. Need to change frequency of letters; possibly by rand() to 100 which
	choose letters from preset array of 100 letters by how often they
	show up in American English
	*Could store letters in a 2D array and the second column could be
	how many points they are worth
2. Need to check words by dictionary
3. For timed games, running out of time would be a penalty stroke
4. Print what hole it is and include par, calculated by difficulty
	of letters in board.

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//need to ignore case of input
//Rank difficulty by letter


char board[25];
char temp[25];
char word[25];
int length, count, score = 0;
bool holeOver = false;

char letters[

//Get random character
char generateChar (void) {
    
	char randChar;
	
	//65 in ASCII is 'A'
	randChar = (char)(26 * (rand() / (RAND_MAX +
                                      1.0)) + 65);
	
	return randChar;
}

//Create an array of 25 random characters
void generateBoard (char array[25]) {
	
	int i;
	
	for(i = 0; i < 25; i++)
		array[i] = generateChar();
}

//print game board
void displayMatrix (char matrix[25]) {
	int i, column;
    
	for (i = 0; i < 25; ) {
		for ( column = 1; column <= 5; ++column ) {
			printf ("%3c", matrix[i]);
			i++;
		}
		printf ("\n");
	}
	if(!holeOver) {
		printf("Enter next word or\n");
		printf("0 to putt out and\n");
		printf("end the hole\n");
	}
}

//get a word from user
int getWord (void) {
	char c;
    length = 0;
	
	while((c = getchar()) != '\n') {
		if(c == '0') {
			holeOver = true;
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
			displayMatrix(board);
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

//start a new hole
void playHole (void) {
	holeOver = false;
	count = 0;
	
	generateBoard(board);
	displayMatrix(board);
	
	//play game board until hole is over
	while(!holeOver) {
		playWord();
		displayMatrix(board);
		if(count == 25)
			holeOver = true;
	}
	score += (25 - count);
}

int main (void) {
    
    char generateChar (void);
    void generateBoard (char array[25]);
    void displayMatrix (char matrix[25]);
    void playHole (void);
    void playWord (void);
    bool checkLetters(void);
    int getWord (void);
    
    int i, hole;
    
	srand(time(NULL));
	
	for(i = 0; i < 25; i++)
        word[i] = '0';
	
    for(hole = 1; hole <= 9; hole++) {
		playHole();
		if(hole == 1)
			printf("You've played 1 hole and your score is: %i\n", score);
		else
			printf("You've played %i holes and your score is: %i\n\n", 
				hole, score);
    }
    
    printf("That's it! See you next round!\n");
    
    return 0;
    
	//Ask user to enter word x
	//	Check that all letters are on board
	//		Create second temp array to check
	//		that letters are used only once
	//	Remove all used letters from the array
	//		Could alternate two arrays
    
	//Print new array and repeat until all letters are used
	//	Except value to end round
	
	//Add up letters remaining
	//	Print score
    
	//Draw a new board and repeat for 9 holes
    
}