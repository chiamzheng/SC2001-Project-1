#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for the random number generator


int** generate(int x, int size,int* lengths);
void mergeSort(int array[], int left, int right);
void merge(int array[], int left_index, int mid_index, int right_index);
void printArray(int arr[], int size);
void insertionSort(int list[], int n);
void swap(int list[], int x, int y);
unsigned int keyCmp = 0; //Global variable

int main() {
    srand(time(NULL)); // Seed the random number generator (time(NULL) for random)

    int choice = 0, x = 1000, generated = 0, gen=0,i = 0, ele = 0,ind=0,size=5;
    int** arr = NULL;
    int* arr_lengths = NULL; // To store the lengths of arrays
    unsigned int* arr_keyCmp = NULL; // To store key comparisons of all arrays

    while (choice != 8) {
        printf("1.Generate array\n");
        printf("2.Size of array\n");
        printf("3.First 100 Elements of array\n");
        printf("4.Find specific element of array\n");
        printf("5.Merge sort\n");
        printf("6.Insertion sort\n");
        printf("7.Number of key comparisons\n");
        printf("8.Exit program\n");
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
                            arr_keyCmp=(int*)calloc(size, sizeof(int));// create arr_keyCmp array
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
            case 5:                             // merge sort
                if (generated == 1){
                    for(i=0;i<size;i++){
                        keyCmp=0;
                        mergeSort(arr[i], 0, arr_lengths[i] - 1);
                        printf("\nSorted array is \n");
                        //printArray(arr[0], arr_lengths[0]);
                        printf("Number of key comparisons: %u\n", keyCmp);
                        arr_keyCmp[i]=keyCmp;
                    }
                }

                break;
            case 6:                                        //insertion sort
                if (generated == 1){
                    for(i=0;i<size;i++){
                        keyCmp=0;
                        insertionSort(arr[i], arr_lengths[i]);
                        //printArray(arr[0], arr_lengths[0]);
                        printf("Number of key comparisons: %u\n", keyCmp);
                        arr_keyCmp[i]=keyCmp;
                    }
                }
                break;
            case 7:
                printf("Key comparisons are :\n");
                for(i=0;i<size;i++){
                    printf("%d : %u\n",arr_lengths[i],arr_keyCmp[i]);
                }
                break;
            case 8:
                printf("Closing Program");
                break;
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
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void mergeSort(int array[], int left, int right){

    if (left < right){
        int mid = left + (right - left) / 2; //Saw online to avoid overflow when the size of our data increases
        mergeSort(array, left, mid);
        mergeSort(array, mid+1, right);

        merge(array, left, mid, right);

    }

}

void merge(int array[], int left_index, int mid_index, int right_index){

    //Partitioning the list into two halves, temporary arrays l_arr and r_arr
    int l_size = (mid_index - left_index) + 1;
    int r_size = (right_index - mid_index);
    int l_arr[l_size], r_arr[r_size];

    for (int i = 0; i < l_size; i++){
        l_arr[i] = array[i + left_index];
    }
    for (int j = 0; j < r_size; j++){
        r_arr[j] = array[j + mid_index + 1];
    }


    //Initalizing the indices of the left & right to 0 before starting the merging of the left and right array into the original
    int l_index = 0, r_index = 0;
    int original_index = left_index;

    //Exit condition: When either left or right array are empty aka have been sorted through
    while (l_index < l_size && r_index < r_size){

        if (l_arr[l_index] <= r_arr[r_index]){ //when left <= right
            array[original_index] = l_arr[l_index];
            l_index++;
            keyCmp++;
        }
        else{ //when right  < left
            array[original_index] = r_arr[r_index];
            r_index++;
            keyCmp++;
        }
        original_index++;
    }

    //Now that either the left or right array is empty, we copy the remaining integers into the original array to complete the "merged" array
    //Copying the elements of left array
    if (l_index < l_size){
        while (l_index < l_size){
            array[original_index] = l_arr[l_index];
            l_index++;
            original_index++;
        }
    }
    //Copying the elements of right array
    else{ //if (r_index < r_size)
        while (r_index < r_size){
            array[original_index] = r_arr[r_index];
            r_index++;
            original_index++;
        }
    }



}
void insertionSort(int list[], int n)
{
    for(int i=1; i<n; i++)
    {
        for(int j=i; j>0; j--)
        {
            keyCmp++;
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
/*
void hybridSort(int array[], int left_index, int mid_index, int right_index, int S){

    //not sure how to calculate the size of the array
    int array_size = sizeof(array) / sizeof(array[0]); //returns size of pointer
    printf("Size of array is: %d\n", array_size);
    if (array_size <= S){
    //Insertion Sort here
    //
    }
    else {
        //Merge Sort here
        //Partitioning the list into two halves, temporary arrays l_arr and r_arr
        int l_size = (mid_index - left_index) + 1;
        int r_size = (right_index - mid_index);
        int l_arr[l_size], r_arr[r_size];

        for (int i = 0; i < l_size; i++){
            l_arr[i] = array[i + left_index];
        }
        for (int j = 0; j < r_size; j++){
            r_arr[j] = array[j + mid_index + 1];
        }


        //Initalizing the indices of the left & right to 0 before starting the merging of the left and right array into the original
        int l_index = 0, r_index = 0;
        int original_index = left_index;

        //Exit condition: When either left or right array are empty aka have been sorted through
        while (l_index < l_size && r_index < r_size){

            if (l_arr[l_index] <= r_arr[r_index]){ //when left <= right
                array[original_index] = l_arr[l_index];
                l_index++;
                keyCmp++;
            }
            else{ //when right  < left
                array[original_index] = r_arr[r_index];
                r_index++;
                keyCmp++;
            }
            original_index++;
        }

        //Now that either the left or right array is empty, we copy the remaining integers into the original array to complete the "merged" array
        //Copying the elements of left array
        if (l_index < l_size){
            while (l_index < l_size){
                array[original_index] = l_arr[l_index];
                l_index++;
                original_index++;
            }
        }
        //Copying the elements of right array
        else{ //if (r_index < r_size)
            while (r_index < r_size){
                array[original_index] = r_arr[r_index];
                r_index++;
                original_index++;
            }
        }
    }
}

*/
