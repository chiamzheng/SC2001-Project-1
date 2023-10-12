#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator
enum GraphType {ADJ_MATRIX, ADJ_LIST};
typedef struct _listnode
{
    int source;
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
    int *S; //Keep track of the vertex that has already found shortest path
    int *d; //Shortest distance from source vertex to all other vertex
    int*pi; //Predecessor
    enum GraphType type;
    union GraphForm adj;
    ListNode **list;
}Graph;

void swap(int *a, int *b);
void heapify(int array[], int size, int i);
void insert(int array[], int w, int v);
int deleteRoot(int array[], int num);
void printArray(int array[], int size);
int size=0, *priorityV, *priorityW;
int main()
{
    Graph g;
    ListNode *temp;
    struct _listnode *testing;
    int choice = 0, V1, V2, W,i=0;

    g.V = 0; //Number of vertices in a graph
    g.E = 0; //Number of edges in a graph

    while(choice >= 0 && choice <= 5)
    {
        printf("1. Manual Input\n");
        printf("2. Random Generator\n");
        printf("3. Print Adjacency List\n");
        printf("4. Insert into priority list\n");
        printf("5. Enter number of vertices\n");
        printf("6. Exit Program\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                //Before creating a new graph, free up the spaces if there exist a graph
                for(int i=0; i<g.V; i++)
                {
                    ListNode *current = g.list[i];
                    while (current != NULL)
                    {
                        ListNode *temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                if(g.V != 0)
                {
                    free(g.list);
                    free(g.S);
                    free(g.d);
                    free(g.pi);
                    free(priorityV);
                    free(priorityW);
                }

                printf("Enter the number of vertices:\n");
                scanf("%d", &g.V); //Number of vertices in a graph
                g.d = (int *) malloc(sizeof(int)*g.V);
                g.S = (int *) malloc(sizeof(int)*g.V);
                g.pi = (int *) malloc(sizeof(int)*g.V);
                priorityV = (int *) malloc(sizeof(int)*g.V);
                priorityW = (int *) malloc(sizeof(int)*g.V);
                g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));//Set null to all list node
                for(int i=0;i<g.V;i++){
                    g.S[i] = 0;
                    priorityW[i]=0;
                    priorityV[i]=0;
                    g.d[i] = 0;
                    g.pi[i] = 0;
                    g.list[i] = NULL;
                }


                printf("Enter two vertices in which V1 is adjacent to V2 and the weights:\n"); //V1 -> V2
                while(scanf("%d %d %d",&V1,&V2, &W) == 3)
                {
                    if(V1>-1 && V1<g.V && V2>-1 && V2<g.V)
                    {
                        if(g.list[V1] == NULL)
                        {
                            g.list[V1] = (ListNode *)malloc(sizeof(ListNode));
                            g.list[V1]->source= V1;
                            g.list[V1]->vertex = V2;
                            g.list[V1]->weight = W;
                            g.list[V1]->next = NULL;
                            temp = g.list[V1];
                            g.E++;
                        }
                        else
                        {
                           temp->next = (ListNode *)malloc(sizeof(ListNode));
                           temp->next->source = V1;
                           temp->next->vertex = V2;
                           temp->next->weight = W;
                           temp->next->next = NULL;
                           temp = temp->next;
                           g.E++;
                        }
                    }
                    else
                        break;
                    printf("Enter two vertices in which V1 is adjacent to V2 and the weights:\n");
                }
                scanf("%*c"); //Termination
                break;
            case 2:

                //Before creating a new graph, free up the spaces if there exist a graph
                for(int i=0; i<g.V; i++)
                {
                    ListNode *current = g.list[i];
                    while (current != NULL)
                    {
                        ListNode *temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                if(g.V != 0)
                {
                    free(g.list);
                    free(g.S);
                    free(g.d);
                    free(g.pi);
                    free(priorityV);
                    free(priorityW);
                }

                srand(time(0));
                g.V = (rand() % (15 - 5 + 1)) + 5; //Upper bound = 15, Lower bound = 5
                printf("Number of vertices created: %d\n", g.V);
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

                g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
                for(int i=0;i<g.V;i++) //Set a base such that all vertices has at least an edge
                {
                    g.list[i] = (ListNode *)malloc(sizeof(ListNode));
                    do
                    {

                        g.list[i]->vertex = (rand() % (g.V - 1 + 1)) + 1; //Upper bound = num of vertex, Lower bound = first vertex

                    }while(i == g.list[i]->vertex); //To prevent e.g. if first vertex connected to first vertex
                    g.list[i]->source = i+1;
                    g.list[i]->weight = (rand() % (10 - 1 + 1)) + 1;
                    g.list[i]->next = NULL;
                    g.E++;
                }

                for(int i=0; i<(rand() % (g.V - 1 + 1)) + 1; i++) //Add at least one more edge to the graph, capped at g.V times
                {
                    V1 =  (rand() % (g.V - 1 + 1)) + 1; //Range from 1 to g.V
                    temp = g.list[V1 - 1];
                    while(temp->next != NULL)
                        temp = temp->next;
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    do
                    {
                        temp->next->vertex = (rand() % (g.V - 1 + 1)) + 1; //Upper bound = num of vertex, Lower bound = first vertex
                    }while(V1 == temp->next->vertex); //To prevent e.g. if first vertex connected to first vertex
                    temp->next->source= V1;
                    temp->next->weight = (rand() % (10 - 1 + 1)) + 1;
                    temp->next->next = NULL;
                    g.E++;
                }
                break;
            case 3:
                if(g.V <= 0)
                {
                    printf("No graph is form yet! Please form a graph!\n");
                    break;
                }

                for(int i=0;i<g.V;i++)
                {
                    temp = g.list[i];
                    printf("%d:\t",i+1);
                    temp = g.list[i];
                    while(temp!=NULL)
                    {
                        printf("V: %d, W: %d -> ",temp->vertex, temp->weight);
                        temp = temp->next;
                    }
                    printf("\n");
                }
                break;
            case 4:
                dik(g,1);

                break;
            case 5:
                //Before creating a new graph, free up the spaces if there exist a graph
                for(int i=0; i<g.V; i++)
                {
                    ListNode *current = g.list[i];
                    while (current != NULL)
                    {
                        ListNode *temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                if(g.V != 0)
                {
                    free(g.list);
                    free(g.S);
                    free(g.d);
                    free(g.pi);
                    free(priorityV);
                    free(priorityW);
                }
                printf("Enter the number of vertices: ");
                int ver_count, max_edge;
                scanf("%d", &ver_count);

                do  {
                    printf("Enter the number of edges: ");
                    scanf("%d", &max_edge);
                    if (max_edge < ver_count){
                        printf("Warning: Enter an edge count >= vertex count for a connected graph.\n");
                    }
                    else if (max_edge > (ver_count) * (ver_count - 1)){
                        printf("Warning: Enter an edge count less than |V| * (|V|- 1).\n");
                    }
                }while (max_edge < ver_count && max_edge > (ver_count) * (ver_count - 1) );

                srand(time(0));
                g.V = ver_count;
                //g.V = (rand() % (15 - 5 + 1)) + 5; //Upper bound = 15, Lower bound = 5
                printf("Number of vertices created: %d\n", g.V);

                //Initializing Arrays for Dijsktra
                g.S = (int *) malloc(sizeof(int)*g.V); //Array S for visited
                priorityV = (int *) malloc(sizeof(int)*g.V);
                priorityW = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.S[i] = 0;
                    priorityV[i]=0;
                    priorityW[i]=0;
                g.d = (int *) malloc(sizeof(int)*g.V); //Array for distance
                for(int i=0;i<g.V;i++)
                    g.d[i] = 0;

                g.pi = (int *) malloc(sizeof(int)*g.V); //Array for previous vertex
                for(int i=0;i<g.V;i++)
                    g.pi[i] = 0;

                //GENERATING ADJACENCY LIST
                g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

                int edge_count = 0;
                /////////////////
                for(int i=0;i<g.V;i++) //Set a base such that all vertices has at least an edge
                {
                    g.list[i] = (ListNode *)malloc(sizeof(ListNode)); //Head
                    int random_edge;
                    do
                    {
                        //Adding the first edge to each vertex at random
                        random_edge = (rand() % (g.V - 1 + 1)) + 1; //Upper bound = num of vertex, Lower bound = first vertex

                    }while(i == random_edge); //To prevent e.g. if first vertex connected to first vertex

                    g.list[i]->vertex = random_edge;
                    g.list[i]->weight = (rand() % (10 - 1 + 1)) + 1;
                    g.list[i]->next = NULL;
                    g.list[i]->source=i;
                    g.E++;
                    edge_count++;
                }

                //We add edges by random until we hit the max_count
                int remaining_edges = max_edge - edge_count;

                //for(int i=0; i<(rand() % (g.V - 1 + 1)) + 1; i++) {//Add at least one more edge to the graph, capped at g.V times
                for(int i=0; i<remaining_edges; i++) {

                    //V1 is to get a random vertex
                    V1 =  (rand() % (g.V - 1 + 1)) + 1; //Range from 1 to g.V
                    temp = g.list[V1 - 1];
                    while(temp->next != NULL)
                        temp = temp->next;
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    do
                    {
                        temp->next->vertex = (rand() % (g.V - 1 + 1)) + 1; //Upper bound = num of vertex, Lower bound = first vertex
                    }while(V1 == temp->next->vertex); //To prevent e.g. if first vertex connected to first vertex
                    temp->next->source = V1;
                    temp->next->weight = (rand() % (10 - 1 + 1)) + 1;
                    temp->next->next = NULL;

                    g.E++;
                }
                break;
            case 6:
                printf("Closing Program\n");
                break;
        }
    }

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

/*enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
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

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
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

void adjM2adjL(Graph *g)
{
    int i,j;
    ListNode **list;
    ListNode *temp;

    if(g->type == ADJ_LIST) {printf("Error"); return;}
    if(g->V<=0){printf("Empty graph!"); return;}

    list = (ListNode **) malloc(g->V*sizeof(ListNode *));
    for(i=0;i<g->V;i++)
        list[i] = NULL;

    for(i=0;i<g->V;i++){
        for(j=0;j<g->V;j++){
            if(g->adj.matrix[i][j]==1){
                if(list[i]==NULL){
                    list[i] = (ListNode *)malloc(sizeof(ListNode));
                    list[i]->vertex = j+1;
                    list[i]->next = NULL;
                    temp = list[i];
                }
                else{
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    temp->next->vertex = j+1;
                    temp->next->next =NULL;
                    temp = temp->next;
                }
            }
        }
    }

    g->type = ADJ_LIST; //change representation form

    //free adjMatrix
    for(i=0;i<g->V;i++)
        free(g->adj.matrix[i]);
    free(g->adj.matrix);

    g->adj.list = list;

}

void adjL2adjM(Graph *g){
    int i,j;
    ListNode *temp;

    if(g->type == ADJ_MATRIX) {printf("Error"); return;}
    if(g->V<=0){printf("Empty graph!"); return;}

    int ** mat = (int **)malloc(g->V*sizeof(int *));
    for(i=0;i<g->V;i++)
        mat[i] = (int *)malloc(g->V*sizeof(int));

    for(i=0;i<g->V;i++)
        for(j=0;j<g->V;j++)
            mat[i][j] = 0;

    for(i=0;i<g->V;i++){
        temp = g->adj.list[i];
        while(temp!=NULL){
            mat[i][(temp->vertex)-1]=1;
            temp = temp->next;
        }
    }

    g->type = ADJ_MATRIX;

    for(i=0;i<g->V;i++)
        free(g->adj.list[i]);
    free(g->adj.list);

    g->adj.matrix = mat;

}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void calDegreeV(Graph g, int *degreeV)
{
    int i,j;
    ListNode *temp = NULL;

    if(g.type == ADJ_MATRIX){
        for(i=0;i<g.V;i++){
            degreeV[i] = 0;
            for(j=0;j<g.V;j++){
                degreeV[i] += g.adj.matrix[i][j];
            }
        }
    }
    else{
        for(i=0;i<g.V;i++){
            degreeV[i]=0;
            ListNode *temp = g.adj.list[i];
            while(temp != NULL){
                degreeV[i]++;
                temp = temp->next;
            }
        }
    }
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}
*/
