#include<stdio.h>
#include<stdlib.h>
#include "tic.h"
#define Maxgrid 10

//the grid that will be used to store the moves of the game
char grid[Maxgrid][Maxgrid];
int __Check_Count;
int gsize;

//this function prompts the user to enter the grid size to start a new game
void promptEnterGridSize()
{
	printf("Enter grid size (3-10):");
}

//this function prompts the user to enter the winning length for the new game
//the parameter represents the maximum winning length for this game
void promptEnterWinLength(int max_win_length)
{
	printf("Enter winning length (3-%i):",max_win_length);
}

//this function prompts the user to enter the location of the symbol
void promptChooseLocation(char symbol)
{
	printf("Player %c, Choose Location (row,col):",symbol);
}

//this function is used to show an error message when an index is out of range
void showErrIndex()
{
	printf("Index out of range, please re-enter\n");
}

//this function is used to show an error message when a location is already taken
void showErrTaken()
{
	printf("This location is already taken\n");
}

//this function is used to show the win message at the end of the game
//the parameter represents the symbol of the player who won the game
void showWinMessage(char symbol)
{
	printf("************************************\n");
	printf("Player %c has won the game\n",symbol);
	printf("************************************\n");
}

//this function is used to show a draw game's message at the end of the game
void showGameOverMessage()
{
	printf("Game over, There are no winners\n");
}

//this function is used to prompt the user to choose if they want to play back the game at the end of the game
void promptPlayBackgame()
{
	printf("\nWould you like to play back the recorded game?(y,n)?");
}

//this function to prompt the user to answer with n (next) or e (exit) 
//to indicate if they want to proceed with the game's replay or exit the program respectively
void promptNextOrExit()
{
	printf("Next or Exit (n,e)?");
}

// This function is a wrapper around an if statement to compare the content of the cell at row,col with symbol
// It also counts the number of times the function is called
int check(int row,int col,char symbol)
{
	__Check_Count++;
	if(grid[row][col]==symbol)
		return 1;
	return 0;
}

//This function peeks at a certain cell in the grid but don't need to be used in the main function
int peek(int row,int col)
{
	return grid[row][col];
}

//This function is used to start a new game
// The first parameter (gridsize) represents the size of the grid of the new game
// The second parameter (winlength) is the number of consecutive symbols for the winning case.
int newGame(int gridsize,int winlength)
{
	int i,j;
	gsize = gridsize;
	if(gridsize<3 || gridsize>10)
		return 0;
	else if(winlength<3 || winlength>gridsize)
		return 0;
	else
	{
		for(i=0;i<gridsize;i++)
		{
			for(j=0;j<gridsize;j++)
			{
				grid[i][j]='.';
			}
		}
		return 1;
	}
}

