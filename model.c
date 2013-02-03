#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>




int main(void) {

	int i;
	int scorecard[9][2];

    //initialize scorecard
    for(i = 0; i < 9; i++) {
    	scorecard[i][0] = 0;
    	scorecard[i][1] = 0;
    }
    
	//print scorecard
	for(i = 0; i < 9; i++) {
		printf(" 1  2  3  4  5  6  7  8  9  TOTAL\n");
		printf("+--+--+--+--+--+--+--+--+--+----+\n");
		printf("%3i%3i%3i%3i%3i%3i%3i%3i%3i %i\n", 3, 4, 4, 4, 5, 5, 3, 4, 4, 39);
		printf("+--+--+--+--+--+--+--+--+--+----+\n");
		printf("%3i%3i%3i%3i%3i%3i%3i%3i%3i %i\n", 4, 3, 12, 4, 6, 4, 5, 2, 12, 56);
		printf("+--+--+--+--+--+--+--+--+--+----+\n");
	}
	
	return 0;
}