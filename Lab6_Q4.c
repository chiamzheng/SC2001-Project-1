#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator
typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    //int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void BFS (Graph G, int v);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void dik(Graph G, ListNode node);
int ExtractCheapest(int[] array);
int main()
{
    Graph g;
    int i,j,weight=0,x=10;
    srand(time(NULL));
    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
           //arr[i][j] = (rand() % x) + 1; //assigning random values to array

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            printf("Enter in the weight of the connected vertices %d to %d\n",V1,V2);
            scanf("%d",&weight);
            g.matrix[V1-1][V2-1] = weight;

            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    //printf("Enter a start vertex for BFS:\n");
    ///scanf("%d", &i);
    printGraphMatrix(g);
    //BFS(g,i);

    return 0;
}
void dik(Graph G, ListNode node){

    int d[G.V], pi[G.V],S[G.V],i=0,priority[G.V],queuesize=1,u, v=0,sortarr;


    for(i=0;i<G.V;i++){
        d[i]=10000; //assign infinity
        pi[i]=0; // assign null
        S[i]=0;
        priority[i]=0;// initialise priority
    }
    d[node.vertex]=0;
    priority[0]=node.vertex; // queue source node

    //add vertices to priority queue
    while(queuesize!=0){
        u=priority[0];
        queuesize--;
        for(i=0;i<queuesize-1;i++){
            priority[i]=priority[i+1];
        }
        priority[G.V-1]=0; //shift entire queue up

        S[u]=1;
        for(v=0;v<G.V;v++){
            if(G.matrix[u][v]!=0 && S[v]!=1 && d[v]>d[u]+G.matrix[u][v]){
                //remove v from Q
                d[v]=d[u]+G.matrix[u][v];
                pi[v]=u;
                priority[queuesize]=v;//actually must insert based on its d[V]
                queuesize++;
            }
        }



    }


return;
}
void insertionSort(int arr[], int start, int end){
    for (int i = start + 1; i < end; i++) {
                for (int j = i; j > 0; j--) {
                    if (arr[j] < arr[j - 1])
                        swap(arr, j, j - 1);
                    else
                        break;
            }
    }
}
void swap(int list[], int x, int y)
{
    int temp;

    temp = list[x];
    list[x] = list[y];
    list[y] = temp;
}

/*void BFS(Graph g, int v){
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;

    int w;
    int i;

    enqueue(&q,v);
    g.visited[v-1] = 1;
    printf("%d ",v);

    while(isEmptyQueue(q)==0){
        w = dequeue(&q);

        for(i=0;i<g.V;i++)
        {
            if(g.matrix[w-1][i] == 1 && g.visited[i]==0)
            {
                g.visited[i]=1;
                printf("%d ",i+1);
                enqueue(&q,i+1);
            }
        }
    }

}
*/
void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}
