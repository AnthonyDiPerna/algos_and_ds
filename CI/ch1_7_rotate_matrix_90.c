#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------
//1.7 rotate matrix 90deg
//-----------------

// T: O(n*n) S: O(1) - touch every value in matrix/table

//In place matrix rotation
//Assume - Always square
void rotate(int matrix[][3], int matrixSize, int* matrixColSize) {
    int tmp = 0;
    
    //How many rows to process
    //3x3 - only outer matrix (same for 2x2 and 1x1)
    //4x4 - outer matrix and inner matrix (same for 5x5)
    //6x6 - 
    int totalRowsToProcess = *matrixColSize < 3 ? 1 : *matrixColSize / 2;
    
    int row = 0;
    while (row < totalRowsToProcess)
    {
        int currRow = row;
            
        for (int i=row; i < (matrixSize-1-row); i++)
        {
            //(0,0) curr=1
            int currCol = i;
            int currVal = matrix[currRow][currCol];

            //4 times to rotate 90deg (360 / 90 = 4)
            for (int j=0; j < 4; j++)
            {
                //(0,2) = 1
                int nextRow = currCol;
                int nextCol = matrixSize - currRow - 1;

                //printf ("\n currRowCol %d,%d: ", currRow,currCol);
                //printf ("\n nextRowCol %d,%d: ", nextRow,nextCol);

                //Get current spot and next spot
                int nextVal = matrix[nextRow][nextCol];

                tmp = nextVal;                           //tmp  = 3
                matrix[nextRow][nextCol] = currVal;      //next = 1
                currVal = tmp;

                currRow = nextRow;
                currCol = nextCol;
            }        
        }
        row++;
    }
}

void debug_print(int matrix[][3], int rows, int cols)
{
  int j=0;
  int k=0;
  for (k=0;k<cols;k++){
    for (j=0;j<rows;j++){
        printf("\n m[%d][%d] = %d ",k,j,matrix[k][j]);
    }
  printf("\n");
  }
}
int main() {    
  int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
  int rowSize = 3;
  int * colSize = &rowSize;
  
  printf("\n---INPUT---");
  debug_print((int**)matrix,rowSize,*colSize);
  rotate(matrix,rowSize,colSize);
  printf("\n---ROTATED 90---");
  debug_print((int**)matrix,rowSize,*colSize);

  return 0;
}