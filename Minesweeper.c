//Author: Kiana Partovi
//Purpose: Create a program that implements the functionality of the minesweeper game
//Date: 12/13/22

#include <time.h>
#include <stdlib.h>
#include <stdio.h>  // pre processor directive
#define FILE_NAME "field.txt"  // file for the field of numbers
#define FILETWO "scores.txt"  //file for the saved names and scores
#define rows 8  // macro for row size of board
#define cols 8  //macro for column size of board
#define SIZE 100  //macro for size of name character array

// function prototypes
void fileIntoArray (FILE*, char [][cols]);
void declaringThePrintingArray (char [][cols]);
void printBoard (char [][cols]);
char getWhichCell (int*, int*);
void flagCell (char [][cols], int, int);
int checkCell (char [][cols], char [][cols], int, int);
int unconverCell (char [][cols], char [][cols], int row, int col);
int didYouWin (char [][cols], char [][cols]);
void readScores (FILE*);
void appendFile (FILE*, char [], int);
void uncoverZero(char otherArray[][cols], char board[][cols], int row, int col);
void randomBoard(char board[][cols]);
// main function
int main () {

    FILE* file;  //file stream pointer
    FILE* f;  //file stream pointer
    char board[rows][cols];  // character array for loaded board
    char otherArray[rows][cols];  // character array for updated board
    int row, col;  // integers for row and column positions
    char option;  // character for user options
    char playAgain = 'Y';  // character for the play again
    int checker = 0; // integer for bomb check
    char name[SIZE];  // character string array for name
    int afterScore = 0;  // integer for winning score tracker

    file = fopen(FILE_NAME, "r");  // opening the file in read mode
    printf("(R)andom or (F)ile: ");
    scanf(" %c",&option);
    if(option == 'F'){
        fileIntoArray(file, board);  // call of the function to store data
    }
    else if(option == 'R'){
        randomBoard(board);
    }
    if (file == NULL) {  // checking if the file can't be opened
        printf("Can't open file\n");
    } else {
int bombChecker = 0;
while (playAgain == 'Y') {
   declaringThePrintingArray(otherArray);  // set the other 2D array to blank through this function call
   f = fopen(FILETWO, "r");  // opening scores.txt file in read mode
     if (f == NULL) {
                printf("Can't open file\n");
   } else {
printf("BEAT THE HIGH SCORES!\n");
           readScores(f);  // prints whatever is currently in the file through the call of this function
             printf("\n\n\n");  // printing space for aesthetic
   }
            fclose(f);  // closing the file
   printBoard(otherArray);  // calling this function to print the entire game board out
   do {
       printf("%c",otherArray[8][1]);
        //printBoard(board);
option = getWhichCell(&row, &col);  // getting user input to do a switch for the different cases
        switch (option) {
                   case 0:
   break;
                    case 'M':
   flagCell(otherArray, row - 1, col - 1);  // flags cell
   printBoard (otherArray);  // prints updated board
     break;
   case 'U':
   if (board[row-1][col-1] == '_'){
       uncoverZero(otherArray, board, row - 1, col - 1);
        bombChecker = 0;
       
   }
   
   else{
       bombChecker = unconverCell (otherArray, board, row - 1 , col - 1);}  // uncovers cell
   printBoard (otherArray);
   break;
   case 'C':
   bombChecker = checkCell (otherArray, board, row - 1, col - 1);  // checks surrounding cells
   printBoard (otherArray);
   break;
   default:
   break;
}
checker = didYouWin(otherArray, board);  // checking for the win
      } while (bombChecker != 1 && checker != 1);  // conditions to continue loop, not hitting a bomb
  if (bombChecker == 1) {
               printf("You lose :(\n");  // you have lost since you hit a bomb
  }
  else {
printf("Winner!\n");  // you have won
afterScore++;  // your score is updated/incremented
  }
           printf("Play again (Y/N)");  
           scanf("\n%c", &playAgain);  // option to play again
      if (playAgain == 'N') {  
      printf("What is your name?");
      scanf("%s", name);  // stores your name if you do not want to play again
     
      f = fopen(FILETWO, "a+");  // reading and appending file
        if (f == NULL) {
                   printf("Can't open file\n");
      } else {
             appendFile(f, name, afterScore);  // updates the scores.txt file through the call of this function
      }
               fclose(f);  // closing file
      f = fopen(FILETWO, "a+");  // opens file in read and append mode
      f = fopen(FILETWO, "r");  // opens file in read mode
               printf("Winners!\n");
        if (f == NULL) {
                   printf("Can't open file\n");
      } else {
             readScores(f);  // prints all of the winners through this function call
      }
               fclose(f);  // closing file
               break;
  } else if (playAgain == 'Y') {
printf("We are going to play again\n");
printf("(R)andom or (F)ile:" );
    scanf(" %c",&option);
    if(option == 'F'){
        fileIntoArray(file, board);  // call of the function to store data
    }
    else if(option == 'R'){
        randomBoard(board);
    }
           } else {
      printf("Invalid Input\n");
  }
}
    }
    fclose (file);  // closing file
   

return 0;
}
void randomBoard(char board[][cols]){
    int row,col,numBombs=48;
    for(int i = 0;i<8;i++){
        for(int n = 0;n<8;n++){
            board[n][i] = '_';
        }    
    }
    srand(time(0));
    // Use current time as seed for random generator
    for(int count=0;count<8;count++){
        
    
    
    row = (rand() % 8);
    col = (rand() % 8);
    board[row][col] = 'F';
       for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < 8 && j >= 0 && j < 8) {
                    for (int n = i - 1; n <= i + 1; n++) {
                        for (int m = j - 1; m <= j + 1; m++) {
                            if (n >= 0 && n != 8 && m >= 0 && m != 8 && board[n][m]=='F') {
                                numBombs += 1;
                            }
                        }
                    }
                    if (board[i][j]!='F'){
                        board[i][j] = numBombs;
                        if(board[i][j]=='0'){
                            board[i][j]=' ';
                        }
                    }
                    numBombs = 48;
                }
            }
        }
    
    }
}
void uncoverZero(char otherArray[][cols], char board[][cols], int row, int col){
       // for loops to check adjacencies
   int num,row2=row,col2=col,debugger;

       num = 1;
   for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
   // selection for edge cases check
            if (i >= 0 && i < rows && j >= 0 && j < cols) {
       // setting the character values based on what is behind the updated board
                if (board[i][j] == '_') {
                    otherArray[i][j] = '_';
                }
            }
        }
    }
    for(int k =0;k!=64;k++){
    for(int i =0; i != 8; i++){  
            for(int n = 0; n != 8; n++){
                if((otherArray[n][i] == '_')&&(board[n][i] == '_')){
                    
                    if (n<7){
                        num = unconverCell (otherArray, board, n+1 , i);
                    }
                    if (i<7){
                        num = unconverCell (otherArray, board, n , i+1);
                    }
                    if (n>0){
                        num = unconverCell (otherArray, board, n-1 , i);
                    }
                    if (i>0){
                    num = unconverCell (otherArray, board, n , i-1);
                    }
                    if ((i>0)&&(n<7)){
                        num = unconverCell (otherArray, board, n+1 , i-1);
                    }
                    if ((i>0)&&(n>0)){
                        num = unconverCell (otherArray, board, n-1 , i-1);
                    }
                    if ((i<7)&&(n<7)){
                        num = unconverCell (otherArray, board, n+1 , i+1);
                    }
                    if ((i<7)&&(n>0)){
                        num = unconverCell (otherArray, board, n-1 , i+1);
                    }
                }
                
            }
    }

}
    
}

