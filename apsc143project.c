#include <stdio.h>

#include <stdlib.h>

void boardCreation() ; // function declaration for the creation of the board

void asterisk () ; // function declaration for the function to add asterisks to the board covering the mines

void printGrid (); // function declaration for the function to output grid to console

int check (int row, int col) ; // function declaration for the function to check indicated cell and reveals necessary cells to AI

void flag (int row, int col) ; //function declaration for the function to place flag on indicated hidden cell

int checkWin () ; // function declaration for the function to determine if win condition has been met

char board[10][10] ; //array to hold board information

char aiInfo[10][10] ; //array to hold mine information

int main() {

    srand(2); //seed randomize function


    boardCreation(board); //create game grid

    asterisk(aiInfo); //add asterisks to grid

    printGrid(); //print grid with added mines and asterisks

    char command;

    //variables used in following while loop
    int z = 1;

    int y = 1;

    int row;

    int col;

    while (z && y) { //when z and y equal 1, print the statement to prompt the user to enter commands

        printf("Enter 'c' for check cell, 'f' for flag cell.\n");

        printf("Enter comment & cell row col:\n");

        scanf("%c %d %d", &command, &row, &col); //read user input

        if (command == 'c') { //when user inputs "c" and a row and column, use check function for the cell inputted, and check if win conditions have been met

            z = check(row, col);

            y = checkWin();

        } else if (command =='f') { // when user inputs "f" and a row and column, perform flag function on the inputted cell

            flag(row, col);

        } else  //if user does not use proper form of input, ie a c or f followed by two numbers, print "invalid input"

            printf("Invalid input");




    printGrid(); //print grid with revealed areas

    if (!y){ //if win conditions have been met, print the following win statement

        printf("Congratulations! You win!\n") ;
    }

    else if (!z) { //if a mine has been hit, print the following game over statement

        printf("You hit a mine, game over.\n");

    }

    }

}

void boardCreation () { // function that creates a 10 by 10 grid board and randomly places mines (M's) on the grid

    for (int i=0; i<10; ++i) {

        for (int j=0; j<10; ++j) {

            board[i][j]= '0';
        }
    }

//variables for mine location
int mineRow  ;

int mineCol ;

int numberOfMines = 0 ; //variable counter for the number of mines placed in grid

while (numberOfMines < 10) { //while there is less than 10 mines, perform the following to randomly assign (M's) about the grid

    mineRow = rand() % 10;

    mineCol = rand() % 10;


    if (board[mineRow][mineCol] != 'M') { //if statement to place "M's" as mines in random locations in the grid

        board[mineRow][mineCol] = 'M';

//if statements that add the number of mines each cell is touching on the x and y planes
        if (mineRow != 9 && board[mineRow + 1][mineCol] != 'M') board[mineRow + 1][mineCol]++;

        if (mineRow != 0 && board[mineRow - 1][mineCol] != 'M') board[mineRow - 1][mineCol]++;

        if (mineCol != 9 && board[mineRow][mineCol + 1] != 'M') board[mineRow][mineCol + 1]++;

        if (mineCol != 0 && board[mineRow][mineCol - 1] != 'M') board[mineRow][mineCol - 1]++;

//number of mines eac cell is touching on the diagonal plane
        if (mineCol != 9 && mineRow != 9 && board[mineRow + 1][mineCol + 1] != 'M') board[mineRow + 1][mineCol + 1]++;

        if (mineCol != 0 && mineRow != 0 && board[mineRow - 1][mineCol - 1] != 'M') board[mineRow - 1][mineCol - 1]++;

        if (mineCol != 9 && mineRow != 0 && board[mineRow - 1][mineCol + 1] != 'M') board[mineRow - 1][mineCol + 1]++;

        if (mineCol != 0 && mineRow != 9 && board[mineRow + 1][mineCol - 1] != 'M') board[mineRow + 1][mineCol - 1]++;

        numberOfMines++; //add one to the number of mines everytime a mine is placed

    }
}

}

void asterisk () { //function to place asterisks overtop of the grid to hide the mines

    for (int i = 0; i < 10; ++i) {

        for (int j = 0; j < 10; ++j) {

            aiInfo [i][j] = '*' ;
        }


    }
}

void printGrid()  { //function to print the 10 by 10 grid with randomly placed mines covered by asterisks

    for (int i=0; i<10; ++i) {
        for (int j = 0; j < 10; ++j) {

            printf("%c  ", aiInfo[i][j]);
        }


        printf("\n"); //print next line of grid
    }

}

int check (int row, int col){ //function to check whether a mine is on the user selected cell

        if (board [row][col] != 'M'){ //if the selected cell is not a mine, reveal the cell

            if (board [row][col] == '0'){ //if the selected cell is a zero, reveal adjacent cells using the following if statements

                aiInfo [row][col] = '0' ;

                if(row != 9 && board[row+1][col] != aiInfo[row+1][col]) check(row+1, col) ;

                if(row != 0 && board[row-1][col] != aiInfo[row-1][col]) check(row-1, col) ;

                if(col != 9 && board[row][col+1] != aiInfo[row][col+1]) check(row, col+1) ;

                if(col != 0 && board[row][col-1] != aiInfo[row][col-1]) check(row, col-1) ;


                if (row != 9 && col != 9 && board[row+1][col+1] != aiInfo[row+1][col+1]) check(row+1, col+1) ;

                if (row != 0 && col != 9 && board[row-1][col+1] != aiInfo[row-1][col+1]) check(row-1, col+1) ;

                if (row != 9 && col != 0 && board[row+1][col-1] != aiInfo[row+1][col-1]) check(row+1, col-1) ;

                if (row != 0 && col != 0 && board[row-1][col-1] != aiInfo[row-1][col-1]) check(row-1, col-1) ;

            }

            else{ //if the selected cell is not a mine or a zero, reveal the selected cell

                aiInfo[row][col] = board[row][col] ;
            }
            return 1;
        }

        else { //if the selected cell is a mine, reveal the mine and return 0 to have the player lose the game

            aiInfo[row][col] = board[row][col];

            return 0;
        }
    }

void flag(int row, int col){ //function to add and F to a user flagged cell

        aiInfo[row][col] = 'F' ;
    }

int checkWin () { //function to check if the win conditions have been met

    int x = 0 ; //counter for the following for loops

    for (int i=0; i<10; ++i){

        for (int j=0; j<10; ++j){

            if (aiInfo [i][j] == '*' || aiInfo[i][j]== 'F'){ //if mines are left as asterisks or are flagged, add to counter

                x++ ;
            }
        }

    }

    if (x == 10){
        return 0 ; //return 0 when counter reaches ten
    }
    else{ //if counter does not reach ten, return 1

        return 1;
    }

}








