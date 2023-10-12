#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
    int weight;
    struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;


void printGraphMatrix(Graph);
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph);

void generateRandomMatrix(Graph);

void dijsktraArrayMatrix(Graph g);
void SortPriorityQueue(int *, int *, int);
void removeAdjacentV(int, int*, int*, int);
void insertNewV(int vertex_v, int v_distance, int*, int*, int queue_size);

void dijsktraListMinHeap(Graph g);

int main(void){
    
    srand(time(NULL));
    
    
    Graph g;
    
    //Asking for the number of Vertex and Edges
    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);
    do{
        printf("Enter the number of edges:\n");
        scanf("%d",&g.E);
        
        if (g.E < g.V){
            printf("Invalid number of edges (Number of Edges need to be >= Number of Vertices)\n");
        }
        else if (g.E > ( g.V * (g.V - 1) )){
            printf("Invalid number of edges (Too many edges):\n");
        }
        
    }while (g.E < g.V || g.E > ( g.V * (g.V - 1) ));
    
    //Initalizing Graph Matrix, g.adj.matrix
    //Initalize Matrix Columns
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    //Initalize Matrix Rows
    for(int i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    
    generateRandomMatrix(g);
    
    printf("\nConverting Matrix into List\n\n");
    adjM2adjL(&g);
    printf("The equivalent list is:\n");
    printGraphList(g);

    printf("\nConverting List back into Matrix\n\n");
    adjL2adjM(&g);
    printGraphMatrix(g);
    
    //////////////////////////////
    ///TESTING MATRIX
    Graph test_graph;
    test_graph.V = 5;
    //Initalizing Graph Matrix, g.adj.matrix
    //Initalize Matrix Columns
    test_graph.adj.matrix = (int **)malloc(test_graph.V*sizeof(int *));
    //Initalize Matrix Rows
    for(int i=0;i<test_graph.V;i++)
        test_graph.adj.matrix[i] = (int *)malloc(test_graph.V*sizeof(int));
    test_graph.adj.matrix[0][1] = 5;
    test_graph.adj.matrix[0][2] = 10;
    test_graph.adj.matrix[2][3] = 1;
    test_graph.adj.matrix[2][1] = 2;
    test_graph.adj.matrix[1][2] = 3;
    test_graph.adj.matrix[1][3] = 9;
    test_graph.adj.matrix[1][4] = 2;
    test_graph.adj.matrix[4][3] = 6;
    test_graph.adj.matrix[3][4] = 4;
    test_graph.adj.matrix[4][0] = 7;
    
    printf("TEST Matrix is:\n");
    printGraphMatrix(test_graph);
    
    dijsktraArrayMatrix(test_graph);
    
    
    
    return 0;
}

