#include <vector>
#include <iostream>
#define MAXTERMS 101
using namespace std;

typedef struct{
	int row;
	int col;
	int value;
}term;

int** MatrixInput(int row,int col){
	int **array;	
	array= new int*[row];
	for(int i=0;i<row;i++){
		array[i]=new int[col];
	}

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			scanf("%d",&array[i][j]);
		}
	}
	return array;
}

void SparseMatrix(int** array, term* sparse,int row,int col){

	sparse[0].row=row;
	sparse[0].col=col;
	int count;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(array[i][j]!=0){
				count++;
				sparse[count].row=i;
				sparse[count].col=j;
				sparse[count].value=array[i][j];	
			}
		}
	}
	sparse[0].value=count;

}
void FastTranspose(term* a,term* b){
	int row_terms[]
}
void PrintSparseMatrix(term* sparse){
	printf("index     row     col     value\n");
	for(int i=0;i<=sparse[0].value;i++){
		printf("%d%10d%10d%10d\n",i,sparse[i].row,sparse[i].col,sparse[i].value);
	}
}
int main(){
	int **array1, **array2;
	int row1,col1,row2,col2;
	scanf("%d %d",&row1,&col1);
	array1=MatrixInput(row1,col1);
	scanf("%d %d",&row2,&col2);
	array2=MatrixInput(row2,col2);
	
	term a1[MAXTERMS], a2[MAXTERMS], a2T[MAXTERMS];
	SparseMatrix(array1,a1,row1,col1);
	SparseMatrix(array2,a2,row2,col2);
	FastTranspose(a2,a2T);

}
