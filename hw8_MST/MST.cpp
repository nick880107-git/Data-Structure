 #include <limits.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h>


int minKey(int key[], bool mstSet[]); 
int primMST(int **graph); 
int V;
int main() 
{ 
	int dataset,times=0;
	scanf("%d",&dataset);
	
	// �s��Ҧ�MST���G���}�C 
	int *result = NULL;
	result = (int*)malloc(sizeof(int)*dataset);
	
	while(times<dataset){
		int e;	//e=edges
		scanf("%d %d",&V,&e);
		
		// �t�m�ʺA�}�C�s��graph 
		int **graph =NULL;
		graph = (int**)malloc(sizeof(int*)*V);
		for(int i=0;i<V;i++){
			graph[i] = (int*)malloc(sizeof(int)*V);
		}
		// ��l��graph���Ȭ�INT_MAX(�����U�I�Z���L�a�j) 
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
  				graph[i][j]=INT_MAX;
		   }
	  	}
		
		// Ū��graph��� 
		int u,v,w;
		
		for(int t=0;t<e;t++){
			scanf("%d %d %d",&u,&v,&w);
			graph[u][v]=w;
			graph[v][u]=w;
		}
		result[times] = primMST(graph);
		times++;
	}
	for(int i=0;i<times;i++){
		printf("%d\n",result[i]);
	}

} 

int minKey(int key[], bool mstSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
  
    return min_index; 
} 
  


int primMST(int **graph) 
{ 
    
    int *parent;	//������ӷ��a(��) 
    int *key; 		//�����u��F���`�I���̧Ccost�v 
    bool *mstSet; 	//�����u�O�_���L���`�I�v 
    parent = (int*)malloc(sizeof(int)*V);
    key = (int*)malloc(sizeof(int)*V);
    mstSet = (bool*)malloc(sizeof(bool)*V);
  
    // ��l��key,mstSet  
    for (int i = 0; i < V; i++){
    	key[i] = INT_MAX, mstSet[i] = false;
    	parent[i] = -1;
	}
    
    // �q��0�Ӹ`�I�X�o�A�]��key[0] = 0, �S�]�`�I0�O�X�o�I�A�G�S���ӷ��a 
    key[0] = 0; 
    parent[0] = -1; 
  	
  	
    for (int count = 0; count < V-1; count++) { 
		int u = minKey(key, mstSet); 	// �qkey�D�@�ӳ̤p�� & �٨S���X�L��  
        mstSet[u] = true; 				// �]���w���X 
  
        // ��s�P�D���s����vertices��key�ȤΨ�parent 
        for (int v = 0; v < V; v++) 
            if (mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 

//		//�[���ܼ��ܤƱ��� 
//        printf("i\tparent\tkey\tmstSet\n");
//  		for(int i=0;i<V;i++){
//			printf("%d\t%d\t%d\t%d\n",i,parent[i],key[i],mstSet[i]);
//		}
    } 
    int cost = 0; 
//    for(int i=0;i<V;i++){
//		for(int j=0;j<V;j++){
//  			printf("%d ",graph[i][j]);
//	   }
//	   printf("\n");
//	}
    for (int i = 1; i < V; i++) 
        cost += graph[i][parent[i]];
	return cost;  
} 
