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
	if(a[0].value>0){		//�}�C������ 
		for(i=0;i<a[0].col;i++){	//��l��row_terms 
			row_terms[i]=0;
		}
		for(i=1;i<a[0].value;i++){	//�w�������row�O�� 
			row_terms[a[i].col]++;
		}
		start_pos[0]=1;					//��l�Ƽи�
		for(i=1;i<a[0].col;i++){		//�и� 
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

int compare(int i,int j){
	int result;
	if(i<j){
		result=-1;
	}
	else if(i==j){
		result=0;
	}
	else if(i>j){
		result=1;
	}
	return result;
}

void StoreSum(term* c, int index, int row, int col, int value){
	c[index].row=row;
	c[index].col=col;
	c[index].value=value;
}

void Multi(term* a, term* b, term* c){	//b���w��m���x�}�A�ñN�p�⵲�G�s��c 
	int d_index;
	int row=a[0].row;					//����c[row][col]�Ϊ�index 
	int col;
	int i,j;							//������ea,b�x�}��index 
	int a_baseIndex=1;					//����a�x�}��erow�Ĥ@�ӭȪ�index 
	int sum=0;
	
	for(i=1;i<=a[0].value;){			//�C�^��o�̡A���b�x�}�w����Ū�����A�}�l�i��a���U�@row�p�� 
		col=b[1].row;					//b�x�}�q�YŪ�_
		for(j=1;j<=b[0].value;){
			if(a[i].row!=row){			//a�x�}Ū���W�L��erow�A�^���erow���Ĥ@�ӭȪ���m���sŪ�� 
				if(sum!=0){
					d_index++;
					StoreSum(c,d_index,row,col,sum);
					sum=0;
				}				
				i=a_baseIndex;
				for(;b[j].row==col;j++)	//�]��a�|�W�L��ܷ�eb��row�w�p�⧹���A�e���U�@��row����m 
					;
				col=b[j].row;
			}
			else if(b[j].row!=col){		//b�x�}Ū���W�L��erow ����erow�w�p�⧹�� 
				if(sum!=0){
					d_index++;
					StoreSum(c,d_index,row,col,sum);
					sum=0;
				}
				i=a_baseIndex;			//a�x�}�^���erow�Ĥ@�ӭȪ�index�A�ǳƤU�@��col���p�� 
				col=b[j].row;
			}
			else {
				switch(compare(a[i].col,b[j].col)){
					case -1:
						i++;
						break;
					case 0:
						sum+=a[i++].value*b[j++].value;
						break;
					case 1:
						j++;
				}
			}
		}
		if(sum!=0){
			d_index++;
			StoreSum(c,d_index,row,col,sum);
			sum=0;
		}
		for(;a[i].row==row;i++)
			;
		a_baseIndex=i;
		row=a[i].row; 
	}
	c[0].row=a[0].row;
	c[0].col=b[0].row;
	c[0].value=d_index;
}



int main(){
	int **array1, **array2;
	int row1,col1,row2,col2;
	term a1[MAXTERMS], a2[MAXTERMS];

	scanf("%d %d",&row1,&col1);
	array1=MatrixInput(row1,col1);
	SparseMatrix(array1,a1,row1,col1);
	
	scanf("%d %d",&row2,&col2);
	array2=MatrixInput(row2,col2);
	SparseMatrix(array2,a2,row2,col2);
	
	term a2T[MAXTERMS];
	FastTranspose(a2,a2T);
	
	term answer[MAXTERMS];
	Multi(a1,a2T,answer);

	PrintSparseMatrix(answer);
}

////���ե� 
//int main(){
//	int **array1;
//	int row1,col1;
//	scanf("%d %d",&row1,&col1);
//	array1=MatrixInput(row1,col1);
//	term a1[MAXTERMS], a1T[MAXTERMS];
//	SparseMatrix(array1,a1,row1,col1);
//	PrintSparseMatrix(a1);
//	FastTranspose(a1,a1T);
//	PrintSparseMatrix(a1T);
//	
//}


