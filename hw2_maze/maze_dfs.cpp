#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define MAXSTACK 400
#define MAXMAP 20 
using namespace std;

struct point{
	int row;
	int col;
	int dir;
};

int m,n;
int map[MAXMAP][MAXMAP], vis[MAXMAP][MAXMAP];
int top=-1;
int found=0;

int dir[8][2]={{1,1},{0,1},{1,0},{-1,1},{1,-1},{0,-1},{-1,0},{-1,-1}};
point start;
point target;
point path[MAXSTACK];

void dfs();
void print();
void push(point pt);
void pop();

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
	
	//列印迷宮 
	printf("\n迷宮長相：\n");
	for(int i=0;i<m+2;i++){
		for(int j=0;j<n+2;j++){
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	
	target.row=m;
	target.col=n;
	start.row=1;
	start.col=1;
	vis[start.row][start.col]=1;
	push(start);
	dfs();
	print();
}
void push(point pt){
	top++;
	path[top].row=pt.row;
	path[top].col=pt.col;
	path[top].dir=-1;

}
void pop(){
	top--;
}
void dfs(){
	if(top>-1){
	
		printf("當前位置：[%d,%d]，",path[top].row,path[top].col);
		if(path[top].row==target.row && path[top].col==target.col){
			found=1;
			printf("抵達終點\n");
		}
		else{
			if(path[top].dir<8){
				point temp;
				path[top].dir++;
				printf("top=%d,dir=%d      ",top,path[top].dir);
				temp.row=path[top].row+dir[path[top].dir][0];
				temp.col=path[top].col+dir[path[top].dir][1];
				printf("看向[%d,%d],map=%d,vis=%d，",temp.row,temp.col,map[temp.row][temp.col],vis[temp.row][temp.col]);
				if(map[temp.row][temp.col]==0 && vis[temp.row][temp.col]==0){
					push(temp);
					printf("前往%d,%d\n",temp.row,temp.col);
					vis[temp.row][temp.col]=1;
					
				}
				else{
					printf("不能通行\n");
				}				
			}
			else{
				pop();
				printf("退後\n");
			}
			dfs();		
		}

	}
}
void print(){
	for(int i=0;i<=top;i++){
			printf("%d %d\n",path[i].row,path[i].col);
		}
	
//	printf("\n");
//	if(found==0){
//		printf("不存在路徑！");
//	}
//
//	else{
//		for(int i=0;i<=top;i++){
//			printf("%d %d\n",path[i].row,path[i].col);
//		}
//	}
}