// This function will store the data from the field.txt file into the program.
//@param file pointer to access the file
//@param character 2D array for the board of minesweeper
void fileIntoArray (FILE* fp, char board[][cols]) {

        int X, Y, temp;
        for(X = 0; X < rows; X++) {
            for(Y = 0; Y < cols; Y++) {
       (fscanf(fp, "%d", &temp));  // scanning values into a temporary integer variable
           if (temp == 0) {  // using selection to set the integer values to character values in the 2D array
           board[X][Y] = '_';
       } else if (temp == 1) {
           board[X][Y] = '1';
       } else if (temp == 2) {
           board[X][Y] = '2';
       } else if (temp == 3) {
           board[X][Y] = '3';
       } else {
           board[X][Y] = 'F';  //if none of the above occurs, the spot is a bomb so it is flagged
       }
   
   }
        }
}

// This function will set another array to all blank character values. This will allow for this board to be updated.
//@param character 2D array for the updated minesweeper board
void declaringThePrintingArray (char otherArray[][cols]) {

    // accessing all elements of the array
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
   otherArray[i][j] = ' ';   // sets the elements to blank
}
    }
}

// This function will display to the screen the board with the aesthetics.
//@param character 2D array for the updated minesweeper board
void printBoard (char otherArray[][cols]) {
   
    printf("    1   2   3   4   5   6   7   8\n");
    for(int i =0; i != 8; i++){  // looping to print out updated 2D array
        printf("  ---------------------------------\n%d ",i+1);
            for(int n = 0; n != 8; n++){
                printf("| %c ",otherArray[i][n]);
            }
        printf("|\n");
    }
    printf("  ---------------------------------\n");
}

