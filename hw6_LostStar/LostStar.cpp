#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXMAP 101
#define MAXSTACK 100

struct point{
	int row;
	int col;
};
int m,n;
int count=0;
char map[MAXMAP][MAXMAP];
int vis[MAXMAP][MAXMAP];
int top=-1;
int dir[8][2]={{1,1},{0,1},{1,0},{-1,1},{1,-1},{0,-1},{-1,0},{-1,-1}};

point path[MAXSTACK];

void dfs(int lost);
void search();
void push(point pt);
void pop();

void show();
void createMaze();

int main(){	
	scanf("%d %d",&m,&n);
	while(m!=0 && n!=0){
		
		//初始化陣列 
		for(int t=0;t<n+2;t++){
			map[0][t]='.';
			map[m+1][t]='.';
		} 
		for(int t=0;t<m+2;t++){
			map[t][0]='.';
			map[t][n+1]='.';
		}
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				scanf(" %c",&map[i][j]);
				vis[i][j]=0;
			}
		}

		
		search();
		scanf("%d %d",&m,&n);
	}
	
}

//int main(){		//自動生成測試 
//	createMaze();
//	for(int t=0;t<n+2;t++){
//		map[0][t]='.';
//		map[m+1][t]='.';
//	} 
//	for(int t=0;t<m+2;t++){
//		map[t][0]='.';
//		map[t][n+1]='.';
//	}
//	search();
//}

void push(point pt){
	top++;
	path[top].row=pt.row;
	path[top].col=pt.col;
}

void pop(){
	top--;
}

void search(){
	int i,j;
	count=0;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			if(map[i][j]=='*' && vis[i][j]==0){
				point pt;
				pt.row=i;
				pt.col=j;
				push(pt);
				vis[i][j]=1;
				dfs(0);
			}				
		}
	}
	printf("%d\n",count);
}

void dfs(int lost){
	int pos=0;
	int isLost=lost;
	int index=top;	//防止遞迴pop到自己之前的point 
	point temp;
	while(top>-1 && top>=index){		
		while(pos<8){
			temp.row=path[top].row+dir[pos][0];
			temp.col=path[top].col+dir[pos][1];
			if(map[temp.row][temp.col]=='*' && vis[temp.row][temp.col]==0){
					push(temp);					
					vis[temp.row][temp.col]=1;
					dfs(1);	
					isLost=1;				
			}
			pos++;
		}
		pop();
	}
	if(isLost==0)
		count+=1;
}

void show(){					//檢查迷宮長相用 
	printf("%d %d\n",m,n);
	for(int i=0;i<=m+1;i++){
		for(int j=0;j<=n+1;j++){
			printf("%c",map[i][j]);
		}
		printf("\n");
	}
}

void createMaze(){
	srand(time(NULL));
	m=(rand()%20)+1;
	n=(rand()%20)+1;
	int value=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			value=rand()%2;
			if(value==1)
				map[i][j]='.';
			else
				map[i][j]='*';
				vis[i][j]=0;
		}
	}
	show();

}
