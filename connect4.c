// connect4.c - game based on Connect 4
// Author - James Birchall
// Date - 6th October 2012

#include <stdio.h>

void welcome();
void initGrid(char[5][6]);
void drawGrid(char[5][6]);
int promptPlayer(int);
int checkSetValue(char[5][6], int);
int setGrid(char[5][6], int, int);
int checkFourInRow(char[5][6], int, int);
int checkFull(char[5][6]);
void win(int);
void draw();



int main(int argc, char *argv[]){
	
	int gameOver = 0;
	int currentPlayer = 1;
	
	int gridWidth = 6;
	int gridHeight = 5;
	
	char connect4grid[gridHeight][gridWidth];
	
	welcome();
	
	initGrid(connect4grid);
	
	while(gameOver != 1){
		
		drawGrid(connect4grid);	
		
		int enteredValue; //column value, x - need to minus one to use
		int heightValue; //found when checking grid, y - don't need to change
		
		enteredValue = promptPlayer(currentPlayer);
		
		if(checkSetValue(connect4grid, enteredValue) == 0){
			printf("That space is already taken! Shame on you...try again...\n");
			continue;
		}
		else{
			heightValue = setGrid(connect4grid, currentPlayer, enteredValue);
		}
		
		if(checkFourInRow(connect4grid, enteredValue, heightValue) != 0){
			gameOver = 1;
			drawGrid(connect4grid);
			win(currentPlayer);
		} else if(checkFull(connect4grid) == 1){
			gameOver = 1;
			drawGrid(connect4grid);
			draw();
		}
		
		if(currentPlayer == 1)
			currentPlayer = 2;
		else
			currentPlayer = 1;		
	}
	
	printf("\nGoodbye!\n");
	
	return 0;
}

void welcome(){
	printf("\n\nWelcome to Connect 4\n");
	printf("\nThis version brought to you by James Birchall\n");
	printf("\nSmee Studios 2012\n\n");
}

void initGrid(char connectgridarray[5][6]){
	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 6; j++){
				connectgridarray[j][i] = ' ';
		}		
	}
}

void drawGrid(char connectgridarray[5][6]){

	printf("\n\t");
	for(int i = 1; i <=7; i++){
		printf("| %d |", i);
	}
	printf("\n\t");
	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 6; j++){
				printf("| %c |",connectgridarray[j][i]);
		}		
		printf("\n\t");
	}
	printf("\n");
}

int promptPlayer(int player){
  int scannedNumber = 0;
  int wrong = 0;

  while(scannedNumber < 1 || scannedNumber > 7){
    if(0 == wrong)
      printf("Player %i, enter a grid number still available [1-7]: ", player);
    else
      printf("Invalid number, Player %i, enter a grid number [1-7]: ", player);

    scanf("%d", &scannedNumber);
    wrong = 1;
  }
}

int checkSetValue(char connectgridarray[5][6], int column){
	column -= 1;
	
	if(connectgridarray[column][0] == ' ')
		return 1;
	
	return 0;
}

int setGrid(char connectgridarray[5][6], int currentPlayer, int column){
	
	column -= 1;
	
	for(int i = 5; i >= 0; i--){
		if(connectgridarray[column][i] == ' '){

				if(currentPlayer == 1){
					connectgridarray[column][i] = 'X';
				}
				else{
					connectgridarray[column][i] = 'O';
				}
			return i;
		}
	}
	
	return 0;
}

int checkFourInRow(char connectgridarray[5][6], int column, int height){
	column -= 1;	//to get actual array value from 0;
	
	char characterToCheck = connectgridarray[column][height];
	
	int connect4 = 1;	//once this value = 4 we have our winner!
	
	//check up and down
	connect4 = 1;
	
	for(int i = 1; i <=3 && height+i <= 5 ; i++){
			if(connectgridarray[column][height+i] == characterToCheck)
				connect4++;
	}
	
	for(int i = 1; i <=3 && height-i >= 0; i++){
			if(connectgridarray[column][height-i] == characterToCheck)
				connect4++;	
	}

	if(4 == connect4)
		return 1;		
	
	//check right and left
	connect4 = 1;


	for(int i = 1; i <=3 && column+i <= 6; i++){
		if(connectgridarray[column+i][height] == characterToCheck)
			connect4++;
	}
	
	for(int i = 1; i <=3 && column-i >= 0; i++){
		if(connectgridarray[column-i][height] == characterToCheck)
			connect4++;
	}		
	
	if(4 == connect4)
		return 1;
	
	//check up/left diagonal and down/right diagonal
	connect4 = 1;
	
	for(int i = 1; i <=3 && height+i <= 5 && column+i <= 6 ; i++){
			if(connectgridarray[column+i][height+i] == characterToCheck)
				connect4++;
	}
	for(int i = 1; i <=3 && height-i >= 0 && column-i >= 0; i++){
			if(connectgridarray[column-i][height-i] == characterToCheck)
				connect4++;
	}
	
	if(4 == connect4)
		return 1;
	
	//check up/right diagonal and down/left diagonal
	connect4 = 1;
	for(int i = 1; i <=3 && height-i >= 0 && column+i <= 6 ; i++){
			if(connectgridarray[column+i][height-i] == characterToCheck)
				connect4++;
	}
	for(int i = 1; i <=3 && height+i <= 5 && column-i >= 0; i++){
			if(connectgridarray[column-i][height+i] == characterToCheck)
				connect4++;
	}
	
	if(4 == connect4)
		return 1;
	
	return 0;
}

int checkFull(char connectgridarray[5][6]){
	int full = 0;
	int counter = 0;

	for(int i = 0; i <= 5; i++){
		for(int j = 0; j <= 6; j++){
				if(connectgridarray[j][i] != ' '){
					counter++;
				}
		}		
	}
	
	if(7*6 == counter)
		full = 1;

	return full;
}

void win(int player){
  printf("\n\tCongratulations Player %i, you WIN!\n", player);
}

void draw(){
  printf("\n\tA stalemate...you have DRAWN!\n");
}
