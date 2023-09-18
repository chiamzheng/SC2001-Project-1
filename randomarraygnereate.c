#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator
#define SIZE 5

int** generate(int x, int* lengths);

int main() {
    srand(time(NULL)); // Seed the random number generator (time(NULL) for random)

    int choice = 0, x = 100, generated = 0, i = 0, ele = 0,ind=0;
    int** arr = NULL;
    int* arr_lengths = (int*)calloc(SIZE, sizeof(int)); // To store the lengths of arrays

    while (choice != 5) {
        printf("1.Generate array\n");
        printf("2.Size of array\n");
        printf("3.First 100 Elements of array\n");
        printf("4.Find specific element of array\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (generated == 0) {
                    arr = generate(x, arr_lengths); // Pass x and arr_lengths to the generate function
                    generated = 1;
                }
                else {
                    for (i = 0; i < SIZE; i++) {
                        free(arr[i]);
                    }
                    free(arr);
                    arr=generate(x, arr_lengths);
                }
                break;
            case 2:
                if (generated == 1) {
                    printf("Sizes of arrays: \n");
                    for (i = 0; i < SIZE; i++) {
                        printf("Array %d length: %d\n", i, arr_lengths[i]);
                    }
                }
                else {
                    printf("No array generated\n");
                }
                break;
            case 3:
                if (generated == 1) {
                    printf("Enter index of array (0-4)\n");
                    scanf("%d", &ele);
                    if (ele < 0 || ele >= SIZE) {
                        printf("Invalid index\n");
                    }
                    else {
                        for (i = 0; i < 100; i++) {
                            printf("%d ", arr[ele][i]);
                        }
                        printf("\n");
                    }
                }
                else {
                    printf("No array generated\n");
                }
                break;
            case 4:
                if (generated == 1){
                    printf("Enter Array (0-4)");
                    scanf("%d", &ele);
                    if (ele < 0 || ele >= SIZE) {
                        printf("Invalid index\n");
                    }
                    else{
                        printf("Choose index (0-%d)\n",arr_lengths[ele]-1);
                        scanf("%d",&ind);
                        printf("The element at %d is %d\n",ind,arr[ele][ind]);

                    }
                }

                else {
                    printf("No array generated\n");
                }
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    // Free the allocated memory before exiting
    if (generated == 1) {
        for (i = 0; i < SIZE; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    free(arr_lengths);
    printf("Closing Program");
    return 0;
}

int** generate(int x, int* lengths) {
    int i = 0, j = 0, length = 100, multiplier=10; 

    int** arr = (int**)calloc(SIZE, sizeof(int*));
    for (i = 0; i < SIZE; i++) {
        length = length * multiplier; // increasing size for current  array
        lengths[i] = length; // Store the length of each array
        arr[i] = (int*)calloc(length, sizeof(int));
        for (j = 0; j < length; j++) {
            arr[i][j] = (rand() % x) + 1; //assigning random values to array
        }
        printf("Array %d generated\n", i);
    }
    printf("All Arrays generated\n");
    return arr;
}
