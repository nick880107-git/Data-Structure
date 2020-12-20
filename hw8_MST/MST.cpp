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
	
	// 存放所有MST結果的陣列 
	int *result = NULL;
	result = (int*)malloc(sizeof(int)*dataset);
	
	while(times<dataset){
		int e;	//e=edges
		scanf("%d %d",&V,&e);
		
		// 配置動態陣列存取graph 
		int **graph =NULL;
		graph = (int**)malloc(sizeof(int*)*V);
		for(int i=0;i<V;i++){
			graph[i] = (int*)malloc(sizeof(int)*V);
		}
		// 初始化graph的值為INT_MAX(視為各點距離無窮大) 
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
  				graph[i][j]=INT_MAX;
		   }
	  	}
		
		// 讀取graph資料 
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
    
    int *parent;	//紀錄其來源地(父) 
    int *key; 		//紀錄「到達此節點的最低cost」 
    bool *mstSet; 	//紀錄「是否走過此節點」 
    parent = (int*)malloc(sizeof(int)*V);
    key = (int*)malloc(sizeof(int)*V);
    mstSet = (bool*)malloc(sizeof(bool)*V);
  
    // 初始化key,mstSet  
    for (int i = 0; i < V; i++){
    	key[i] = INT_MAX, mstSet[i] = false;
    	parent[i] = -1;
	}
    
    // 從第0個節點出發，因此key[0] = 0, 又因節點0是出發點，故沒有來源地 
    key[0] = 0; 
    parent[0] = -1; 
  	
  	
    for (int count = 0; count < V-1; count++) { 
		int u = minKey(key, mstSet); 	// 從key挑一個最小的 & 還沒拜訪過的  
        mstSet[u] = true; 				// 設為已拜訪 
  
        // 更新周遭有連結的vertices的key值及其parent 
        for (int v = 0; v < V; v++) 
            if (mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 

//		//觀察變數變化情形 
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