void dijsktraArrayMatrix(Graph g){
    
    //Put these into the graph later
    int d[g.V];
    int pi[g.V];
    int S[g.V];
    
    for (int i=0; i<g.V; i++){
        d[i] = 9999999;
        pi[i] = -1; //Since we using vertex as int, we set to -1 to represent NULL/no predessor
        S[i] = 0;
    }
    
    int source = 0; //we assume source to be the first vertex 0
    d[source] = 0;

    int priorityqueue_VertexSorted[g.V];
    int priorityqueue_DistanceSorted[g.V];
    
    //Inserting all the Vertex and Distance into the PriorityQueue
    int queue_size = g.V; //Starts from g.V to add in all the Vertices
    for (int i=0; i<g.V; i++){
        priorityqueue_VertexSorted[i] = i; //Each vertex 0,1,2, ... etc.
        priorityqueue_DistanceSorted[i] = d[i]; //Duplicate of distance array d[i]
    }
    
    //Sorting Not Needed tbh
    SortPriorityQueue(priorityqueue_VertexSorted, priorityqueue_DistanceSorted, queue_size);

    while (queue_size > 0){

        int vertex_u = priorityqueue_VertexSorted[0]; //Extract Cheapest is the first index as it is sorted by distance already
        
        removeAdjacentV(vertex_u, priorityqueue_VertexSorted, priorityqueue_DistanceSorted, queue_size);
        S[vertex_u] = 1;
        queue_size--;
        
        for (int adj_vertex_v = 0; adj_vertex_v<g.V; adj_vertex_v++){
            if (adj_vertex_v != vertex_u && g.adj.matrix[vertex_u][adj_vertex_v] != 0){ //Ignore itself, we do not include self-loops && ignore missing edges

                if (S[adj_vertex_v] != 1 && d[adj_vertex_v] > d[vertex_u] + g.adj.matrix[vertex_u][adj_vertex_v]){
                    //Not Visited && Current Distance > New Distance
                    
                    printf("adj_vertex_v is %d\n", adj_vertex_v);
                    printf("\n");
                    
                    removeAdjacentV(adj_vertex_v, priorityqueue_VertexSorted, priorityqueue_DistanceSorted, queue_size);
                    queue_size--;

                    d[adj_vertex_v] = d[vertex_u] + g.adj.matrix[vertex_u][adj_vertex_v];
                    pi[adj_vertex_v] = vertex_u;
                    /*
                    printf("adj_vertex_v after REMOVING %d\n", adj_vertex_v);
                    printf("Priority vertex queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_VertexSorted[i]);
                    }
                    printf("\n");
                    printf("Priority distance queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_DistanceSorted[i]);
                    }
                    printf("\n");
                    printf("\n");
                    */
                    insertNewV(adj_vertex_v, d[adj_vertex_v], priorityqueue_VertexSorted, priorityqueue_DistanceSorted, queue_size);
                    queue_size++;
                    /*
                    printf("adj_vertex_v after INSERTING %d\n", adj_vertex_v);
                    printf("Priority vertex queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_VertexSorted[i]);
                    }
                    printf("\n");
                    printf("Priority distance queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_DistanceSorted[i]);
                    }
                    printf("\n");
                    printf("\n");
                    
                    printf("Priority vertex queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_VertexSorted[i]);
                    }
                    printf("\n");
                    printf("Priority distance queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_DistanceSorted[i]);
                    }
                    printf("\n");
                    printf("\n");
                    */
                    SortPriorityQueue(priorityqueue_VertexSorted, priorityqueue_DistanceSorted, queue_size);
                    /*
                    printf("adj_vertex_v after SORTING %d\n", adj_vertex_v);
                    printf("Priority vertex queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_VertexSorted[i]);
                    }
                    printf("\n");
                    printf("Priority distance queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_DistanceSorted[i]);
                    }
                    printf("\n");
                    printf("\n");
                    
                    printf("Priority vertex queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_VertexSorted[i]);
                    }
                    printf("\n");
                    printf("Priority distance queue is:\n");
                    for (int i=0; i<queue_size; i++){
                        printf("%d ", priorityqueue_DistanceSorted[i]);
                    }
                    printf("\n");
                    printf("\n");
                    */
                    
                    
                }
            }
        }
    }
    
    printf("\n");
    printf("Distance Array:");
    for (int i=0; i<g.V; i++){
        printf("%d\t", d[i]);
    }
    
    printf("\n");
    printf("pi Array:");
    for (int i=0; i<g.V; i++){
        printf("%d\t", pi[i]);
    }
    printf("\n");
    
    printf("S Array:");
    for (int i=0; i<g.V; i++){
        printf("%d\t", S[i]);
    }
    printf("\n");
}

void SortPriorityQueue(int *priorityqueue_VertexSorted, int *priorityqueue_DistanceSorted, int QueueSize){
    //Sorting by distance, swap both Vertex and Distance
    
    //Using insertion sort although not the most efficient
    for (int i=1; i<QueueSize; i++){
        for (int j=i; j>0; j--){
            if (priorityqueue_DistanceSorted[j] < priorityqueue_DistanceSorted[j-1]){
                //Swap operation
                int temp_vertex = priorityqueue_VertexSorted[j];
                int temp_distance = priorityqueue_DistanceSorted[j];
                
                priorityqueue_VertexSorted[j] = priorityqueue_VertexSorted[j-1];
                priorityqueue_DistanceSorted[j] = priorityqueue_DistanceSorted[j-1];
                
                priorityqueue_VertexSorted[j-1] = temp_vertex;
                priorityqueue_DistanceSorted[j-1] = temp_distance;
            }
        }
        
    }
}

void removeAdjacentV(int remove_vertex, int *priorityqueue_VertexSorted, int *priorityqueue_DistanceSorted, int QueueSize){
    
    int remove_index = 9999999;
    
    for (int i=0; i<QueueSize; i++){
        if (priorityqueue_VertexSorted[i] == remove_vertex){
            remove_index = i;
        }
    }
    
    if(remove_index == 9999999){
        printf("Unable to find remove_index.");
        return;
    }
    
    //Removing the vertex
    priorityqueue_VertexSorted[remove_index] = -66666;
    priorityqueue_DistanceSorted[remove_index] = -66666;
    
    //Shifting everything to fill in the space of the removed vertex
    for (int i=remove_index; i<QueueSize-1; i++){
        priorityqueue_VertexSorted[i] = priorityqueue_VertexSorted[i+1];
        priorityqueue_DistanceSorted[i] = priorityqueue_DistanceSorted[i+1];
    }
    
    return;
}