// This function will interact with the user for which cell position they would like to play and then goes on to prompt for more information from the user.
//@param a pointer integer for the most recent row position
//@param a pointer integer for the most recent column position
char getWhichCell (int* row, int* col) {

    char choice;
    int tempR = 0;
    int tempC = 0;
    printf("Which cell?");
    scanf(" %d %d", &tempR, &tempC);  // storing the cell coordinates
    *row = tempR;  // setting the row coordinate in a pointer variable
    *col = tempC;  // setting the column coordinate in a pointer variable

    // next set of options
    printf("(M)ark this cell with a bomb flag\n");
    printf("(U)ncover to reveal what's in this cell\n");
    printf("(C)heck the surrounding cells\n");
    printf("Which move?");
    scanf(" %c", &choice);
    return choice;
}

// This function will mark the cell with a character value if you choose to mark the cell with a flag.
//@param character 2D array for the updated minesweeper board
//@param integer row for the access of that space
//@param integer column for the access of that space
void flagCell (char otherArray[][cols], int row, int col) {
    otherArray[row][col] = 'F';  // at a specified coordinate will place a character value to mark a placeholder of a to be or not to be bomb
}

// This function will print out the adjacencies around a chosen cell.
//@param character 2D array for the updated minesweeper board
//@param character 2D array for the board of minesweeper
//@param integer row for the access of that space
//@param integer column for the access of that space
//@return integer value for if there is a bomb value or not.
int checkCell (char otherArray[][cols], char board[][cols], int row, int col) {
   int output = 0;
   // for loops to check adjacencies
   for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
   // selection for edge cases check
            if (i >= 0 && i < rows && j >= 0 && j < cols) {
       // setting the character values based on what is behind the updated board
if (board[i][j] == '_') {
   otherArray[i][j] = '_';
} else if (board[i][j] == '1') {
   otherArray[i][j] = '1';
} else if (board[i][j] == '2') {
   otherArray[i][j] = '2';
} else if (board[i][j] == '3') {
   otherArray[i][j] = '3';
} else {
   otherArray[i][j] = 'X';
   output = 1;
}
   }
}
    }
    return output;
}

// This function will uncover the current chosen cell with adjacencies, or a bomb.
//@param character 2D array for the updated minesweeper board
//@param character 2D array for the board of minesweeper
//@param integer row for the access of that space
//@param integer column for the access of that space
//@return integer value for if there is a bomb or not
int unconverCell (char otherArray[][cols], char board[][cols], int row, int col) {
    // gets the row, gets the cell and just copies
    int output = 0;
    if (board[row][col] == '_') {
otherArray[row][col] = '_';
    } else if (board[row][col] == '1') {
        otherArray[row][col] = '1';
    } else if (board[row][col] == '2') {
        otherArray[row][col] = '2';
    } else if (board[row][col] == '3') {
        otherArray[row][col] = '3';
    } else if(board[row][col] == 'F') {
        otherArray[row][col] = 'X';
output = 1;
    }
    return output;
}

// This function will check the equalities of the array to see if they match and hence win the game.
//@param character 2D array for the updated minesweeper board
//@param character 2D array for the board of minesweeper
//@return an integer value for if it is true that you won or false that you didn't win
int didYouWin (char otherArray[][cols], char board[][cols]) {

    // accessing all the elements in the array
    for(int a = 0; a < rows; a++) {
        for(int b = 0; b < cols; b++) {
   if (otherArray[a][b] != board[a][b]) {  // if the arrays are not equal to each other then it will return 0
       return 0;
            }
}
    }
    return 1;  // otherwise, the arrays are equal and a one will be returned
}

// This function will store the names and scores from the scores.txt file
//@param file pointer to pass in the file
void readScores (FILE* f) {
    char names[SIZE];  // for string array
    int score;
    while (fscanf(f, "%s %d", names, &score) == 2) {  // scanning two at a time
        printf("%s: %d\n", names, score);  // printing the variables in this fashion
    }

}

// This function will update the scores.txt file with names and scores
//@param file pointer to pass in the file
//@param character string array for letters of name
//@param integer for updated score
void appendFile (FILE* f, char name[], int afterScore) {
    fprintf(f , "%s %d\n", name , afterScore);  //updates to the file with the winner or losers name and their updated score
}