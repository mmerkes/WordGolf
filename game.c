/*
version 0.00004
NOTES:
1. For timed games, running out of time would be a penalty stroke
2. Dictionary does not support plurals or different versions of verbs
	i.e. runs, bells, fills, etc.
3. Create arrays with different combinations of pars on holes
4. Adjust letter generator to pick easier letters for par 3s and 4s
Dictionary: perhaps copy hidden file /Library/spelling/localdictionary ?
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


char board[25]; //houses characters for the board
char temp[25];	//temporarily houses board characters while checking validity
char word[25]; //stores the characters of the word input from user
int length, count, cumScore = 0, hole = 1, players = 1, player = 0, score; //length of word, count, adds score, hole
bool holeOver = false, escape = false;
int pars[9] = { 4, 4, 5, 3, 4, 5, 3, 4, 5 };
int par = 32;
int scorecard[9][4]; //[hole][score]
char clear;
char names[4][15];

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

//Create an array of 25 random characters, takes board as argument
void generateBoard (char array[25]) {
	int i;
	
	for(i = 0; i < (pars[hole - 1]* pars[hole - 1]); i++)
		array[i] = generateChar();
	for( ; i < 25; i++)
		array[i] = 0;
}

//displays the top and bottom of the board
void displayEdge (void) {
	int i;
	
	printf("  +---");
    	
    for(i = 0; i < pars[hole - 1]; i++)
    	printf("+---");
    
    printf("+\n");
}

//print game board
void displayBoard (char matrix[25]) {
	int i, column;
    
    printf("\n");
    displayEdge();
	for (i = 0; i < (pars[hole - 1] * pars[hole - 1]); ) {
		printf("  |");
		for ( column = 1; column <= pars[hole - 1]; ++column ) {
			printf ("%4c", matrix[i]);
			i++;
		}
		printf ("   |\n");
	}
	displayEdge();
	
	printf("\n");
	if(!holeOver) {
		printf("Enter next word or\n");
		printf("0 to putt out and\n");
		printf("end the hole\n\n");
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
			escape = true;
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

//checks the word in the dictionary
bool wordLookup(void) {
	static const char filename[] = "/usr/share/dict/words";
    FILE *file = fopen ( filename, "r" );
	bool wordFound = false;
    char spellcheck[26];
    int i = 0;
    char c;
    
    for(i = 0; i < length; i++)
    	spellcheck[i] = word[i] + 32;
    spellcheck[i] = '\n';
    i++;
    for( ; i < 26; i++)
        spellcheck[i] = 0;
    i = 0;
    
    if ( file != NULL )
    {
        char line [ 26 ]; //maximum line length
        while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
        {
      		if(strcmp(spellcheck, line) == 0 ) {
      			wordFound = true;
      			break;
      		}
        }
        fclose ( file );
    }
    else
    {
        perror ( filename ); //why file didn't open
    }
    if(!wordFound)
    	printf("\nNice try buck-o, but that's not a word!\nTry again\n\n");
    
    return wordFound;
}

//verify that all of the letters are available to use
bool checkLetters(void) {
	bool validLetter, validWord = true; //Do I need to declare validWord?
	int i, j;
	
	for(i = 0; i < length; i++) {
		if(holeOver) //necessary?
			break;
		validLetter = false;
		for(j = 0; j < (pars[hole - 1] * pars[hole - 1]); j++) {
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
	if(validWord && !escape)
		validWord = wordLookup();
	if(validWord && !escape) {
		score++;
	}
	if(validWord)
		count += length;
		
	return validWord;
}

//play a word on the game board
void playWord (void) {
    int i, length;
	bool validWord = false;
	
	while(!validWord) {
		if(holeOver) //Why did I add this?
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

//Prints the line in scoreboard
void printLine (void) {
	printf("------+--+--+--+--+--+--+--+--+--+----+\n");
}

//print score
void printScore(int p) {
	int i;
	
	//Print player name
	for(i = 0; i < 6; i++) {
		printf("%c", names[p][i]); 
		if(names[p][i] == '\0')
			printf(" ");	
	}
		
	cumScore = 0;
	
	for(i = 0; i < 9; i++) {
		if(scorecard[i][p] == 0)
			printf("%3c", ' ');
		else
			printf("%3i", scorecard[i][p]);
		cumScore += scorecard[i][p];
	}
		printf("%4i\n", cumScore);
}

//print scorecard
void displayScorecard(void) {
	int i, j;
	
	printf("SCORECARD\n");
	printf("        1  2  3  4  5  6  7  8  9  TOTAL\n");
	printLine();
	printf("PAR   ");
	
	//print pars
	for(i = 0; i < 9; i++)
		printf("%3i", pars[i]);
	printf("%4i\n", par);
	
	//print the score for each player
	for(j = 0; j < players; j++) {
		if(j == 2 && players == 4)
			printLine();
		printScore(j);
	}
	printLine();
}

//start a new hole
void playHole (void) {
	holeOver = false, escape = false;
	count = 0, score = 0;
	int i;
	char c;
	
	generateBoard(board);
	displayScorecard();
	displayBoard(board);
	
	//play game board until hole is over
	while(!holeOver) {
		for(i = 0; i < 25; i++)
        	word[i] = 0;
		playWord();
		displayBoard(board);
		
		//if there are only two or less letters left, end the hole
		if(count >= ((pars[hole - 1] * pars[hole - 1]) - 2)) {
			holeOver = true; 
		}
	}
	//Take the score
	scorecard[hole - 1][player] = 
				((pars[hole - 1] * pars[hole - 1]) - count) + score;
	printf("The hole is over and you scored a %i.\n\n", scorecard[hole - 1][player]);
	
	//pause game
	
	printf("Press enter to go to the next hole.\n");
	while((c = getchar()) != '\n');
}

//Get the number of players
void getPlayers (void) {
	bool validPlayers = false;
	printf("\n\n");

	while(!validPlayers) {
		printf("How many players are there? ");
		scanf("%i%c", &players, &clear);
		if(players >= 1 && players <= 4)
			validPlayers = true;
		else
			printf("\nYou can only choose 1 - 4 players\n\n");
	}
	printf("\n");
}

//Get players names
void getNames(void) {
	int p, j;
	
	//initialize names
	for(p = 0; p < players; p++)
		for(j = 0; j < 15; j++)
			names[p][j] = '\0';
			
	
	//initialize scorecards
    for(p = 0; p < 9; p++) {
    	for(j = 0; j < players; j++);
    	scorecard[p][j] = 0;
    }
	
	for(p = 0; p < players; p++){
		printf("Enter a name for player %i: ", p);
		scanf("%s%c", &names[p][0], &clear);
	}
	printf("\n");
}

int main (void) {
    
    char generateChar (void);
    void generateBoard (char array[25]);
    void displayBoard (char matrix[25]);
    void playHole (void);
    void playWord (void);

    bool checkLetters(void);
    int getWord (void);
    
	srand(time(NULL));
	
	getPlayers();
	getNames();
	
	//play a round
    for( ; hole <= 9; hole++) {
    	player = 0;
    	for( ; player < players; player++) {
			playHole();
			printf("\n\n");
		}
    }
    
    displayScorecard();
    printf("That's it! See you next round!\n");
    
    return 0;
}