void insertNewV(int vertex_v, int v_distance, int *priorityqueue_VertexSorted, int *priorityqueue_DistanceSorted, int queue_size){
    
    priorityqueue_VertexSorted[queue_size] = vertex_v;
    priorityqueue_DistanceSorted[queue_size] = v_distance;
      
}

void generateRandomMatrix(Graph g){
    
    //Creating an Empty Matrix
    for(int i=0;i<g.V;i++){
        for(int j=0;j<g.V;j++){
            g.adj.matrix[i][j] = 0;
        }
    }
    
    //Creating a random matrix
    int remaining_edges = g.E;
    int random_vertex_row;
    int random_vertex_column;
    
    int upper = 10; //upper weight limit
    int lower = 1; // lower weight limit
    
    //Making sure each vertex has at least 1 edge
    for (int i=0; i<g.V; i++){
        
        random_vertex_column = (rand() % (g.V));
        
        while (i == random_vertex_column){ //Making sure that we do not self loop
            random_vertex_column = (rand() % (g.V));
        }
        
        if (random_vertex_column != i){
            g.adj.matrix[i][random_vertex_column] = (rand() % (upper - lower + 1)) + lower;
            remaining_edges--;
        }

        
    }
    
    //Doing the remaining_edges
    while(remaining_edges > 0){
        
        random_vertex_row = (rand() % (g.V));
        random_vertex_column = (rand() % (g.V));
        
        if (random_vertex_row != random_vertex_column && g.adj.matrix[random_vertex_row][random_vertex_column] == 0){     //Making sure that there are no self-loops
            g.adj.matrix[random_vertex_row][random_vertex_column] = (rand() % (upper - lower + 1)) + lower;
            remaining_edges--;
        }
    }
}

void adjM2adjL(Graph *g)
{
    
    if (g->type == ADJ_LIST) {printf("Error. Already in list format.\n");return; }
    if (g->V <= 0) {printf("Empty Graph.\n"); return;}
    
    
    ListNode **list;
    list = (ListNode **)malloc(sizeof(ListNode*) * g->V);
    
    for (int index=0; index<g->V; index++){
        list[index] = NULL;
    }
    
    ListNode *temp_node = NULL;
    
    for (int i=0; i<g->V; i++){
        for (int j=0; j<g->V; j++){
            if (g->adj.matrix[i][j] != 0){
                
                if (list[i] == NULL){
                    list[i] = (ListNode*) malloc(sizeof(ListNode));
                    list[i]->vertex = j; //or +1 to account for index
                    list[i]->weight = g->adj.matrix[i][j];
                    list[i]->next = NULL;
                    temp_node = list[i];
                }
                
                else{
                    temp_node->next = (ListNode*)malloc(sizeof(ListNode));
                    temp_node->next->vertex = j; //or + 1 to account for index
                    temp_node->next->weight = g->adj.matrix[i][j];
                    temp_node->next->next = NULL;
                    temp_node = temp_node->next;
                    
                }
            }
            
        }
    }
    
    g->adj.list = list;

}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("v: %d (w: %d) -> ", temp->vertex,temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}



//List to Matrix Probably dunnid
void adjL2adjM(Graph *g){
    if (g->type == ADJ_MATRIX){
        printf("Error. Graph is already in matrix form.\n");
        return;
    }
    if (g->V <= 0){
        printf("Empty Graph.\n");
        return;
    }
    
    int **mat;
    mat = (int**)malloc(sizeof(int*) * g->V); //Allocate memory for the rows
    for (int i=0; i<g->V; i++){
        mat[i] = (int*)malloc(sizeof(int) *g->V); //Allocate memory of the columns
    }
    
    //Initalizing all the values of the matrix to 0
    for (int i=0; i<g->V; i++){
        for (int j=0; j<g->V; j++){
            mat[i][j] = 0;
        }
    }
    
    ListNode *temp_node = NULL;
    int i;
    
    for (i=0; i<g->V; i++){
        temp_node = g->adj.list[i];
        while (temp_node!=NULL){
            mat[i][temp_node->vertex] = temp_node->weight;
            temp_node = temp_node->next;
        }
    }
    
    g->type = ADJ_MATRIX;
    
    for (i=0; i<g->V; i++){
        free(g->adj.list[i]);
    }
    free(g->adj.list);
    
    
    g->adj.matrix = mat;
    
}
