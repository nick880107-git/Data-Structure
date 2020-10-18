#include <cstdio>
#include <iostream>
#include <queue>
#define MAXSTACK 100
#define NEW2D(H, W, TYPE) (TYPE **)new2d(H, W, sizeof(TYPE))
using namespace std;

struct point{
	int row;
	int col;
	point *last;
};


int top=-1;
int found=0;
queue <point*> q;
int dir[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
void bfs(int **data,int **vis,point *start,point target,int **path);
void print(int **path);
void *new2d(int m,int n,int size);




int main(){
	int m,n;
	printf("請輸入迷宮大小：");
	scanf("%d %d",&m,&n);
	
	//初始化陣列 
	int **data=NEW2D(m+2,n+2,int);
	int **vis=NEW2D(m+2,n+2,int);
	int **path=NEW2D(m*n,2,int);
	
	for(int t=0;t<n+2;t++){
		data[0][t]=1;
		data[m+1][t]=1;
	} 
	for(int t=0;t<m+2;t++){
		data[t][0]=1;
		data[t][n+1]=1;
	}
	
	for(int i=0;i<m+2;i++){
		for(int j=0;j<n+2;j++){
			vis[i][j]=0;
		}
	}
	
	printf("請輸入迷宮資料：\n");
	for(int i=1;i<=m;i++){
		int j=1;
		char y;
		do{
			scanf("%d",&data[i][j]);
			j++;
		}while((y=getchar())!='\n');
	}
	
	//設定起點終點
	point *start=new point;
	start->row=1;
	start->col=1;
	point target;	 
	target.row=m;
	target.col=n;

	vis[1][1]=1;
	q.push(start);
	bfs(data,vis,start,target,path);
	print(path);
}

void* new2d(int h, int w, int size)
{
    int i;
	void **p;
	try{
		p = (void**)new char[h*sizeof(void*) + h*w*size];
	}
   	catch(std::bad_alloc){
   		printf("out of memory");
	}
    
    for(i = 0; i < h; i++)
        p[i] = ((char *)(p + h)) + i*w*size;

    return p;
}

void bfs(int **data,int **vis,point *start,point target, int **path){
	while(!q.empty()){
		point *position=q.front(); //取得queue儲存的第一個位置
		q.pop();
		if(position->row==target.row && position->col==target.col){
			do{
				top++;
				path[top][0]=position->row;
				path[top][1]=position->col;
				position=position->last;
			}while((position->row!=start->row)||(position->col!=start->col));
			top++;
			path[top][0]=position->row;
			path[top][1]=position->col;
			found=1;
			break;
		}
		else{
			for(int i=0;i<8;i++){
				int row,col;
				row=position->row+dir[i][0];
				col=position->col+dir[i][1];
				if(data[row][col]==0 && vis[row][col]==0){
					point* temp=new point;
					temp->row=row;
					temp->col=col;
					temp->last=position;
					q.push(temp);
					vis[row][col]=1;							
				}
			}
		} 
	}
}

void print(int **path){
	if(found==0){
		printf("不存在路徑！");
	}
	else{
		while(top>-1){
			printf("%d %d\n",path[top][0],path[top][1]);
			top--;	
		}

	}
}

	
//	for(int i=0;i<m+2;i++){
//		for(int j=0;j<n+2;j++){
//			printf("%d ",vis[i][j]);
//		}
//		printf("\n");
//	}