//This function is used to show the game's grid on the terminal screen
void showGrid()
{
	int i,j;
	printf("\n\t");
	for(i=0;i<gsize;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=0;i<gsize;i++)
	{
		printf("%d\t",i);
		for(j=0;j<gsize;j++)
		{

			printf("%c ",grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

//This function is used to make a move by a player in the game
//The first two parameters represent indices of the row and column of the cell in which the player wants to place their symbol.
//The last parameter is the symbol of that player.
int makeMove(int row,int col,char symbol)
{
	if(row<0 || row>=gsize || col<0 ||col>=gsize)
	{
			showErrIndex();
			return 0;
	}
	if(grid[row][col]=='X' || grid[row][col]=='O')
	{
		showErrTaken();
		return 0;
	}

	grid[row][col]=symbol;
	return 1;
}

//This function is used to check if the board is full i.e. if every location of the grid is occupied with either x or o
int boardIsFull()
{
	int i,j,count=0;
	for(i=0;i<gsize;i++)
	{
		for(j=0;j<gsize;j++)
		{
			if(grid[i][j]=='X' || grid[i][j]=='O')
					count++;
		}
	}
	if(count==gsize*gsize)
		return 1;
	else
		return 0;
}

//This function is used to check if there is any horizontal line in the grid that contains a consecutive sequence of the same symbol
int checkHorizontal(char symbol,int length)
{
	int i,j,count;
	if(length<3 || length>gsize)
    {
        return -1;
    }

    if(symbol!='X' && symbol!='O')
        return -1;

	for(i=0;i<gsize;i++)
	{
		count=0;
		for(j=0;j<gsize-1;j++)
		{

			if(grid[i][j]==symbol && grid[i][j]==grid[i][j+1])
            {
                count++;

            }

		}
		if(count>=length-1)
			return 1;

	}
	return 0;

}

//This function is used to check if there is any vertical line in the grid that contains a consecutive sequence of the same symbol
int checkVertical(char symbol,int length)
{
	int i,j,count;
	if(length<3 || length>gsize)
    {
        return -1;
    }

    if(symbol!='X' && symbol!='O')
        return -1;

	for(j=0;j<gsize;j++)
	{
		count=0;
		for(i=0;i<gsize-1;i++)
		{

			if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j])
            {
                count++;


            }

		}
		if(count>=length-1)
			return 1;
	}
	return 0;
}

//This function is used to check if there is any diagonal line in the grid that contains a consecutive sequence of the same symbol
int checkDiagonals(char symbol,int length)
{
	int i,j,count1=0,count2=0,count3=0,count4=0,count5=0,count6=0,count7=0,count8=0;
	int count9=0,count10=0,count11=0,count12=0,count13=0,count14=0,count15=0;
	if(length<3 || length>gsize)
    {
        return -1;
    }

    if(symbol!='X' && symbol!='O')
        return -1;

    for(i=0;i<gsize;i++)
    {

        for(j=0;j<gsize-1;j++)
        {

            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i==j)
                count1++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==1)
                count2++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==2)
                count3++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==3)
                count4++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==4)
                count5++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==5)
                count6++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==6)
                count7++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && i-j==7)
                count8++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==1)
                count9++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==2)
                count10++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==3)
                count11++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==4)
                count12++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==5)
                count13++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==6)
                count14++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j+1] && j-i==7)
                count15++;


        }
        if(count1>=length-1)
            return 1;
        if(count2>=length-1)
            return 1;
        if(count3>=length-1)
            return 1;
        if(count4>=length-1)
            return 1;
        if(count5>=length-1)
            return 1;
        if(count6>=length-1)
            return 1;
        if(count7>=length-1)
            return 1;
        if(count8>=length-1)
            return 1;
        if(count9>=length-1)
            return 1;
        if(count10>=length-1)
            return 1;
        if(count11>=length-1)
            return 1;
        if(count12>=length-1)
            return 1;
        if(count13>=length-1)
            return 1;
        if(count14>=length-1)
            return 1;
        if(count15>=length-1)
            return 1;


    }
    return 0;

}

//This function is used to check if there is any antidiagonal line in the grid that contains a consecutive sequence of the same symbol
int checkAntiDiagonals(char symbol,int length)
{
		int i,j,count1=0,count2=0,count3=0,count4=0,count5=0,count6=0,count7=0,count8=0;
		int count9=0,count10=0,count11=0,count12=0,count13=0,count14=0,count15=0;
		if(length<3 || length>gsize)
        {
            return -1;
        }

        if(symbol!='X' && symbol!='O')
            return -1;

		for(i=0;i<gsize-1;i++)
		{

			for(j=0;j<gsize;j++)
			{

            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize)
                count1++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-1)
                count2++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-2)
                count3++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-3)
                count4++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-4)
                count5++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-5)
                count6++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize-6)
                count7++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+1)
                count8++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+2)
                count9++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+3)
                count10++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+4)
                count11++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+5)
                count12++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+6)
                count13++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+7)
                count14++;
            if(grid[i][j]==symbol && grid[i][j]==grid[i+1][j-1] && i+j==gsize+8)
                count15++;

			}
			if(count1>=length-1)
            return 1;
        if(count2>=length-1)
            return 1;
        if(count3>=length-1)
            return 1;
        if(count4>=length-1)
            return 1;
        if(count5>=length-1)
            return 1;
        if(count6>=length-1)
            return 1;
        if(count7>=length-1)
            return 1;
        if(count8>=length-1)
            return 1;
        if(count9>=length-1)
            return 1;
        if(count10>=length-1)
            return 1;
        if(count11>=length-1)
            return 1;
        if(count12>=length-1)
            return 1;
        if(count13>=length-1)
            return 1;
        if(count14>=length-1)
            return 1;
        if(count15>=length-1)
            return 1;

		}
		return 0;

}

