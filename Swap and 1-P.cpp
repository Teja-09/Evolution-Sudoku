#include<bits/stdc++.h>
#define n 9
using namespace std;

struct det
{
        int rowmark;
        int colmark;
        int gridmark;
        int sum;
}s;
struct det scorearray[10];
struct det temparray[10];
int space[10][n][n];
int spare[10][n][n];
int p1[n][n],p2[n][n],p3[n][n],summin[10];
struct det fittness(int [][n]);



void copy(int k)
{

                for(int i=0;i<n;i++)
                {
                        for(int j=0;j<n;j++)
                        {
                                space[k][i][j]=spare[k][i][j];
                                scorearray[k]=temparray[k];
                        }
                }

}



void determine()
{
        for(int i=0;i<10;i++)
        {
                if(scorearray[i].sum>temparray[i].sum)
                copy(i);
        }
}

void mutaterow(int p1[n][n],int row,int fillup[n][n])
{

	int count = 0;
	for(int i =0;i<n;i++)
	{
		if(fillup[row][i] != 1)
		{
			++count;
		}
	}
	if(count >=2)
	{
			int x = rand()%4;
		while(fillup[row][x] == 1)
		{
			x = rand()%4;
		}
		int y = rand()%9;
		while(x == y || fillup[row][y]==1)
		{
			y = rand()%9;
		}
	for(int i=0;i<n;i++)
	{
		if(i==x)
		{
			p3[row][i] = p1[row][y];
		}
		else if(i==y)
		{
			p3[row][i] = p1[row][x];
		}
		else
		{
			p3[row][i] = p1[row][i];
		}
		
	}
	
	}
	else if(count < 2)
	{
		for(int i=0 ;i<n ; i++)
		{
		int x=rand()%9+1;
              if(fillup[row][i]!=1)
                p3[row][i]=x;
                else
                p3[row][i]=p1[row][i];	
		}
		
	}



}



void crossrow(int p1[n][n],int p2[n][n],int row)
{
        int x=rand()%10;
        for(int i=0;i<x;i++)    
        {
                p3[row][i]=p1[row][i];
        }
        for(int j=x;j<n;j++)
        {
                p3[row][j]=p2[row][j];
        }
}





void mutation(int p1[n][n],int k,int fillup[n][n])
{
for(int i=0;i<n;i++)
{
		int ran = rand()%9;
        mutaterow(p1,ran,fillup);

}
for(int i=0;i<n;i++)
{
        for(int j=0;j<n;j++)
        {
                spare[k][i][j]=p3[i][j];
        }
}
temparray[k]=fittness(p3);
}



void crossover(int p1[n][n],int p2[n][n],int k)
{
        for(int i=0;i<n;i++)
        {
                crossrow(p1,p2,i);
        }
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                spare[k][i][j]=p3[i][j];
        }
        temparray[k]=fittness(p3);
}





int rowcheck(int board[n][n],int rows)
{
        int count=0;
        for(int i=0;i<n;i++)
        {int ref=board[rows][i];

                for(int j=0;j<n;j++ )
                {
                        if(board[rows][j]==ref)
                        	count++;
                }
        }
        return count;
}
int colcheck(int board[n][n],int col)
{
        int countc=0;
        for(int i=0;i<n;i++)
        {int ref=board[i][col];

                for(int j=0;j<n;j++ )
                {
                        if(board[j][col]==ref)
                        	countc++;
                }
        }
        return countc;
}


int iscol(int board[n][n] )
{       
        int tcountcol=0;
        for(int i=0;i<n;i++)
        {
           tcountcol+=colcheck(board,i);
        }
        return tcountcol;
}






int isrow(int board[n][n] )
{       
        int tcountrow=0;
        for(int i=0;i<n;i++)
        {
           tcountrow+=rowcheck(board,i);
        }
        return tcountrow;
}

int gridcheck(int board[n][n],int row,int col)
{

        int gridcount=0;
        int rm=row+3;
        int cm=col+3;
        for(int k=row;k<rm;k++)
        {
                for(int s=col;s<cm;s++)
                { int ref=board[k][s];

        for(int i=row;i<rm;i++)
        {

                for(int j=col;j<cm;j++)
                {
                        if(board[i][j]==ref)
                        gridcount++;
                }
        }
}
}
return gridcount;

}


int isgrid(int board[n][n])
{int countg=0;
        for(int i=0;i<n;i+=3)
        {
                for(int j=0;j<n;j+=3)
                {

                countg+=gridcheck(board,i,j);
        }
        }
        return countg;
}


struct det fittness(int board[n][n] )
{
        int rowscore=0,colscore=0,gridscore=0;
        rowscore+=isrow(board);           //81
        colscore+=iscol(board);           //81
        gridscore+=isgrid(board);         //81

        s.rowmark=rowscore;
        s.colmark=colscore;
        s.gridmark=gridscore;
        s.sum=rowscore+colscore+gridscore;
        return s;                                               

}
void out(int space[10][n][n])
{
        for(int q=0;q<10;q++)
        {
                for(int i=0;i<n;i++)
                {
                        for(int j=0;j<n;j++)
                        {
                                cout<<space[q][i][j];
                        }
                        cout<<"\n";

                }
                cout<<"\n"<<'\n';
        }
}


