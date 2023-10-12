#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _listnode
{
    int source;
    int vertex;
    int weight;
    struct _listnode *next;
} ListNode;

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation
union GraphForm{
    int **matrix;

    ListNode **list;
};


typedef struct _graph{
    int V;
    int E;
    int *S; //Keep track of the vertex that has already found shortest path
    int *d; //Shortest distance from source vertex to all other vertex
    int*pi; //Predecessor
    enum GraphType type;
    union GraphForm adj;
    ListNode **list;
}Graph;


void printGraphMatrix(Graph);
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph);

void generateRandomMatrix(Graph);

//part a
void dijsktraArrayMatrix(Graph g);
void SortPriorityQueue(int *, int *, int);
void removeAdjacentV(int, int*, int*, int);
void insertNewV(int vertex_v, int v_distance, int*, int*, int queue_size);

//part b
void dik(Graph G, int source);
void swap(int *a, int *b);
void heapify(int array[], int size, int i);
void insert(int array[], int w, int v);
int deleteRoot(int array[], int num);
void printArray(int array[], int size);
int size=0, *priorityV, *priorityW;

int main()
{
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

    //Initalizing for Part b
    g.d = (int *) malloc(sizeof(int)*g.V);
    g.S = (int *) malloc(sizeof(int)*g.V);
    g.pi = (int *) malloc(sizeof(int)*g.V);
    priorityV = (int *) malloc(sizeof(int)*g.V);
    priorityW = (int *) malloc(sizeof(int)*g.V);
     for(int i=0;i<g.V;i++){
        g.S[i] = 0;
        priorityW[i]=0;
        priorityV[i]=0;
        g.d[i] = 0;
        g.pi[i] = 0;
      }
    
    generateRandomMatrix(g);
    printGraphMatrix(g);
    
    dijsktraArrayMatrix(g); //Part A
    printf("\nConverting Matrix into List\n\n");
    adjM2adjL(&g);
    printf("The equivalent list is:\n");
    printGraphList(g);
    dik(g, 1); //Part B
    

    
    /*
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
    
    test_graph.d = (int *) malloc(sizeof(int)*test_graph.V);
    test_graph.S = (int *) malloc(sizeof(int)*test_graph.V);
    test_graph.pi = (int *) malloc(sizeof(int)*test_graph.V);
    priorityV = (int *) malloc(sizeof(int)*test_graph.V);
    priorityW = (int *) malloc(sizeof(int)*test_graph.V);
    for(int i=0;i<test_graph.V;i++){
        test_graph.S[i] = 0;
        priorityW[i]=0;
        priorityV[i]=0;
        test_graph.d[i] = 0;
        test_graph.pi[i] = 0;
        }
    
    printf("TEST Matrix is:\n");
    printGraphMatrix(test_graph);
    
    dijsktraArrayMatrix(test_graph); //Part A

    printf("\nConverting Matrix into List\n\n");
    adjM2adjL(&test_graph);
    printf("The equivalent list is:\n");
    printGraphList(test_graph);
    
    dik(test_graph, 1); //Part B
    
    
    */
    return 0;
}
void swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}
void heapify(int array[], int size, int i)
{
  if (size == 1)
  {
    printf("Single element in the heap\n");
  }
  else
  {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] < array[smallest])
      smallest = l;
    if (r < size && array[r] < array[smallest])
      smallest = r;
    if (smallest != i)
    {
      swap(&array[i], &array[smallest]);
      swap(&priorityV[i], &priorityV[smallest]);
      heapify(array, size, smallest);
    }
  }
}
void insert(int array[],int w, int v)
{
  if (size == 0)
  {
    array[0] = w;
    priorityV[0]= v;
    printf("inserted source %d with weight %d\n",priorityV[size],priorityW[size]);
    size++;
  }
  else
  {
    array[size] = w;
    priorityV[size]= v;
    printf("inserted source %d with weight %d\n",priorityV[size],priorityW[size]);
    size ++;
     for (int i = size / 2 - 1; i >= 0; i--)
    {
      heapify(array, size, i);
    }
  }
  printArray(array,size);
}
int deleteRoot(int array[], int num)
{
  int i=0,value=0;
  heapify(priorityW, size, 0);
  if(num==-1){ //to obtain smallest value in priority queue
    i=0;
  }
  else{
    for (i = 0; i < size; i++)
    {
        if (num == array[i])
        break;
    }
  }


  value=priorityV[i];
  array[i]=0;
  priorityW[i]=0;
  swap(&array[i], &array[size - 1]);
  swap(&priorityW[i], &priorityW[size - 1]);
  size --;
  for (int i = size / 2 - 1; i >= 0; i--){
    heapify(priorityW, size, i);
   }
   printf("deleted %d\n",value);
  return value;
}
void printArray(int array[], int size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", array[i]);
  printf("\n");
}

void dik(Graph G, int source){

    int d[G.V], pi[G.V],S[G.V],i=0,u, v=0;
    source--;

    for(i=0;i<G.V;i++){
        d[i]=10000; //assign infinity
        pi[i]=-1; // assign null
        S[i]=-1;
        priorityV[i]=0;// initialise priority
        priorityW[i]=0;
    }
    d[source]=0;
    clock_t start, end; //added time func
    double cpu_time_used;
    start = clock();
    //priority[0]=source; // queue source node
    for(i=0;i<G.V;i++){
        insert(priorityW, d[i],i);//add vertices to priority queue
    }
    while(size!=0){
        u=deleteRoot(priorityV,-1);// extractcheapest
        S[u] = 1;

        struct _listnode *temp=G.list[u];
        while(temp!=NULL){
            v=temp->vertex;
            if(S[temp->vertex]==-1 && d[v]>(d[u]+temp->weight)){
                deleteRoot(priorityV,v);
                d[v]=d[u]+ temp->weight;
                pi[v]= u;
                insert(priorityW,d[v],v);
            }
            temp=temp->next;
            printf("d:\n");
            printArray(d,G.V);
            printf("pi:\n");
            printArray(pi,G.V);
            printf("s:\n");
            printArray(S,G.V);
            printf("pW:\n");
            printArray(priorityW,size);
            printf("pV:\n");
            printArray(priorityV,size);

        }
    }
            
            printf("d:\n");
            printArray(d,G.V);
            printf("pi:\n");
            printArray(pi,G.V);
            printf("s:\n");
            printArray(S,G.V);
            printf("pW:\n");
            printArray(priorityW,size);
            printf("pV:\n");
            printArray(priorityV,size);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time: %f\n",cpu_time_used);


    return;
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
    
    g->list = (ListNode **) malloc(g->V*sizeof(ListNode *));
    
    for (int i=0; i<g->V; i++){
        for (int j=0; j<g->V; j++){
            if (g->adj.matrix[i][j] != 0){
                
                if (g->list[i] == NULL){
                    g->list[i] = (ListNode*) malloc(sizeof(ListNode));
                    g->list[i]->vertex = j; //or +1 to account for index
                    g->list[i]->weight = g->adj.matrix[i][j];
                    g->list[i]->next = NULL;
                    temp_node = g->list[i];
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
