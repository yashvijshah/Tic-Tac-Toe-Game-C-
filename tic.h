//THE HEADER FILE

// the maximum size of the game's grid
define MaxGrid 10			
  
//the game's grid
extern char grid[MaxGrid][MaxGrid];

// prototypes of the functions that we need to implement
// the functions themselves are in the tic.c file
int newGame (int gridsize, int winlength);
int makeMove(int row, int col, char symbol);
int boardIsFull();
int checkHorizontal (char symbol, int length);
int checkVertical (char symbol, int length);
int checkDiagonals (char symbol, int length);
int checkAntiDiagonals (char symbol, int length);
int playerHasWon (char symbol , int length);
int effPlayerHasWon (int row, int col, char symbol , int length);
void showGrid ();

//this function is used in effPlayerHasWon()
int check (int row, int col, char symbol);

int peek (int row, int col);	
extern int __Check_Count;
