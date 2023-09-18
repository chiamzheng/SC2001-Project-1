#include <stdio.h>

void mergeSort(int array[], int left, int right);
void merge(int array[], int left_index, int mid_index, int right_index);
void printArray(int arr[], int size);

//void insertSort ();
//void hybridSort (int array[], int left, int right, int S);

int keyCmp = 0; //Global variable

int main(void) {
    int arr[] = { 10, 12, 13, 3, 6, 7, 5 };
    int arr_size = sizeof(arr) / sizeof(arr[0]); //calculating the size of array
      
    printf("Imported array of size %d is \n", arr_size);
    printArray(arr, arr_size);
      
    mergeSort(arr, 0, arr_size - 1);
      
    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    printf("Number of key comparisons: %d\n", keyCmp);
    
    return 0;
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