//This function is used to check if a player has won the game by forming a horizontal, vertical, diagonal, or anti-diagonal line
int playerHasWon(char symbol,int length)
{
    if(length<3 || length>gsize)
    {
        return -1;
    }
    if(symbol!='X' && symbol!='O')
        return -1;

	if(checkHorizontal(symbol,length) ||checkVertical(symbol,length)||checkDiagonals(symbol,length)||checkAntiDiagonals(symbol,length))
		return 1;
	else
		return 0;
}

//This function is used to implement a much more efficient version of the playerHasWon function
int effPlayerHasWon(int row,int col,char symbol,int length)
{
    if(row<0 || row>=gsize || col<0 || col>=gsize)
    {
        return -1;
    }
    else if(length<3 || length>gsize)
    {
        return -1;
    }
    else if(symbol!= 'X' && symbol!= 'O')
    {
        return -1;
    }
	  else if(grid[row][col] == '.')
    {
        grid[row][col] = symbol;
    }
    else if(row >= 0 && col >= 0 length < gsize)
    {
        check(row, col, symbol);
        check(row, col, symbol);
        check(row, col, symbol);
        return(playerHasWon(symbol, length));
    }
    return -1;
}

//This function is what runs the game
int  main (int argc, char* argv[])
{
    int maxwinlength,winlength,res,c,r,i,move=0;
    char ch,ch2;
	  int ro[100];
	  int co[100];
	  char sym[100];
        //printf("Hello");
	  while(1)
	  {
		    promptEnterGridSize();
		    scanf("%i", &gsize);
		    maxwinlength = gsize;
		    promptEnterWinLength(maxwinlength);
		    scanf("%i", &winlength);
		    res=newGame(gsize, winlength);
		    if(res)
			      break;
	  }
	  showGrid();
	  while(move < gsize*gsize)
	  {
		    while(1)
		    {
			      promptChooseLocation('X');
			      scanf("%i, %i", &r, &c);
			      res=makeMove(r, c, 'X');
			      if(res)
				    break;
		    }
		    ro[move]  =r;
		    co[move] = c;
		    sym[move] = 'X';
		    move++;

		    showGrid();
		    if(playerHasWon('X', winlength))
		    {
			    showWinMessage('X');
			    break;
		    }
        
		    if(move == gsize*gsize)
		        break;
		    while(1)
		    {
			    promptChooseLocation('O');
			    scanf("%i, %i", &r, &c);
			    res=makeMove(r, c, 'O');
			    if(res)
				      break;
		    }
		    ro[move] = r;
		    co[move] = c;
		    sym[move] = 'O';
		    move++;
		    showGrid();
		    if(playerHasWon('O', winlength))
		    {
			      showWinMessage('O');
			      break;
		    }
	  }
	  res = boardIsFull();
	  if(res)
		    showGameOverMessage();

	  promptPlayBackgame();
	  scanf(" %c", &ch);
	  if(ch == 'y')
	  {
          i = 0;
		      newGame(gsize, winlength);
          grid[ro[i]][co[i]] = sym[i];
          showGrid();
          promptNextOrExit();
          scanf(" %c",&ch2);
		      while((ch2 == 'n' && i < move-1)
		      {
              i++;
              grid[ro[i]][co[i]] = sym[i];
              showGrid();
              promptNextOrExit();
              scanf("%c", &ch2);
		      }
	  }
	  return 0;
}





