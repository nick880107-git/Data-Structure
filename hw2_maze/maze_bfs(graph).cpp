#include <cstdio>
#include <iostream>
#include <queue>
#define MAXSTACK 400
#define MAXMAP 20 
using namespace std;

struct point{
	int row;
	int col;
	point *last;
};

int m,n;
int map[MAXMAP][MAXMAP], vis[MAXMAP][MAXMAP];
int top=-1,path[MAXSTACK][2];
int found=0;
queue <point*> q;
int dir[8][2]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
point *start=new point;
point target;


void bfs();
void print();


int main(){
	
	printf("請輸入迷宮大小：");
	scanf("%d %d",&m,&n);
	
	//初始化陣列 
	for(int t=0;t<n+2;t++){
		map[0][t]=1;
		map[m+1][t]=1;
	} 
	for(int t=0;t<m+2;t++){
		map[t][0]=1;
		map[t][n+1]=1;
	}
	
	printf("請輸入迷宮資料：\n");
	for(int i=1;i<=m;i++){
		int j=1;
		char y;
		do{
			scanf("%d",&map[i][j]);
			j++;
		}while(y=getchar()!='\n');
	}
	target.row=m;
	target.col=n;
	start->row=1;
	start->col=1;
	vis[start->row][start->col]=1;
	q.push(start);
	bfs();
	print();
}
void bfs(){
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
				if(map[row][col]==0 && vis[row][col]==0){
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

void print(){
	if(found==0){
		printf("不存在路徑！");
	}
	else if(top>-1){
		printf("%d %d\n",path[top][0],path[top][1]);
		top--;
		print();
	}
	else{
		return;
	}
}
