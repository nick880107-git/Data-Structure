#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define MAXSTACK 100
using namespace std;

struct point{
	int x;
	int y;
	point *last;
};

int main(){
	int h,w;
	
	printf("請輸入迷宮大小：");
	scanf("%d %d",&h,&w);
	
	//初始化陣列 
	int **map = new int*[h+2];
	for(int i=0;i<h+2;i++){
		map[i]=new int[w+2];		
	}
	for(int i=0;i<w+2;i++){
		map[0][i]=1;
		map[h+1][i]=1;
	}
	for(int j=0;j<h+2;j++){
		map[j][0]=1;
		map[j][h+1]=1;
	}
	printf("請輸入迷宮資料：\n");
	for(int i=1;i<=h;i++){
		int j=1;
		char y;
		do{
			scanf("%d",&map[i][j]);
			j++;
		}while(y=getchar()!='\n');
	}

	queue<point*> q;
	point *start=new point;
	start->x=1;
	start->y=1;
	q.push(start);
	map[1][1]=1;
	point end;
	end.x=h;
	end.y=w;
	int dir[8][2]={{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}};
	int found=0; //表示找到路徑與否
	int top=-1,path[MAXSTACK][2]; 
	
	while(!q.empty()||found!=1){
		point *position=q.front(); //取得queue儲存的第一個位置
		q.pop();
		if(position->x==end.x&&position->y==end.y){
			found=1;
			do{
				top++;
				path[top][0]=position->x;
				path[top][1]=position->y;
				position=position->last;
			}while((position->x!=start->x)||(position->y!=start->y));
			top++;
			path[top][0]=position->x;
			path[top][1]=position->y;
		}
		else{
			for(int i=0;i<8;i++){
				point *temp=new point;
				temp->x=position->x+dir[i][0];
				temp->y=position->y+dir[i][1];
				if(map[temp->x][temp->y]==0){
					temp->last=position;
					q.push(temp);
					map[temp->x][temp->y]=map[position->x][position->y]+1;
				}
			}
		} 
	}
	if(found==0){
		printf("不存在路徑！");
	}
	else{
		while(top!=-1){
			printf("%d %d\n",path[top][0],path[top][1]);
			top--;
		}
	}
}

