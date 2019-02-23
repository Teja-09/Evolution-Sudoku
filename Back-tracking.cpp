#include <stdio.h>
#include<unistd.h>
int board[9][9];
void solvesudoku(int,int);
void display();
void solve(int , int);
int checkrow(int, int);
int checkcolumn(int , int);
int checkgrid(int, int, int);
int main(){    
    for(int i=0;i<9;i++)
	{
    	for(int j=0;j<9;j++)
			{
      			scanf("%d",&board[i][j]);
    		}
  	}
  		solvesudoku(0,0); 
}

void solvesudoku(int row, int column)
{	
	if(row>8)
		{
  			display();
		}
	if(board[row][column]!=0)
		{
  			solve(row,column);
		}
	else
		{
  		for(int num=1;num<=9;num++)
			 {
    			if((checkrow(row,num)==1)&&(checkcolumn(column,num)==1)&&(checkgrid(row,column,num)==1))
					{
     					board[row][column]=num;
      					solve(row,column);
    				}
  			}
  			board[row][column]=0;
	}
}

void solve(int row, int column)
{
  if(column<8)
  {
    solvesudoku(row,column+1);
  }
  else{ 
    solvesudoku(row+1,0);
  }
}

int checkrow(int row,int num)
{
  for(int k=0;k<9;k++)
  {
  if(board[row][k]==num)
  {
    return 0;
  }
  }
    return 1;
}

int checkcolumn(int column,int num){
  for(int k=0;k<9;k++){
    if(board[k][column]==num)
	{
      return 0;
    }
    }
    return 1;
}

int checkgrid(int row,int column,int num)
{
	row = (row/3)*3;
	column = (column/3)*3;
	 for(int r=0;r<3;r++){
      for(int c=0;c<3;c++)
	  {
        if(board[row+r][column+c]==num)
		{
          return 0;
        }
      }
    }
    return 1;
	
	
//  if(row%3==0 && column%3==0){
//    for(int r=0;r<3;r++){
//      for(int c=0;c<3;c++)
//	  {
//        if(board[row+r][column+c]==num)
//		{
//          return 0;
//        }
//      }
//    }
//    return 1;
//  }
}

void display(){
  printf("The final solved sudoku is: \n");
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      printf("%d\t",board[i][j]);
    }
    printf("\n");
  }
}
