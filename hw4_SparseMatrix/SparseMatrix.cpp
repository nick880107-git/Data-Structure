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
	int *row_terms, *start_pos;
	int i,j;
	row_terms=new int[a[0].col];
	start_pos=new int[a[0].col];
	b[0].row=a[0].col;
	b[0].col=a[0].row;
	b[0].value=a[0].value;
	if(a[0].value>0){		//陣列不為空 
		for(i=0;i<a[0].col;i++){	//初始化row_terms 
			row_terms[i]=0;
		}
		for(i=1;i<a[0].value;i++){	//針對對應的row記數 
			row_terms[a[i].col]++;
		}
		start_pos[0]=1;					//初始化標號
		for(i=1;i<a[0].col;i++){		//標號 
			start_pos[i]=start_pos[i-1]+row_terms[i-1];
		}
		for(i=1;i<=a[0].value;i++){ 
			j=start_pos[a[i].col]++;
			b[j].row=a[i].col;
			b[j].col=a[i].row;
			b[j].value=a[i].value;
		} 
	}
}
void PrintSparseMatrix(term* sparse){
	printf("index     row     col     value\n");
	for(int i=0;i<=sparse[0].value;i++){
		printf("%d%10d%10d%10d\n",i,sparse[i].row,sparse[i].col,sparse[i].value);
	}
}

void Multi(term* a, term* b, term* c){	//b為已轉置的矩陣,計算a.bT的結果並存於c 
	c[0].row=a[0].row;
	c[0].col=b[0].row;
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
	term answer[MAXTERMS];
	Multi(a1,a2T,answer);
	PrintSparseMatrix(answer);

}

//測試用 
int main(){
	int **array1;
	int row1,col1;
	scanf("%d %d",&row1,&col1);
	array1=MatrixInput(row1,col1);
	term a1[MAXTERMS], a1T[MAXTERMS];
	SparseMatrix(array1,a1,row1,col1);
	PrintSparseMatrix(a1);
	FastTranspose(a1,a1T);
	PrintSparseMatrix(a1T);
	
}