void generation(int board[n][n],int fillup[n][n])
{       int dup[n][n];


struct det r;
        {for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        dup[i][j]=board[i][j];
                }
        }

        for(int q=0;q<10;q++)
        {
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {

                        int x=rand()%9+1;

                        if(fillup[i][j]!=1)
                        {
                                dup[i][j]=x;



                        }




                        space[q][i][j]=dup[i][j];
                }
        }
        scorearray[q]=fittness(dup);
    }
}
out(space);     
}











int main()
{   srand(time(NULL));
        // 0 means unassigned cells
        int board[n][n] ={{0, 1, 6, 5, 7, 8, 0, 9, 2},
                      {5, 0, 9, 1, 3, 0, 7, 6, 8},
                      {4, 8, 7, 0, 2, 9, 0, 3, 1},
                      {2, 6, 3, 0, 1, 5, 9, 8, 7},
                      {9, 7, 4, 8, 0, 3, 1, 2, 5},
                      {8, 5, 1, 7, 9, 2, 6, 4, 3},
                      {1, 3, 8, 9, 0, 7, 2, 5, 6},
                      {6, 9, 2, 3, 5, 1, 0, 7, 4},
                      {7, 4, 5, 2, 8, 6, 3, 1, 9}
                                          };



//  {{3, 1, 6, 5, 7, 8, 4, 9, 2},
//                      {5, 2, 9, 1, 3, 4, 7, 6, 8},
//                      {4, 8, 7, 6, 2, 9, 5, 3, 1},
//                      {2, 6, 3, 4, 1, 5, 9, 8, 7},
//                      {9, 7, 4, 8, 6, 3, 1, 2, 5},
//                      {8, 5, 1, 7, 9, 2, 6, 4, 3},
//                      {1, 3, 8, 9, 4, 7, 2, 5, 6},
//                      {6, 9, 2, 3, 5, 1, 8, 7, 4},
//                      {7, 4, 5, 2, 8, 6, 3, 1, 9}
//                                          };


        int fillup[n][n];
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        if(board[i][j]!=0)
                        fillup[i][j]=1;
                        else
                        fillup[i][j]=0;
                }
        }
        
        generation(board,fillup);
        int min1,min2;



        for(int y=0;y<2000;y++)
        {

                cout<< "Generation : " << y << "\n";


         min1=min2=scorearray[0].sum;
        int line1=0,line2=0;
        for(int i=0;i<10;i++)
        {
                cout<<"\n"<<scorearray[i].rowmark<<'\t'<<scorearray[i].colmark<<'\t'<<scorearray[i].gridmark<<'\t'<<scorearray[i].sum<<'\n';
                summin[i]=scorearray[i].sum;
                if(scorearray[i].sum<min1)
                {
                min2=min1;
                min1=scorearray[i].sum;
                line2=line1;
                line1=i;
            }
            else if(scorearray[i].sum<min2&&min2!=min1)
            {
                min2=scorearray[i].sum;
                line2=i;
                }

        }
        if(line1==line2)
        do
        {
                int tie=rand()%10;
                min2=scorearray[tie].sum;
                line2=tie;
        }while(line1==line2);
        cout<<"min sum  "<<min1<<'\t'<<line1<<'\t'<<min2<<'\t'<<line2<<'\n';
        
                for(int i=0;i<n;i++)
                {
                        for(int j=0;j<n;j++)
                        {
                                spare[0][i][j]=space[line1][i][j];
                                spare[1][i][j]=space[line2][i][j];
                                p1[i][j]=space[line1][i][j];
                                p2[i][j]=space[line2][i][j];
                        }
                }
                temparray[0]=scorearray[line1];
                temparray[1]=scorearray[line2];


for(int k=2;k<10;k++)
{
        if(k==2)
        crossover(p1,p2,k);
        if(k==3)
        crossover(p2,p1,k);
        if(k==4)
        mutation(p1,k,fillup);
        if(k==5)
        mutation(p2,k,fillup);
        for(int i=0;i<n;i++)
                {
                        for(int j=0;j<n;j++)
                        {

                                p1[i][j]=space[2][i][j];
                                p2[i][j]=space[3][i][j];
                        }
                }
        if(k==6)
        crossover(p1,p2,k);
        if(k==7)
        crossover(p2,p1,k);
        if(k==8)
        mutation(p1,k,fillup);
        if(k==9)
        mutation(p2,k,fillup);




}



cout<<'\n'<<"determined\n";
determine();







for(int k=0;k<10;k++)
{
        for(int i=0;i<n;i++)
        {
                for(int j=0;j<n;j++)
                {
                        cout<<space[k][i][j];
                }
                cout<<'\n';
        }cout<<'\n';
}               
for(int q1=0;q1<10;q1++)
{
        if(scorearray[q1].sum==243 &&scorearray[q1].rowmark==81 &&scorearray[q1].colmark==81 &&scorearray[q1].gridmark==81)
        {	
               cout<<"---------GOT IT ---------------" << "\n";
                cout<< "Generation is = " << y << "\n";
                for(int i =0;i<n;i++)
                {
                	for(int j=0;j<n;j++)
                	{
                		cout<<space[q1][i][j];
					}
					cout<<'\n';
				}
				cout<<'\n';
        exit(0);
}
}                       

}
        return 0;
}
