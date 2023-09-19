#include <stdio.h>
#include <stdlib.h>

void insertionSort(int list[], int n);
void swap(int list[], int x, int y);

int main()
{
    int* list;
    int size;

    printf("Enter size of list: \n");
    scanf("%d", &size);
    list = (int*)malloc(size * sizeof(int));

    printf("Enter %d elements for list: \n", size);
    for(int i=0; i<size; i++)
    {
        scanf("%d", &list[i]);
    }

    insertionSort(list, size);

    for(int i=0; i<size; i++)
    {
        printf("%d ", list[i]);
    }

    return 0;
}

void insertionSort(int list[], int n)
{
    for(int i=1; i<n; i++)
    {
        for(int j=i; j>0; j--)
        {
            if(list[j] < list[j-1])
            {
                swap(list, j, j-1);
            }
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
