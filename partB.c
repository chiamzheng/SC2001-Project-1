#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator

typedef struct _listnode
{
    int vertex;
    int weight;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *S; //Keep track of the vertex that has already found shortest path
    int *d; //Shortest distance from source vertex to all other vertex
    int*pi; //Predecessor
    ListNode **list;
}Graph;

int main()
{
    Graph g;
    ListNode *temp;
    int choice = 0, V1, V2, W;

    g.V = 0; //Number of vertices in a graph
    g.E = 0; //Number of edges in a graph

    while(choice >= 0 && choice <= 3)
    {
        printf("1. Manual Input\n");
        printf("2. Random Generator\n");
        printf("3. Print Adjacency List\n");
        printf("4. Exit Program\n");
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
                }

                printf("Enter the number of vertices:\n");
                scanf("%d", &g.V); //Number of vertices in a graph

                g.S = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.S[i] = 0;

                g.d = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.d[i] = 0;

                g.pi = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.pi[i] = 0;

                g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
                for(int i=0;i<g.V;i++) //Set null to all list node
                    g.list[i] = NULL;

                printf("Enter two vertices in which V1 is adjacent to V2 and the weights:\n"); //V1 -> V2
                while(scanf("%d %d %d",&V1,&V2, &W) == 3)
                {
                    if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
                    {
                        if(g.list[V1-1] == NULL)
                        {
                            g.list[V1-1] = (ListNode *)malloc(sizeof(ListNode));
                            g.list[V1-1]->vertex = V2;
                            g.list[V1-1]->weight = W;
                            g.list[V1-1]->next = NULL;
                            temp = g.list[V1-1];
                            g.E++;
                        }
                        else
                        {
                           temp->next = (ListNode *)malloc(sizeof(ListNode));
                           temp->next->vertex = V2;
                           temp->next->weight = W;
                           temp->next->next = NULL;
                           temp = temp->next;
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
                }

                srand(time(0));
                g.V = (rand() % (15 - 5 + 1)) + 5; //Upper bound = 15, Lower bound = 5
                printf("Number of vertices created: %d\n", g.V);

                g.S = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.S[i] = 0;

                g.d = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.d[i] = 0;

                g.pi = (int *) malloc(sizeof(int)*g.V);
                for(int i=0;i<g.V;i++)
                    g.pi[i] = 0;

                g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
                for(int i=0;i<g.V;i++) //Set a base such that all vertices has at least an edge
                {
                    g.list[i] = (ListNode *)malloc(sizeof(ListNode));
                    do
                    {

                        g.list[i]->vertex = (rand() % (g.V - 1 + 1)) + 1; //Upper bound = num of vertex, Lower bound = first vertex

                    }while(i == g.list[i]->vertex); //To prevent e.g. if first vertex connected to first vertex
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
                    temp->next->weight = (rand() % (10 - 1 + 1)) + 1;
                    temp->next->next = NULL;
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
                printf("Closing Program\n");
                break;
        }
    }

    return 0;
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
