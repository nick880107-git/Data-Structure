#include <vector>
#include <iostream>

using namespace std;

typedef struct{
	int row;
	int col;
	int value;
}term;

int** MatrixInput(){
	int **array;
	int row,col;
	printf("¿é¤Jrow,col:");
	scanf("%d %d",&row,&col);
	
	array= new int*[row];
	for(int i=0;i<row;i++){
		array[i]=new int[col];
	}
	
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			scanf("%d",array[i][j]);
		}
	}
	return array;
}

int main(){
	int **array1, **array2;
	array1=MatrixInput();
	array2=MatrixInput();
	
}
