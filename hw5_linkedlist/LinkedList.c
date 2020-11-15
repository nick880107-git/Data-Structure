#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int data;
	struct node* link;
}node, *Nodeptr;

void add(Nodeptr *start,int value);
void del(Nodeptr *start,int index);
void ins(Nodeptr *start,int value,int index);
void rev(Nodeptr *start);
void show(Nodeptr start);

int main(){
	Nodeptr ptr=NULL;	//宣告一個指向node型 別的指標(作head)，預設為空
	char command[10];
	int value=0;
	int index=0;
	char pos[10];	//用來判斷before/after，不過尚未實作 
	while(scanf("%s",command)!=EOF){
		if(strcmp(command,"ADD")==0){
			scanf("%d",&value);
			add(&ptr,value);
		}
		else if(strcmp(command,"INSERT")==0){
			scanf("%d",&value);
			scanf("%s",pos);
			scanf("%d",&index);
			ins(&ptr,value,index);
		}
		else if(strcmp(command,"DELETE")==0){
			scanf("%d",&index);
			del(&ptr,index);
		}
		else if(strcmp(command,"REVERSE")==0){
			rev(&ptr);
		}
		show(ptr);
	}
	 
}

void add(Nodeptr *start ,int value){	//輸入指向node指標的位址&新增的值 
	Nodeptr head= *start;	//設一head指向start所指向的node 
	Nodeptr temp=(node *)malloc(sizeof(node));
	temp->data=value;
	temp->link=NULL;
	
	if(*start==NULL){
		*start=temp;
		return;
	}
		
	while(head && head->link){
		head=head->link;
		if(head->link==NULL)
			break;
	}
	head->link=temp;
}
void del(Nodeptr *start,int index){
	if(*start){
		if(index==1){
			Nodeptr tempptr=*start;
			*start=(*start)->link;
			free(tempptr);
			return;
		}
		else{
			int count=1;
			Nodeptr curptr=*start;
			Nodeptr preptr=(*start)->link;
			while(curptr && count!=index){
				if(curptr->link){
					count++;
					preptr=curptr;
					curptr=curptr->link;
				}
				else
					break;
			}
			if(count==index){
				preptr->link=curptr->link;
				free(curptr);
				return;
			}	
		}
	}	
		
	printf("Index is out of range!!\n");
	
}

void ins(Nodeptr *start,int value,int index){
	Nodeptr temp=(node *)malloc(sizeof(node));
	temp->data=value;
	if(index==0){
		temp->link=*start;
		*start=temp;
		return;
	}
	else if(*start){
		int count=1;
		Nodeptr curptr=*start;
		while(curptr && count!=index){
			if(curptr->link){
				count++;
				curptr=curptr->link;
			}
			else
				break;
		}
		if(count==index){
			temp->link=curptr->link;
			curptr->link=temp;
			return;
		}	
	}	
	
	printf("Index is out of range!!\n");
}

void rev(Nodeptr *start){
	Nodeptr curptr,preptr,trial;
	curptr=*start;
	preptr=NULL;
	trial=curptr->link;
	if(*start==NULL || (*start)->link==NULL)	//只有一個node或完全沒有node 
		return;
	while(trial){
		curptr->link=preptr;
		preptr=curptr;
		curptr=trial;
		if(trial->link)
			trial=trial->link;
		else
			break;
	}
	curptr->link=preptr;
	*start=curptr;
}

void show(Nodeptr start){
	Nodeptr head=start;
	while(head){
		printf("%d ",head->data);
		head=head->link;
	}
	printf("\n");
}
