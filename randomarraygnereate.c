#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator


int** generate(int x, int size,int* lengths);

int main() {
    srand(time(NULL)); // Seed the random number generator (time(NULL) for random)

    int choice = 0, x = 100, generated = 0, gen=0,i = 0, ele = 0,ind=0,size=5;
    int** arr = NULL;
    int* arr_lengths = NULL; // To store the lengths of arrays

    while (choice != 5) {
        printf("1.Generate array\n");
        printf("2.Size of array\n");
        printf("3.First 100 Elements of array\n");
        printf("4.Find specific element of array\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Choose sample size:\n");
                printf("1.Small\n");
                printf("2.Medium\n");
                printf("3.Large\n");
                scanf("%d",&gen);
                if((gen>0)&&(gen<4)&&(generated==1)){ //check if generated before and free previous arrays
                    for (i = 0; i < size; i++) {
                        free(arr[i]);
                    }
                    free(arr);
                    free(arr_lengths);
                }
                while(gen!=979797){
                    switch(gen){ //choose size of array
                        case 1:
                            size=5;
                            gen=989898;
                            break;
                        case 2:
                            size=9;
                            gen=989898;
                            break;
                        case 3:
                            size=37;
                            gen=989898;
                            break;
                        case 989898:
                            arr_lengths=(int*)calloc(size, sizeof(int));// create arr_lengths array
                            arr = generate(x, size, arr_lengths); // Pass x, size and arr_lengths to the generate function
                            generated = 1;
                            gen=979797;
                            break;
                        case 979797:
                            break;
                        default:
                            printf("Invalid choice\n");
                            gen=979797;
                            break;
                    }
                }

                break; // end case 1
            case 2:
                if (generated == 1) {
                    printf("Sizes of arrays: \n");
                    for (i = 0; i < size; i++) {
                        printf("Array %d length: %d\n", i, arr_lengths[i]);
                    }
                }
                else {
                    printf("No array generated\n");
                }
                break; // end case 2
            case 3:
                if (generated == 1) {
                    printf("Enter index of array (0-%d)\n",size-1);
                    scanf("%d", &ele);
                    if (ele < 0 || ele >= size) {
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
                break; // end case 3
            case 4:
                if (generated == 1){
                    printf("Enter Array (0-%d)",size-1);
                    scanf("%d", &ele);
                    if (ele < 0 || ele >= size) {
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
                break; // end case 4
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    // Free the allocated memory before exiting
    if (generated == 1) {
        for (i = 0; i < size; i++) {
            free(arr[i]);
        }
        free(arr);
    }

    free(arr_lengths);
    printf("Closing Program");
    return 0;
}

int** generate(int x, int size, int* lengths) {
    int i = 0, j = 0, length = 1000, multiplier=10;
    int** arr = (int**)calloc(size, sizeof(int*));
    if(size==5){
        //no need change length or multiplier
    }
    else if(size==9){
        multiplier=2;
    }
    else if(size==37){
        multiplier=1000;
    }

    for (i = 0; i < size; i++) {
        lengths[i] = length; // Store the length of each array
        arr[i] = (int*)calloc(length, sizeof(int));
        for (j = 0; j < length; j++) {
            arr[i][j] = (rand() % x) + 1; //assigning random values to array
        }
        printf("Array %d generated\n", i);

        switch(size){
            case 37:
                if((length/multiplier)==10){
                    multiplier=length;
                }
                length= length+multiplier;
                break;
            case 9:
                multiplier = 10/multiplier; //1k,5k,10k,50k,100k,500k,1mil,5mil,10mil
            case 5:
                length=length*multiplier; //1k,10k,100k,1mil,10mil
                break;
        }

    }
    printf("All Arrays generated\n");
    return arr;
}
