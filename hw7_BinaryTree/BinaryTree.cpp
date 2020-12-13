#include <stdlib.h>
#include <stdio.h>

typedef struct node node_t;

struct node{
	int data;
	node_t *left;
	node_t *right;
};
void Traversal(node_t* ptr);
 
node_t* MakeNode(int data);
node_t* HasNode(node_t *ptr, int data);
int GetHeight(node_t* ptr);
void GetLeaf(node_t* ptr);

node_t* tree;
int leaf=0;
int height=0;
int main(){
	int v,l,r;
	int state=0;
	while(scanf("%d %d %d",&v,&l,&r)!=EOF){
		if(!tree){
			tree=MakeNode(v);
			tree->left=MakeNode(l);
			tree->right=MakeNode(r);
			state=1;
		}
		else{
			node_t* parent=HasNode(tree,v);
			if(parent){
				parent->left=MakeNode(l);
				parent->right=MakeNode(r);
			}
			else
				state=-1;
		}
	}
	if(state==0)
		printf("Tree is empty");
	if(state==-1)
		printf("Invalid tree");
	if(state==1){
		height=GetHeight(tree);
		GetLeaf(tree);
		printf("%d\n",height);
		printf("%d\n",leaf);
	}

}

node_t* MakeNode(int data){
	if(data!=0){
		node_t *newnode=(node_t*)malloc(sizeof(node_t));
		newnode->data=data;
		newnode->left=NULL;
		newnode->right=NULL;
		return newnode;
	}
	else
		return NULL;
	
}

node_t* HasNode(node_t *ptr, int data){
	node_t* temp=NULL;
	if(ptr){
		if(ptr->data==data){
			temp=ptr;
		}
		else{
			node_t* l=HasNode(ptr->left,data);
			node_t* r=HasNode(ptr->right,data);
			if(l)
				temp=l;
			if(r)
				temp=r;
		}
	}
	
	return temp;
		
}

void Traversal(node_t* ptr){
	int l,r,v;
	l=r=v=0;
	if(ptr)
		v=ptr->data;
	if(ptr->left)
		l=ptr->left->data;
	if(ptr->right)
		r=ptr->right->data;	
	printf("%d %d %d\n",v,l,r);
	if(ptr->left)
		Traversal(ptr->left);
	if(ptr->right)
		Traversal(ptr->right);
		
}


int GetHeight(node_t* ptr){	//比較左右子樹高度，取最大者+1 
	int height=0;
	int l_height,r_height;
	if(ptr){
		l_height=GetHeight(ptr->left);
		r_height=GetHeight(ptr->right);
		height = l_height>r_height ? l_height:r_height;
		return height+1;
	}
	else
		return height;
}
void GetLeaf(node_t* ptr){
	if(ptr->left)
		GetLeaf(ptr->left);
	if(ptr->right)
		GetLeaf(ptr->right);
	if(!(ptr->left)&& !(ptr->right)){
		leaf=leaf+1;
	}
}
